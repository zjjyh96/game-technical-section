float theta;

void setup()
{
  size(720,360);
}

void draw()
{
  background(255);
  theta = PI/2*mouseX/width;
  
  translate(width/2, height);
  stroke(0);
  branch(100);
}

void branch(float len)
{
  strokeWeight(2);
  line(0,0,0,-len);
  translate(0,-len);
  len *= 0.6;
  
  if (len > 1)
  {
    pushMatrix(); 
    rotate(theta); 
    branch(len);    
    popMatrix();     

    pushMatrix();
    rotate(-theta);
    branch(len);
    popMatrix();
  }
}