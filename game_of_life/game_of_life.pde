GOL gol;
int iter=0;

void setup() {
  size(720, 460);
  gol = new GOL();
}

void draw() {
  background(255);
  gol.generate();
  gol.display();
  
  if( !gol.isEnd())
  {
    iter++;
  }
  fill(0);
  textSize(32);  
  text(iter,640,230);
}

void mousePressed() {
  iter=0;
  gol.init();
}