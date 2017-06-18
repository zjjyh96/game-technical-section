#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>


//调整窗口大小
void expand_origin(const cv::Mat &origin, cv::Mat &image)
{
    cv::Mat tmp = image(cv::Range(1, origin.size().height + 1), cv::Range(1, origin.size().width + 1));
    origin.copyTo(tmp);

    tmp = image(cv::Range(0, 1), cv::Range(1, origin.size().width + 1));
    origin.row(0).copyTo(tmp);

    tmp = image(cv::Range(origin.size().height + 1, origin.size().height + 2),
                cv::Range(1, origin.size().width + 1));
    origin.row(origin.size().height - 1).copyTo(tmp);

    tmp = image(cv::Range(1, origin.size().height + 1), cv::Range(0, 1));
    origin.col(0).copyTo(tmp);

    tmp = image(cv::Range(1, origin.size().height + 1),
                cv::Range(origin.size().width + 1, origin.size().width + 2));
    origin.col(origin.size().height - 1).copyTo(tmp);

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
}

//计算梯度
void calculate_gradient(cv::Mat &gradientX, cv::Mat &gradientY, cv::Mat &image)
{
    const cv::Mat sobelX = (cv::Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    const cv::Mat sobelY = (cv::Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    cv::Mat tmp;
    int m = gradientX.size().height, n = gradientX.size().width;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            tmp = image(cv::Range(i, i + 3), cv::Range(j, j + 3));// image[0:2, 0:2]...image[end-2:end, end-2:end]
            gradientX.at<float>(i, j) = cv::sum(tmp.mul(sobelX)).val[0];
            gradientY.at<float>(i, j) = cv::sum(tmp.mul(sobelY)).val[0];
        }
    }
}

//提取本地R的最大值
void pick_R_local_max(cv::Mat &response, double threshold)
{
    double maxVal = 0, tmp;
    int windowSize = 30;
    int m = response.size().height, n = response.size().width;
    for (int i = 0; i < m - windowSize; i += windowSize) {
        for (int j = 0; j < n - windowSize; j += windowSize) {
            maxVal = 0;
            for (int k = i; k < i + windowSize; ++k) {
                for (int l = j; l < j + windowSize; ++l) {
                    tmp = response.at<float>(k, l);
                    if (tmp - maxVal > 1e-7 && tmp - threshold > 1e-7) {
                        maxVal = response.at<float>(k, l);
                    }
                    else {
                        response.at<float>(k, l) = 0.0f;
                    }
                }
            }
        }
    }

    for (int k = 0; k < n - windowSize; k += windowSize) {
        maxVal = 0;
        for (int i = m - windowSize; i < m; ++i) {
            for (int j = k; j < k + windowSize; ++j) {
                tmp = response.at<float>(i, j);
                if (tmp - maxVal > 1e-7 && tmp - threshold > 1e-7) {
                    maxVal = response.at<float>(i, j);
                }
                else {
                    response.at<float>(i, j) = 0.0f;
                }
            }
        }
    }
    for (int k = 0; k < m - windowSize; k += windowSize) {
        maxVal = 0;
        for (int i = k; i < k + windowSize; ++i) {
            for (int j = n - windowSize; j < n; ++j) {
                tmp = response.at<float>(i, j);
                if (tmp - maxVal > 1e-7 && tmp - threshold > 1e-7) {
                    maxVal = response.at<float>(i, j);
                }
                else {
                    response.at<float>(i, j) = 0.0f;
                }
            }
        }
    }

    maxVal = 0;
    for (int i = m - windowSize; i < m; ++i) {
        for (int j = n - windowSize; j < n; ++j) {
            tmp = response.at<float>(i, j);
            if (tmp - maxVal > 1e-7 && tmp - threshold > 1e-7) {
                maxVal = response.at<float>(i, j);
            }
            else {
                response.at<float>(i, j) = 0.0f;
            }
        }
    }
}

//绘制角点（红色）
void draw_corner(cv::Mat &response, cv::Mat &image, int windowSize)
{
    int m = response.size().height, n = response.size().width;
    cv::Vec3b red(0, 0, 255);
    for (int i = windowSize / 2, k = 0; k < m; ++i, ++k) {
        for (int j = windowSize / 2, l = 0; l < n; ++j, ++l) {
            if (response.at<float>(k, l) > 1e-7) {
                image.at<cv::Vec3b>(i, j) = red;
            }
        }
    }
}

//计算矩阵M
void calculate_M(cv::Mat &gradientX, cv::Mat &gradientY, cv::Mat &M, int row, int col, int windowSize)
{
    for (int i = row - windowSize / 2; i < row + windowSize / 2 + 1; ++i) {
        for (int j = col - windowSize / 2; j < col + windowSize / 2 + 1; ++j) {
            M.at<float>(0, 0) += gradientX.at<float>(i, j) * gradientX.at<float>(i, j);
            M.at<float>(1, 0) += gradientX.at<float>(i, j) * gradientY.at<float>(i, j);
            M.at<float>(0, 1) += gradientX.at<float>(i, j) * gradientY.at<float>(i, j);
            M.at<float>(1, 1) += gradientY.at<float>(i, j) * gradientY.at<float>(i, j);
        }
    }
}

//用求根公式计算两个特征值
void calculate_lambda(cv::Mat &M, float &lambda1, float &lambda2)
{

    float a = 1.0f, b = -cv::trace(M).val[0], c = cv::determinant(M);
    lambda1 = 0.5f / a * (-b + sqrt(b*b - 4 * a * c));
    lambda2 = 0.5f / a * (-b - sqrt(b*b - 4 * a * c));
}

//将值映射到0-255
void normalize_to_Range_0_255(cv::Mat &M)
{
    double minVal = 0.0, maxVal = 255.0;
    cv::minMaxIdx(M, &minVal, &maxVal);
    M = (M - minVal) / (maxVal - minVal) * 255;
}

//计算R值
double calculate_R(cv::Mat &image, cv::Mat &response, const cv::Size &responseSize, float cof_k, int windowSize)
{
    cv::Mat lambdaMin(responseSize, CV_32F), lambdaMax(responseSize, CV_32F);
    float lambda1, lambda2;
    cv::Mat gradientX(image.size().height - 2, image.size().width - 2, CV_32F);
    cv::Mat gradientY(image.size().height - 2, image.size().width - 2, CV_32F);
    calculate_gradient(gradientX, gradientY, image);

    int m = responseSize.height, n = responseSize.width;
    for (int i = windowSize / 2, k = 0; k < m; ++i, ++k) {
        for (int j = windowSize / 2, l = 0; l < n; ++j, ++l) {
            cv::Mat M(2, 2, CV_32F, cv::Scalar(0.0));
            calculate_M(gradientX, gradientY, M, i, j, windowSize);
            calculate_lambda(M, lambda1, lambda2);
            lambdaMax.at<float>(k, l) = lambda1;
            lambdaMin.at<float>(k, l) = lambda2;
            response.at<float>(k, l) = lambda1 * lambda2 - cof_k * (lambda1 + lambda2) * (lambda1 + lambda2);
        }
    }

    normalize_to_Range_0_255(lambdaMin);
    cv::namedWindow("lambda min");
    cv::imshow("lambda min", lambdaMin);
    cv::waitKey();

    normalize_to_Range_0_255(lambdaMax);
    cv::namedWindow("lambda max");
    cv::imshow("lambda max", lambdaMax);
    cv::waitKey();

    //移去小于0的R值点
    cv::threshold(response, response, 0, 0, cv::THRESH_TOZERO);
    cv::log(response, response);
    //将R值在0-255上线性投影
    normalize_to_Range_0_255(response);
    //显示R值图
    cv::namedWindow("log-normalize-unthreshold response");
    cv::imshow("log-normalize-unthreshold response", response);
    cv::waitKey();

    //Show response after threshold
    double threshold = 240.0;
    cv::threshold(response, response, threshold, 0, cv::THRESH_TOZERO);
    cv::namedWindow("thresholded response");
    cv::imshow("thresholded response", response);
    cv::waitKey();
    return threshold;
}


int main(int argc, char *argv[])
{
    float k;
    int windowSize;
    std::string imageFile;
    double threshold;

//    if (argc != 4) {
//        std::cerr << "argc = " << argc << " is not equal to 4" << std::endl;
//    }

//    imageFile = argv[1];
//    k = atof(argv[2]);
//    windowSize = atoi(argv[3]);

    imageFile = "image.jpg";
    k = 0.06;
    windowSize = 3;

    cv::Mat origin = cv::imread(imageFile);
    cv::Mat image(origin.size().height + 2, origin.size().width + 2, CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));
    expand_origin(origin, image);
    image.convertTo(image, CV_32F);
    cv::Size responseSize(origin.size().width - windowSize * 2, origin.size().height - windowSize * 2);
    cv::Mat response(responseSize, CV_32F);

    //计算根据给定阈值得到的R值图
    threshold = calculate_R(image, response, responseSize, k, windowSize);

    //计算本地最大R值点
    pick_R_local_max(response, threshold);
    cv::namedWindow("corner");
    cv::imshow("corner", response);
    cv::waitKey();
    cv::namedWindow("result");

    //在原图上绘制角点
    draw_corner(response, origin, windowSize);
    cv::imshow("result", origin);
    cv::waitKey();
    return 0;
}
