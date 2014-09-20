// 45 degree sweep for three servos


#include <Servo.h> 
 
Servo rock;  // create servo object to control a servo
Servo paper;
Servo scissors;
 
int stop_move1 = 118; 
float stop_move2 = 97;
int up_move = 180;
int down_move = 0;

int delay_time = 350;
 
void countdown()
{
  for(int i=0; i<3; i++){
     rock.write(up_move);
     paper.write(up_move);
     scissors.write(up_move);
     delay(delay_time);
     rock.write(down_move);
     paper.write(down_move);
     scissors.write(down_move);
     delay(delay_time);
  }
}
void makeMoveRock()
{
  rock.write(up_move);
  delay(delay_time);
  rock.write(stop_move1);
  delay(300); // holds the choosen move for given delay
  rock.write(down_move);
  delay(delay_time);
  rock.write(stop_move1);
}
void makeMovePaper()
{
  paper.write(up_move);
  delay(delay_time);
  paper.write(stop_move2);
  delay(300); // holds the choosen move for given delay
  paper.write(down_move);
  delay(delay_time);
  paper.write(stop_move2);
}

void setup() 
{ 
  rock.attach(9);  // attaches the servo on pin 9 to the servo object 
  paper.attach(10);
  scissors.attach(11);
  Serial.begin(9600);
} 

void loop() 
{
    countdown();
    
 
     
    rock.write(stop_move1);
    paper.write(stop_move2);
//    scissors.write(stop_move1);
   
    delay(300);
    
    int randomMove = random(2);
    if(randomMove == 0){
      makeMoveRock();
    }
//    else if(randomMove == 1){
//      makeMove(scissors);
//    }
    else{
      makeMovePaper();
    }
    rock.write(stop_move1);
    paper.write(stop_move2);
//    scissors.write(stop_move);
    delay(1000);   
} 
