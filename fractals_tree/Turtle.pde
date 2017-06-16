class Turtle {
  
  String todo;
  float len;
  float theta;

  Turtle(String s, float l, float t) {
    todo = s;
    len = l; 
    theta = t;
  } 

  void render() {
    stroke(0, 175);
    for (int i = 0; i < todo.length(); i++) {
      char c = todo.charAt(i);
      switch (c){
      case 'F':
      case 'G':
        line(0, 0, len, 0);
        translate(len, 0);
        break;
      case '+':
        rotate(theta);
        break;
      case '-':
        rotate(-theta);
        break;
      case '[':
        pushMatrix();
        break;
      case ']':
        popMatrix();
        break;
      }
    }
  }

  void setLen(float l) {
    len = l;
  } 

  void changeLen(float percent) {
    len *= percent;
  }

  void setToDo(String s) {
    todo = s;
  }
}