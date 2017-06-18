class Bird 
{
  float x, y, vy, vx, g;
  PImage[] bird = new PImage[2];
  int flyState=0;
  int birdHeight=32;
  int birdWidth=45;

  Bird() 
  {
    g=0.5;
    vx=3.25;
    x = window_width/4;
    y = window_height/2;
    bird[0]=loadImage("bird_blue_0.png");
    bird[1]=loadImage("bird_blue_1.png");
  } 
  
  // draw the bird
  void render() 
  {
    gravity();
    switch(flyState)
    {
      case 0:
        image(bird[0],x,y);
        break;
      case 1:
        image(bird[1],x,y);
        break;
    }
  }

  void jump() 
  {
    vy = -9;
    flyState=0;
  }

  void gravity() 
  {
    vy += g;
    if (vy>0)
      flyState=1;
    else flyState=0;
  }

  void move() 
  {
    y += vy;
    for (int i = 0; i < n_pillars; i++) 
    {
      pillar[i].x -= vx;
    }
  }

  boolean isCollision() 
  {
    if (y > window_height||y < 0) 
    {
      return true;
    }
    
    for(int i = 0; i < n_pillars; i++)
    {
      float pWidth=pillar[i].pillarWidth;
      float pHeight=pillar[i].pillarHeight;
      float px=pillar[i].x;
      float pyup=pillar[i].yup;
      float pydown=pillar[i].ydown;
      
      if (isInBox(x,y,birdHeight,birdWidth,px,pyup,pHeight,pWidth))
      {
        return true;
      }
      if (isInBox(x,y,birdHeight,birdWidth,px,pydown,pHeight,pWidth))
      {
        return true;
      }
    }
    return false;
  }
  
  boolean isInBox(float x1,float y1,float h1,float w1,float x2,float y2,float h2,float w2)
  {
    float[][] box1=new float[4][2];
    int i;
    box1[0][0]=x1; 
    box1[0][1]=y1;
    box1[1][0]=x1+w1; 
    box1[1][1]=y1;
    box1[2][0]=x1; 
    box1[2][1]=y1+h1;
    box1[3][0]=x1+w1; 
    box1[3][1]=y1+h1;
    
    for (i=0;i<=3;i++)
    {
      if (box1[i][0]<=x2+w2 && box1[i][0]>=x2)
        if (box1[i][1]<=y2+h2 && box1[i][1]>=y2)
          return true;
    }
    return false;
  }
}