// TEAM 23 ROCK, PAPER, SCISSORS ROBOT

#include <Servo.h> 
#include <LiquidCrystal.h>

// pin declarations
int rockPin = 8;
int paperPin = 9;
int scissorsPin = 10;

int flexSensorMiddlePin = A1;
int flexSensorRingPin = A2;

// flex sensor calibration values
int flexMiddleLowerBound = 250;
int flexMiddleUpperBound = 450;
int flexRingLowerBound   = 360;
int flexRingUpperBound   = 490;

// the % value at which we determine a finger to be straight.
// anything less or equal will be considered a straight finger
int fingerStraight = 30; 
//>>>>>>> flexSensor

// Servo object declarations 
Servo rock;
Servo paper;
Servo scissors;

//initialize library with numbers of interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
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
int userScore = 0;
int robotScore = 0;
// CONST: max score for ending game; change to desired value
int maxScore = 7;

int userMove = 0;
int botMove = 0; 

boolean cheating = true;

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

void updateLCD()
{
  String line1 = "User: " + String(userScore);
  String line2 = "Robot: " + String(robotScore);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

int userInput()
// gets user input for move
// can be changed later for input from buttons; uses serial monitor for now
{
  int middleReading = analogRead(flexSensorMiddlePin);
  int ringReading = analogRead(flexSensorRingPin);
  int middleFinger = map(middleReading, flexMiddleLowerBound, flexMiddleUpperBound, 0, 100);
  int ringFinger = map(ringReading, flexRingLowerBound, flexRingUpperBound, 0, 100);

  if((ringFinger < fingerStraight) && (middleFinger < fingerStraight))
  { 
    return rockInt;
  }
  else if ((ringFinger >= fingerStraight) && (middleFinger >= fingerStraight)) 
  { 
    return paperInt; 
  }
  else if ((ringFinger < fingerStraight) && (middleFinger >= fingerStraight))
 { 
   return scissorsInt; 
 }
}
  
int whoWins(int user, int robot)
// return 0 for draw, 1 for user win, 2 for robot win
// return values may be changed later
{
  if (user == ((robot+1)%3)){
    return userWin;
  }
  else if (robot == ((user+1)%3)){
    return botWin;
  }
  else{
   return draw; 
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

void printWinner()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  if (userScore == maxScore)
  {
    String toPrint = "You Win!";
    lcd.print(toPrint);
  }  
  else
  {
    String toPrint = "You Lose! You Suck!";
    lcd.print(toPrint);  
  }
}

void setup() 
{ 
  lcd.begin(16, 2);
  rock.attach(rockPin);  // attaches the servo on pin 9 to the servo object 
  paper.attach(paperPin);
  scissors.attach(scissorsPin);
  Serial.begin(9600);
  updateLCD();
}

void loop()
{   
    countdown();
    userMove = userInput();
    
    if(cheating == true){
      botMove = (userMove+1)%3;
    }
    else {
      botMove = random(0,3);
    }
    
    if(botMove == rockInt){ makeMove(rock); }
    else if(botMove == paperInt){ makeMove(paper); }
    else if(botMove == scissorsInt){ makeMove(scissors); }
    
    int winner = whoWins(userMove, botMove);
    updateScore(winner);
    updateLCD();
    if (gameOver()){
      printWinner();
   }
} 
