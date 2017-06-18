PImage bg;
int bgSpace=382;
int n_bgs=3;
int window_height=550;
int window_width=bgSpace*n_bgs;

int ballRadius = 15;
int score = 0;
int game_status;
int pillarSpace = 210;
int n_pillars = window_width/pillarSpace+1;

Bird player;
Pillar[] pillar = new Pillar[n_pillars];

void settings()
{
  size(window_width,window_height);
}

void setup() 
{
  player = new Bird();
  for (int i =0; i < n_pillars; i++) 
  {
    pillar[i] = new Pillar(i);
  }
  bg=loadImage("background.png");
  game_status = 0;
}

void draw() 
{
  for (int i=0; i<n_bgs; i++)
  {
    image(bg,i*bgSpace,0);
  }
  
  switch(game_status) 
  {
  case 0:
    initialScreen();
    break; 
  case 1:
    gameRun();
    break;
  case 2:
    gameEnd();
    break;
  }
}

void initialScreen()
{
  textSize(60);
  text("Flappy Bird", width/3, height/2-100);
  textSize(30);
  text("Press any Key to play!", width/3, height/2+100);
}

void gameEnd()
{
  textSize(46);
  fill(#ecf0f1);
  text("Game Over", (window_width/2)-120, (window_height/2)-60);
  textSize(32);
  text("Score:", (window_width/2)-80, (window_height/2));
  text(score, (window_width/2)+50, (window_height/2));
}

void gameRun() 
{
  player.move();
  player.render();
  for (int i = 0; i < n_pillars; i++) 
  {
    pillar[i].checkLimits();
    pillar[i].render(); 
    pillar[i].setPoints();
  }
  renderScore();
  if (player.isCollision()) game_status=2;
}

void renderScore() 
{
  strokeWeight(2);
  stroke(#ecf0f1);
  fill(#2c3e50);
  ellipse(70, 70, 80, 80);
  stroke(#2c3e50);
  fill(#ecf0f1);
  ellipse(40, 35, 60, 60);
  textSize(18);
  fill(#2c3e50);
  text("Score", 17, 40);
  fill(#ecf0f1);
  textSize(24);
  text(score, 65, 85);
}

void keyPressed() 
{
  if (game_status == 0) 
  {
    game_status=1;
  } 
  else if(game_status == 2) 
  {
    // init
    score = 0;
    player.y = (window_height/2);
    player.vy = 0;
    
    // draw the pillars
    for(int i = 0; i < n_pillars; i++)
    {
      pillar[i] = new Pillar(i);
    }
    
    // switch to run
    game_status=1;
  } else {
    // the bird jumps
    player.jump();
  }
}

void mousePressed()
{
  if (game_status == 0) 
  {
    game_status=1;
  } 
  else if(game_status == 2) 
  {
    // init the features
    score = 0;
    player.y = (window_height/2);
    player.vy = 0;
    
    // draw the pillars
    for(int i = 0; i < n_pillars; i++)
    {
      pillar[i] = new Pillar(i);
    }
    
    // switch to run
    game_status=1;
  } else {
    // the bird jumps
    player.jump();
  }
}