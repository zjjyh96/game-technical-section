KochFractal k;

void setup() 
{
  size(800,250);
  background(255);
  frameRate(1);
  k = new KochFractal();
}

void draw() 
{
  background(255);
  k.render();
  k.nextLevel();
  fill(0);
  text("iter=",10,20);
  text(k.getCount(),40,20);
  if (k.getCount() > 6) 
  {
    k.restart();
  }
}