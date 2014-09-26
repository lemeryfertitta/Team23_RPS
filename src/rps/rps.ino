// TEAM 23 ROCK, PAPER, SCISSORS ROBOT

#include <Servo.h> 

// pin declarations
int rockPin = 9;
int paperPin = 10;
int scissorsPin = 11;

int flexSensorMiddlePin = A0;
int flexSensorRingPin = A1;

// flex sensor calibration values
int flexLowerBound = 512;
int flexUpperBound = 614;

// the % value at which we determine a finger to be straight.
// anything less or equal will be considered a straight finger
int fingerStraight = 30; 

// Servo object declarations 
Servo rock;
Servo paper;
Servo scissors;
 
// Int representation for things like random() and userInput
int rockInt = 0;
int paperInt = 1;
int scissorsInt = 2;

int draw = 0;
int userWin = 1;
int botWin = 2;

// Values to control the speed of the continuous servos - use floats for percision
int upAngle = 45;
int downAngle = 0;

int moveTime = 500; // the amount of time (ms) to allow the servos to move up or down
int pauseTime = 1000; // the amount of time for the bot to hold up its chosen move

// track scores
int userScore;
int robotScore;
// CONST: max score for ending game; change to desired value
int maxScore = 5;

// the countdown function is the robots way of doing "Rock, Paper, Scissors"
void countdown()
{
  // move all arms down and up three times
  for(int i=0; i<3; i++){
     rock.write(downAngle);
     paper.write(downAngle);
     scissors.write(downAngle);
     delay(moveTime);
     rock.write(upAngle);
     paper.write(upAngle);
     scissors.write(upAngle);
     delay(moveTime);
  }
}
// the makeMove functions hold up the chosen move for pauseTime and then put the arm down
void makeMove(Servo armToMove)
{
  armToMove.write(downAngle);
  delay(moveTime);
  delay(pauseTime); // holds the chosen move for given delay
  armToMove.write(upAngle);
  delay(moveTime);
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
  int middleReading = analogRead(flexSensorMiddlePin);
  int ringReading = analogRead(flexSensorRingPin);
  int middleFinger = map(middleReading, flexLowerBound, flexUpperBound, 0, 100);
  int ringFinger = map(ringReading, flexLowerBound, flexUpperBound, 0, 100);

  if((ringFinger > fingerStraight) && (middleFinger > fingerStraight)){ return rockInt; }
  else if ((ringFinger <= fingerStraight) && (middleFinger <= fingerStraight)) { return paperInt; }
  else if ((ringFinger > fingerStraight) && (middleFinger <= fingerStraight)) { return scissorsInt; }
}
  
int whoWins(int user, int robot)
// return 0 for draw, 1 for user win, 2 for robot win
// return values may be changed later
{
  if (user == robot) // draw
    return draw;
  else if (user == rockInt){  // user played rock
    if (robot == scissorsInt)
      return userWin;
    else if (robot == paperInt)
      return botWin;
  }
  else if (user == paperInt){  // user played paper
    if (robot == rockInt)
      return userWin;
    else if (robot == scissorsInt)
      return botWin;
  }
  else if (user == scissorsInt){  // user played scissors
    if (robot == paperInt)
      return userWin;
    else if (robot == rockInt)
      return botWin;
  }
}

void updateScore(int winner)
// adds 1 to winner's score constant
{
  if (winner == userWin)
    ++userScore;
  else if (winner == botWin)
    ++robotScore;
}

boolean gameOver()
// checks if game is over
{
  if (userScore == maxScore || robotScore == maxScore)
    return true;
  else
    return false;
}

void loop()
{   
    countdown();
    
    int userMove = userInput();
    
    int botMove = random(0,3);
    if(botMove == rockInt){ makeMove(rock); }
    else if(botMove == paperInt){ makeMove(paper); }
    else if(botMove == scissorsInt){ makeMove(scissors); }
    
   int winner = whoWins(userMove, botMove);
   updateScore(winner);
   if (gameOver()){
     // do something?
   }
} 
