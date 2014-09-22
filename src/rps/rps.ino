// TEAM 23 ROCK, PAPER, SCISSORS ROBOT

#include <Servo.h> 

// pin declarations
int rockPin = 9;
int paperPin = 10;
int scissorsPin = 11;

// Servo object declarations 
Servo rock;
Servo paper;
Servo scissors;
 
// Int representation for things like random() and userInput
int rockInt = 0;
int paperInt = 1;
int scissorsInt = 2;

int drawInt = 0;
int userWinInt = 1;
int botWinInt = 2;

// Values to control the speed of the continuous servos - use floats for percision
float rockStop = 118;
float paperStop = 97;
// NOTE: its worth testing is speed is relative; otherwise just use commented out values
// Also might have to switch up and down depending on Servo orientation
// int up = 180
// int down = 0
float rockUp = rockStop + 50;
float paperUp = paperStop + 50;
float rockDown = rockStop - 50;
float paperDown = paperStop - 50;

int moveTime = 350; // the amount of time (ms) to allow the servos to move up or down
int pauseTime = 1000; // the amount of time for the bot to hold up its chosen move

// track scores
int userScore;
int robotScore;
// CONST: max score for ending game; change to desired value
int maxScore = 5;

// the countdown function is the robots way of doing "Rock, Paper, Scissors"
void countdown()
{
  // move all arms up and down three times
  for(int i=0; i<3; i++){
     rock.write(rockUp);
     paper.write(paperUp);
     delay(moveTime);
     rock.write(rockDown);
     paper.write(paperDown);
     delay(moveTime);
  }
}
// the makeMove functions hold up the chosen move for pauseTime and then put the arm down
void makeMoveRock()
{
  rock.write(rockUp);
  delay(moveTime);
  rock.write(rockStop);
  delay(pauseTime); // holds the chosen move for given delay
  rock.write(down_move);
  delay(moveTime);
  rock.write(rockStop);
}
void makeMovePaper()
{
  paper.write(paperUp);
  delay(moveTime);
  paper.write(paperStop);
  delay(pauseTime); // holds the chosen move for given delay
  paper.write(paperDown);
  delay(moveTime);
  paper.write(paperStop);
}
void makeMoveScissors()
{
  
}

void setup() 
{ 
  rock.attach(rockPin);  // attaches the servo on pin 9 to the servo object 
  paper.attach(paperPin);
  scissors.attach(scissorsPin);
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
  
  Serial.println("Choice (rock=0, paper=1, scissors=2):");
  while(!Serial.available()){} //halts program until input is received
  int choice = Serial.parseInt();
  
  Serial.println(choice, DEC); 
  if (choice == rockInt)
    return rockInt;
  else if (choice == paperInt)
    return paperInt;
  else if (choice == scissorsInt)
    return scissorsInt;
}
  
int whoWins(int user, int robot)
// return 0 for draw, 1 for user win, 2 for robot win
// return values may be changed later
{
  if (user == robot) // draw
    return drawInt;
  else if (user == rockInt){  // user played rock
    if (robot == scissorsInt)
      return userWinInt;
    else if (robot == paperInt)
      return botWinInt;
  }
  else if (user == paperInt){  // user played paper
    if (robot == rockInt)
      return userWinInt;
    else if (robot == scissorsInt)
      return botWinInt;
  }
  else if (user == scissorsInt){  // user played scissors
    if (robot == paperInt)
      return userWinInt;
    else if (robot == rockInt)
      return botWinInt;
  }
}

void updateScore(int winner)
// adds 1 to winner's score constant
{
  if (winner == userWinInt)
    ++userScore;
  else if (winner == botWinInt)
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
         
    rock.write(rockStop);
    paper.write(paperStop);
    
    int randomMove = random(0,3);
    if(randomMove == rockInt){
      makeMoveRock();
    }
    else if(randomMove == paperInt){
      makeMovePaper();
    }
//    else if(randomMove == scissorsInt){
//      makeMoveScissors();
//    }
    
    rock.write(rockStop);
    paper.write(paperStop);
    
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
