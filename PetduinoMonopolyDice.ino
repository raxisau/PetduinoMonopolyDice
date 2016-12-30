#include <LedControl.h>
#include <Petduino.h>

#define INTRO_ANIM_FRAMES 8
byte introF[INTRO_ANIM_FRAMES][8]={
  { // Frame 1
    B10000100,
    B10000100,
    B00000000,
    B00010000,
    B00001000,
    B10000100,
    B10000100,
    B00000000
    },
  { // Frame 2
    B00000000,
    B10000100,
    B10000100,
    B00001000,
    B00010000,
    B00000000,
    B10000100,
    B10000100
    },
  { // Frame 3
    B00000000,
    B00000000,
    B11000110,
    B00010000,
    B00001000,
    B00000000,
    B00000000,
    B11000110
    },
  { // Frame 4
    B00000000,
    B00000000,
    B01100011,
    B00001000,
    B00010000,
    B00000000,
    B00000000,
    B01100011
    },
  { // Frame 5
    B00000000,
    B00100001,
    B00100001,
    B00010000,
    B00001000,
    B00000000,
    B00100001,
    B00100001
    },
  { // Frame 6
    B00100001,
    B00100001,
    B00000000,
    B00001000,
    B00010000,
    B00100001,
    B00100001,
    B00000000
    },
  { // Frame 7
    B01100011,
    B00000000,
    B00000000,
    B00010000,
    B00001000,
    B01100011,
    B00000000,
    B00000000
    },
  { // Frame 8
    B11000110,
    B00000000,
    B00000000,
    B00001000,
    B00010000,
    B11000110,
    B00000000,
    B00000000
    }
};
unsigned long introD[INTRO_ANIM_FRAMES]  = { 100, 100, 100, 100, 100, 100, 100, 100 };

long dice1       = 1;
long dice2       = 1;
long dice3       = 1;
int  spinStarted = 0;

#define INTRO_STATE 0
#define SPIN_STATE  1

Petduino pet = Petduino();

void setup() {

  // Setup Petduino
  pet.begin();

  // Set initial state
  pet.setState( INTRO_STATE );
  
  // Initialize random seed
  randomSeed( analogRead( 0 ) );

  dice1 = random( 1, 7 );
  dice2 = random( 1, 7 );
  dice3 = random( 1, 7 );
}

void loop() {
  pet.update();
  
  if ( pet.isBtn1Pressed() || pet.isBtn2Pressed() ) {
    spinStarted = 0;
    pet.stopAnimation();
    pet.setState( SPIN_STATE );
  }
    
  switch( pet.getState() ) {
    case INTRO_STATE:
    
      // Show intro anim
      spinStarted = 0;
      pet.playAnimation( introF, introD, INTRO_ANIM_FRAMES, 1 );
      pet.setNextState( INTRO_STATE, INTRO_ANIM_FRAMES * 100 );
      break;
      
    case SPIN_STATE:
      if ( ! spinStarted ) {
        dice1 = random( 1, 7 );
        dice2 = random( 1, 7 );
        dice3 = random( 1, 7 );
        spinStarted = 1;
      }
      
      drawDice( dice1, dice2, dice3 );
      pet.setNextState( INTRO_STATE, 30000 );
      break;
  }
}

int drawDice( long dice1, long dice2, long dice3 ) {
  
  byte screen[8] = { 0, 0, 0, 0, 0, 0, 0 };
  pet.drawImage( screen );
  
  switch ( dice1 ) {
    case 1:
      screen[0] |= B00000000;
      screen[1] |= B01000000;
      screen[2] |= B00000000;
    break;
    case 2:
      screen[0] |= B10000000;
      screen[1] |= B00000000;
      screen[2] |= B00100000;
    break;
    case 3:
      screen[0] |= B00100000;
      screen[1] |= B01000000;
      screen[2] |= B10000000;
    break;
    case 4:
      screen[0] |= B10100000;
      screen[1] |= B00000000;
      screen[2] |= B10100000;
    break;
    case 5:
      screen[0] |= B10100000;
      screen[1] |= B01000000;
      screen[2] |= B10100000;
    break;
    case 6:
      screen[0] |= B10100000;
      screen[1] |= B10100000;
      screen[2] |= B10100000;
    break;
  }
    
  switch ( dice2 ) {
    case 1:
      screen[0] |= B00000000;
      screen[1] |= B00000010;
      screen[2] |= B00000000;
    break;               
    case 2:              
      screen[0] |= B00000100;
      screen[1] |= B00000000;
      screen[2] |= B00000001;
    break;               
    case 3:              
      screen[0] |= B00000001;
      screen[1] |= B00000010;
      screen[2] |= B00000100;
    break;               
    case 4:              
      screen[0] |= B00000101;
      screen[1] |= B00000000;
      screen[2] |= B00000101;
    break;               
    case 5:              
      screen[0] |= B00000101;
      screen[1] |= B00000010;
      screen[2] |= B00000101;
    break;               
    case 6:              
      screen[0] |= B00000101;
      screen[1] |= B00000101;
      screen[2] |= B00000101;
    break;
  }
  
  switch ( dice3 ) {
    case 1:
      screen[5] |= B00000000;
      screen[6] |= B01000000;
      screen[7] |= B00000000;
    break;
    case 2:
      screen[5] |= B10000000;
      screen[6] |= B00000000;
      screen[7] |= B00100000;
    break;
    case 3:
      screen[5] |= B00100000;
      screen[6] |= B01000000;
      screen[7] |= B10000000;
    break;
    case 4:
    case 5:
      screen[3] |= B00001000;
      screen[4] |= B00111110;
      screen[5] |= B00001000;
      screen[6] |= B00010100;
      screen[7] |= B00100010;
    break;
    case 6:
      screen[3] |= B00000000;
      screen[4] |= B00111110;
      screen[5] |= B01001010;
      screen[6] |= B01111110;
      screen[7] |= B00100010;
    break;
  }
  
  pet.drawImage( screen );
}

