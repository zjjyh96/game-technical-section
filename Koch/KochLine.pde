class KochLine 
{
  PVector a;
  PVector b;

  KochLine(PVector start, PVector end) 
  {
    a = start;
    b = end;
  }

  void display() 
  {
    stroke(0);
    line(a.x, a.y, b.x, b.y);
  }

  PVector start() 
  {
    return a;
  }

  PVector end()
  {
    return b;
  }

  PVector kochleft() 
  {
    PVector v = PVector.sub(b, a);
    v.div(3);
    v.add(a);
    return v;
  }    

  PVector kochmiddle() 
  {
    PVector v = PVector.sub(b, a);
    v.div(3);
    
    PVector p = a.get();
    p.add(v);
    
    rotate(v,-radians(60));
    p.add(v);
    
    return p;
  }    

  PVector kochright() 
  {
    PVector v = PVector.sub(a, b);
    v.div(3);
    v.add(b);
    return v;
  }
}

  public void rotate(PVector v, float theta) 
  {
    float xTemp = v.x;
    v.x = v.x*cos(theta) - v.y*sin(theta);
    v.y = xTemp*sin(theta) + v.y*cos(theta);
  }