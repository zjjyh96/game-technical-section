class GOL 
{
  int w = 16;
  int columns, rows;
  Cell[][] board;

  GOL() {
    columns = (width-80)/w;
    rows = height/w;
    board = new Cell[columns][rows];
    init();
  }

  void init() {
    for (int i = 0; i < columns; i++) {
      for (int j = 0; j < rows; j++) {
        board[i][j] = new Cell(i*w, j*w, w);
      }
    }
  }
  
  boolean isEnd(){
    boolean flag1, flag2;
    flag1=flag2=true;
    
    for ( int i = 0; i < columns;i++) 
      for ( int j = 0; j < rows;j++) 
      {
        if (board[i][j].pre!=board[i][j].state) flag1=false;
      }
      
    for ( int i = 0; i < columns;i++) 
      for ( int j = 0; j < rows;j++) 
      {
        if (board[i][j].ppre!=board[i][j].state) flag2=false;
      }
      
    if (flag1 || flag2) return true;
    else return false;
  }

  void generate() {
     for ( int i = 0; i < columns;i++) {
      for ( int j = 0; j < rows;j++) {
        board[i][j].savePrePrevious();
        board[i][j].savePrevious(); 
      }
    }
    
    for (int x = 0; x < columns; x++) {
      for (int y = 0; y < rows; y++) {
        int neighbors = 0;
        
        // calc the neighbor 9 sum
        for (int i = -1; i <= 1; i++) 
          for (int j = -1; j <= 1; j++)   
            neighbors += board[(x+i+columns)%columns][(y+j+rows)%rows].pre;
        // except itself   
        neighbors -= board[x][y].pre;

        // Rules of Life
        if ((board[x][y].state == 1) && (neighbors <  2)) board[x][y].newState(0);
        else if ((board[x][y].state == 1) && (neighbors >  3)) board[x][y].newState(0); 
        else if ((board[x][y].state == 0) && (neighbors == 3)) board[x][y].newState(1);
      }
    }
  }

  void display() {
    for ( int i = 0; i < columns;i++) {
      for ( int j = 0; j < rows;j++) {
        board[i][j].display();
      }
    }
  }
}