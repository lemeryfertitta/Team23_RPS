// TEAM 23 ROCK, PAPER, SCISSORS ROBOT

#include <Servo.h>
#include <IRremote.h>
#include <IRremoteInt.h>

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

// setup constants for SparkFun's IR Remote
const uint16_t BUTTON_POWER = 0xD827; // i.e. 0x10EFD827
const uint16_t BUTTON_A = 0xF807;
const uint16_t BUTTON_B = 0x7887;
const uint16_t BUTTON_C = 0x58A7;
const uint16_t BUTTON_UP = 0xA05F;
const uint16_t BUTTON_DOWN = 0x00FF;
const uint16_t BUTTON_LEFT = 0x10EF;
const uint16_t BUTTON_RIGHT = 0x807F;
const uint16_t BUTTON_CIRCLE = 0x20DF;

// Connect the output of the IR receiver diode to pin 11. CHANGE PIN #
int RECV_PIN = 6;
// Initialize the irrecv part of the IRremote  library
IRrecv irrecv(RECV_PIN);
decode_results results; // This will store our IR received codes
uint16_t lastCode = 0; // This keeps track of the last code RX'd

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
  irrecv.enableIRIn(); // Start the receiver
} 

int userInput()
// gets user input for move from IR remote
//maybe add this into a while loop? need to be tested
{
 if (irrecv.decode(&results)) 
  {
    // read the RX'd IR into a 16-bit variable
    uint16_t resultCode = (results.value & 0xFFFF);

    /* The remote will continue to spit out 0xFFFFFFFF if a 
     button is held down. If we get 0xFFFFFFF, let's just
     assume the previously pressed button is being held down */
    if (resultCode == 0xFFFF)
      resultCode = lastCode;
    else
      lastCode = resultCode;

    // This switch statement checks the received IR code against
    // all of the known codes. Each button press produces a 
    // serial output, and has an effect on the LED output.
    switch (resultCode)
    {
      case BUTTON_POWER:
        Serial.println("Power");
        break;
      case BUTTON_A:
        Serial.println("A");
        return rockInt;
        break;
      case BUTTON_B:
        Serial.println("B");
        return paperInt;
        break;
      case BUTTON_C:
        Serial.println("C");
        return scissorsInt;
        break;
      case BUTTON_CIRCLE:
        Serial.println("Circle");
        // maybe a wake up call?
        break;
      default:
        Serial.print("Unrecognized code received: 0x");
        Serial.println(results.value, HEX);
        break;        
    }    
    irrecv.resume(); // Receive the next value
  }
}

void clearIR()
//read IR results until it's clear;
{
  while (irrecv.decode(&results)) 
  {
    // read the RX'd IR into a 16-bit variable
    uint16_t resultCode = (results.value & 0xFFFF);
  }
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
    // accept user input only during countdown; clear IR codes received before
    clearIR();    
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
