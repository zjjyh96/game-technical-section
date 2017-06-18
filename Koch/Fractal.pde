class KochFractal 
{
  PVector start;
  PVector end;
  ArrayList<KochLine> lines;
  int count;
  
  public KochFractal() 
  {
    start = new PVector(0,height-20);
    end = new PVector(width,height-20);
    lines = new ArrayList<KochLine>();
    restart();
  }

  void nextLevel() 
  {  
    lines = iterate(lines);
    count++;
  }

  void restart() 
  { 
    count = 0;
    lines.clear();
    lines.add(new KochLine(start,end));
  }
  
  int getCount() 
  {
    return count;
  }
  
  void render() 
  {
    for(KochLine l : lines) 
    {
      l.display();
    }
  }

  ArrayList iterate(ArrayList<KochLine> before) 
  {
    ArrayList now = new ArrayList<KochLine>(); 
    for(KochLine l : before)  // for each line before
    {
      PVector a = l.start();                 
      PVector b = l.kochleft();
      PVector c = l.kochmiddle();
      PVector d = l.kochright();
      PVector e = l.end();

      now.add(new KochLine(a,b));
      now.add(new KochLine(b,c));
      now.add(new KochLine(c,d));
      now.add(new KochLine(d,e));
    }
    return now;
  }

}