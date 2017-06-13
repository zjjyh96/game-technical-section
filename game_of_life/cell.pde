class Cell 
{
  float x, y;
  float w;

  int state;
  int pre;
  int ppre;

  Cell(float x_, float y_, float w_) {
    x = x_;
    y = y_;
    w = w_;
    
    state = int(random(2));
    pre = state;
  }
  
  void savePrevious() {
    pre = state; 
  }
  
  void savePrePrevious(){
    ppre=pre;
  }

  void newState(int s) {
    state = s;
  }

  void display() {
    if (pre == 0 && state == 1) fill(0,0,255);
    else if (state == 1) fill(0);
    else if (pre == 1 && state == 0) fill(0,0,255);
    else fill(255); 
    stroke(0);
    rect(x, y, w, w);
  }
}