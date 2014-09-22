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

// track scores
int userScore;
int robotScore;
// CONST: max score for ending game; change to desired value
int maxScore = 5;
 
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
  delay(300); // holds the chosen move for given delay
  rock.write(down_move);
  delay(delay_time);
  rock.write(stop_move1);
}
void makeMovePaper()
{
  paper.write(up_move);
  delay(delay_time);
  paper.write(stop_move2);
  delay(300); // holds the chosen move for given delay
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

int userInput()
// gets user input for move
// can be changed later for input from buttons; uses serial monitor for now
{
  Serial.flush(); // clears outgoing Serial buffer
  while(Serial.available()){ //clears incoming Serial buffer
    Serial.read();
  }
  
  Serial.println("Choice (rock=0, scissors=1, paper=2):");
  while(!Serial.available()){} //halts program until input is received
  int choice = Serial.parseInt();
  
  Serial.println(choice, DEC); 
  if (choice == 0)
    return 0;
  else if (choice == 1)
    return 1;
  else if (choice == 2)
    return 2;
}
  
int whoWins(int user, int robot)
// return 0 for draw, 1 for user win, 2 for robot win
// return values may be changed later
{
  if (user == robot) // draw
    return 0;
  else if (user == 0){  // user played rock
    if (robot == 1)
      return 1;
    else if (robot == 2)
      return 2;
  }
  else if (user == 1){  // user played scissors
    if (robot == 0)
      return 2;
    else if (robot == 2)
      return 1;
  }
  else if (user == 2){  // user played paper
    if (robot == 0)
      return 1;
    else if (robot == 1)
      return 2;
  }
}

void updateScore(int winner)
// adds 1 to winner's score constant
{
  if (winner == 1)
    ++userScore;
  else if (winner == 1)
    ++robotScore;
}

boolean gameOver()
// checks if game is over
{
  if (userScore == maxScore || robotScore == maxScore)
    return True;
  else
    return False;

void loop() 
{
    int user = userInput(); // store user input
    
    countdown();
         
    rock.write(stop_move1);
    paper.write(stop_move2);
//    scissors.write(stop_move1);
   
    delay(300);
    
    int randomMove = random(0,3);
    if(randomMove == 0){
      makeMoveRock();
    }
//    else if(randomMove == 1){
//      makeMove(scissors);
//    }
    else if(randomMove == 2){
      makeMovePaper();
    }
    
    rock.write(stop_move1);
    paper.write(stop_move2);
//    scissors.write(stop_move);

    delay(1000);
    
    // prints info on game; TEMP
    Serial.print("Robot plays: ");
    Serial.println(randomMove);
    Serial.print("Winner (0=draw, 1=user, 2=robot): ");
    Serial.println(winner);
    
    //determine winner, update score, and check if game is over
    int winner = whoWins(user, randomMove);
    updateScore(winner);
    if (gameOver())
      Serial.println("Game Over");
} 
