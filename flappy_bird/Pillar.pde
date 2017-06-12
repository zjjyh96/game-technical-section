class Pillar {
  float x, yup, ydown, fissureTop, fissureBottom, fissureMiddle;    
  int pillarHeight=426;
  int pillarWidth=69;
  boolean isCount = false;
  PImage pdown,pup;
  
  Pillar(int i) {
    x =600+(i*pillarSpace);
    generateFissure(window_height/2);
    pdown=loadImage("bound_down.png");
    pup=loadImage("bound_up.png");
  }

  void render() {
    yup=fissureTop-pillarHeight;
    ydown=fissureBottom;
    image(pup,x,yup);
    image(pdown,x,ydown);
  }

  void checkLimits() {
    if (x < -pillarWidth) {
      x += pillarSpace*n_pillars;
      generateFissure(window_height/2); 
      isCount=false;
    }
  }

  void setPoints() {
    if (x < window_width/4 && !isCount) {
      score++; 
      isCount=true;;
    }
  }

  void generateFissure(int i) {
    fissureMiddle = random(i)+100;
    fissureTop = fissureMiddle - 85;
    fissureBottom = fissureMiddle + 85;
  }
}