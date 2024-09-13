// Lab9Main.c
// Runs on MSPM0G3507
// Lab 9 ECE319K
// RayCaster uses code from https://lodev.org/cgtutor/raycasting.html created by Lode Vandevenne
// The Raycaster program is modified to work with fixed-point integers and has it's own unique way of outputting to display
// Jerin Andrews and William Wang
// Last Modified: 04/23/2023

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // I added this!!!
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC1.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"
#include "sounds/WavSounds.h"

//#include <math.h> // I added this

// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}


// ******************************* UNCOMMENT THIS LATER *************************************//
// games  engine runs at 30Hz
//void TIMG12_IRQHandler(void){uint32_t pos,msg;
//  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
//    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//// game engine goes here
//    // 1) sample slide pot
//    // 2) read input switches
//    // 3) move sprites
//    // 4) start sounds
//    // 5) set semaphore
//    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
//    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//  }
//}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

////typedef enum {English, Spanish, Portuguese, French} Language_t;
////Language_t myLanguage=English;
//typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
//const char Hello_English[] ="Hello";
//const char Hello_Spanish[] ="\xADHola!";
//const char Hello_Portuguese[] = "Ol\xA0";
//const char Hello_French[] ="All\x83";
//const char Goodbye_English[]="Goodbye";
//const char Goodbye_Spanish[]="Adi\xA2s";
//const char Goodbye_Portuguese[] = "Tchau";
//const char Goodbye_French[] = "Au revoir";
//const char Language_English[]="English";
//const char Language_Spanish[]="Espa\xA4ol";
//const char Language_Portuguese[]="Portugu\x88s";
//const char Language_French[]="Fran\x87" "ais";
//const char *Phrases[3][4]={
//  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
//  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
//  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
//};
//// use main1 to observe special characters
//int main1(void){ // main1
//    char l;
//  __disable_irq();
//  PLL_Init(); // set bus speed
//  LaunchPad_Init();
//  ST7735_InitPrintf();
//  ST7735_FillScreen(0x0000);            // set screen to black
//  for(phrase_t myPhrase=HELLO; myPhrase<= GOODBYE; myPhrase++){
//    for(Language_t myL=English; myL<= French; myL++){
//         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
//      ST7735_OutChar(' ');
//         ST7735_OutString((char *)Phrases[myPhrase][myL]);
//      ST7735_OutChar(13);
//    }
//  }
//  Clock_Delay1ms(3000);
//  ST7735_FillScreen(0x0000);       // set screen to black
//  l = 128;
//  while(1){
//    Clock_Delay1ms(2000);
//    for(int j=0; j < 3; j++){
//      for(int i=0;i<16;i++){
//        ST7735_SetCursor(7*j+0,i);
//        ST7735_OutUDec(l);
//        ST7735_OutChar(' ');
//        ST7735_OutChar(' ');
//        ST7735_SetCursor(7*j+4,i);
//        ST7735_OutChar(l);
//        l++;
//      }
//    }
//  }
//}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
//  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
//  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
//  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
//  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
//  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
//  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
//  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
//  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
//  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
//  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString("Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString("Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs
    
  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    if((last == 0)&&(now == 1)){
      Sound_Shoot(); // call one of your sounds
    }
    if((last == 0)&&(now == 2)){
      Sound_Killed(); // call one of your sounds
    }
    if((last == 0)&&(now == 4)){
      Sound_Explosion(); // call one of your sounds
    }
    if((last == 0)&&(now == 8)){
      Sound_Fastinvader1(); // call one of your sounds
    }
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int mainF(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ADCinit();     //PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
    // initialize interrupts on TimerG12 at 30 Hz
  TimerG12_IntArm(80000000/30,2);
  // initialize all data structures
  __enable_irq();

  while(1){
    // wait for semaphore
       // clear semaphore
       // update ST7735R
    // check for end game or level switch
  }
}


// games  engine runs at 30Hz
//void TIMG12_IRQHandler(void){uint32_t pos,msg;
//  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
//    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//// game engine goes here
//    // 1) sample slide pot
//    // 2) read input switches
//    // 3) move sprites
//    // 4) start sounds
//    // 5) set semaphore
//    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
//    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
//  }
//}

//uint32_t startTime,stopTime, Offset;
//double frameTime;
//uint32_t curr_key;
//int cameraX;
//int planeX, planeY, rayDirX, rayDirY;
//int dirX, dirY;
//int deltaDistX, deltaDistY, perpWallDist;
//int sideDistX, sideDistY;
//int side;
//
//int lineHeight;

////int check1, check2;
//
//// Fixed Point Raycaster
//int mainFixedPoint(void){
//  Clock_Init80MHz(0);
//  LaunchPad_Init();
//  ST7735_InitR(INITR_REDTAB);
//  ST7735_FillScreen(ST7735_BLACK);
//
//  Switch_Init(); // initialize switches
//
//    int worldMap[24][24]=
//    {
//      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,4,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,0,0,0,5,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,4,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//    };
//
//    posX = 22*10000, posY = 12*10000;  //x and y start position
//    dirX = -1*10000, dirY = 0; //initial direction vector
//    planeX = 0, planeY = 6600;//0.66; //the 2d raycaster version of camera plane
//
//    //TimerG12_IntArm(80000000/30,2);
//
//    while(1){
//        for(int x = 0; x < screenWidth; x++)
//        {
//            //calculate ray position and direction
////            int32_t cameraX = ((10000 * 2 * x ) /  screenWidth) - 10000; //x-coordinate in camera space
////            int rayDirX = dirX + planeX * cameraX;
////            rayDirX = ((rayDirX == 1) || rayDirX == -1) ? rayDirX*10000 : rayDirX;
////            int rayDirY = dirY + planeY * cameraX;
//
////            cameraX = 2 * x / (double) screenWidth - 1;
////            rayDirX = dirX + ((planeX * cameraX));
////            rayDirY = dirY + ((planeY * cameraX));
//
//            cameraX = ((2*x*10000)/screenWidth) - 10000;
//            rayDirX = dirX + ((planeX * cameraX)/10000);
//            rayDirY = dirY + ((planeY * cameraX)/10000);
//
//
//
//            //which box of the map we're in
//            int mapX = (int) posX/10000;
//            int mapY = (int) posY/10000;
//
//            //length of ray from current position to next x or y-side
////            sideDistX;
////            sideDistY;
////            int sideDistX;
////            int sideDistY;
//
//            //length of ray from one x or y-side to next x or y-side
////            deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
////            deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//            //perpWallDist;
//
//            //Fixed Point Method
//            deltaDistX = (rayDirX == 0) ? 0x7FFFFFFF : abs((10000*100000)/rayDirX);
//            deltaDistY = (rayDirY == 0) ? 0x7FFFFFFF : abs((10000*100000)/rayDirY);
//
////            int deltaDistX = (rayDirX == 0) ? 0x7FFFFFFF : abs(10000*1000 / rayDirX);
////            int deltaDistY = (rayDirY == 0) ? 0x7FFFFFFF : abs(10000*1000 / rayDirY);
////            int perpWallDist;
//
//            //what direction to step in x or y-direction (either +1 or -1)
//            int stepX;
//            int stepY;
//
//            int hit = 0; //was there a wall hit?
//            //side; //was a NS or a EW wall hit?
//
//            //calculate step and initial sideDist
//            if (rayDirX < 0)
//            {
//                stepX = -1;
//                sideDistX = (posX - mapX*10000)/10000 * deltaDistX;
//            }
//            else
//            {
//                stepX = 1;
//                sideDistX = (mapX*10000 + 10000 - posX)/10000 * deltaDistX;
//            }
//            if (rayDirY < 0)
//            {
//                stepY = -1;
//                sideDistY = (posY - mapY*10000)/10000 * deltaDistY;
//            }
//            else
//            {
//                stepY = 1;
//                sideDistY = (mapY*10000 + 10000 - posY)/10000 * deltaDistY;
//            }
//
//            //perform DDA
//            while(hit == 0)
//            {
//                //jump to next map square, either in x-direction, or in y-direction
//                if(sideDistX < sideDistY)
//                {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//                }
//                else
//                {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//                }
//                //Check if ray has hit a wall
//                if(worldMap[mapX][mapY] > 0) hit = 1;
//            }
//
//            //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//            if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//            else          perpWallDist = (sideDistY - deltaDistY);
//
//            //Calculate height of line to draw on screen
////            lineHeight = (int)(screenHeight / perpWallDist);
//
//            //Fixzed Point Line Height
//            lineHeight = (screenHeight * 100000) / perpWallDist;
//
//             //calculate lowest and highest pixel to fill in current stripe
//             int drawStart = -lineHeight / 2 + screenHeight / 2;
//             if(drawStart < 0) drawStart = 0;
//             int drawEnd = lineHeight / 2 + screenHeight / 2;
//             if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;
//
//             uint8_t r, g, b;
////             switch(worldMap[mapX][mapY])
////             {
////               case 1:  r = 255; g = 0; b = 0; if(side==1) {r/=2;}  break; //red
////               case 2:  r = 0; g = 255; b = 0; if(side==1) {g/=2;} break; //green
////               case 3:  r = 0; g = 0; b = 255; if(side==1) {b/=2;}  break; //blue
////               case 4:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
////               default: r = 255; g = 255; b = 0; if(side==1) {r/=2; g/=2;} break; //yellow
////             }
//
//             switch(worldMap[mapX][mapY])
//             {
//               case 1:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               case 2:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               case 3:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               case 4:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               default: r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//             }
//
//             //give x and y sides different brightness
//             //if (side == 1) {color = color / 2;}
//
//             ST7735_DrawFastVLine(x, drawStart, drawEnd-drawStart, ST7735_Color565(r, g, b));
//        }
//
//        //timing for input and FPS counter
////        stopTime = SysTick->VAL;
////        frameTime = ((((startTime-stopTime)&0x0FFFFFF)-Offset)*pow(12.5, -9)); //frameTime is the time this frame has taken, in seconds
//
//        //speed modifiers
//        int moveSpeed = 1; //the constant value is in squares/second
//        int rotSpeed = 1; //the constant value is in radians/second
//
//        Clock_Delay(4000000); // 0.5ms -> 40,000 (I think)
//        ST7735_FillScreen(ST7735_BLACK);
//
//        curr_key = Switch_In();
//
//        // forward
//        if (curr_key == 2) {
//            //(posX + dirX) < mapWidth) &
////            check1 = (posX*10000 + (dirX * moveSpeed))/10000;
//            if(worldMap[((posX + (dirX/2 * moveSpeed))/10000 + 1)][(posY/10000)] == 0) {
//                posX = (posX + (dirX/2 * moveSpeed));
//            }
//
//            //((posX + dirX) < mapHeight) &
////            check2 = (posY*10000 + (dirY * moveSpeed))/10000;
//            if(worldMap[(posX/10000)][((posY + (dirY/2 * moveSpeed + 1))/10000)] == 0) {
//                posY = (posY + (dirY/2 * moveSpeed));
//            }
//
//            // Write edge cases for going off screen
//        }
//
//        // backward
//        if (curr_key == 4) {
//            // ((posX + dirX) > 0) &
//            if(worldMap[((posX - (dirX/2 * moveSpeed))/10000 - 1)][(posY/10000)] == 0) {
//                posX = (posX- (dirX/2 * moveSpeed));
//            }
//
//            //((posY + dirY) > 0) &
//            if(worldMap[(posX/10000)][((posY - (dirY/2 * moveSpeed))/10000 - 1)] == 0) {
//                posY = (posY - (dirY/2 * moveSpeed));
//            }
//            // Write edge cases for going off screen
//        }
//
//        // right
//        if (curr_key == 8) {
//            //both camera direction and camera plane must be rotated
//            int oldDirX = dirX;
////            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
////            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//
//            // Fixed Point Sol
//            dirX = ((dirX*5403)/10000) - ((dirY * -8414)/10000);
//            dirY = ((oldDirX*-8414)/10000) + ((dirY*5403)/10000);
//
//            int oldPlaneX = planeX;
////            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
////            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//
//            //Fixed Point Sol
//            planeX = ((planeX * 5403)/10000) - ((planeY * -8414)/10000);
//            planeY = ((oldPlaneX * -8414)/10000) + ((planeY * 5403)/10000);
//        }
//
//        // left
//        if (curr_key == 1) {
//            int oldDirX = dirX;
////            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
////            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//
//            // Fixed Point Sol
//            dirX = ((dirX*5403)/10000) - ((dirY * 8414)/10000);
//            dirY = ((oldDirX*8414)/10000) + ((dirY*5403)/10000);
//
//            int oldPlaneX = planeX;
////            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
////            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//
//            //Fixed Point Sol
//            planeX = ((planeX * 5403)/10000) - ((planeY * 8414)/10000);
//            planeY = ((oldPlaneX * 8414)/10000) + ((planeY * 5403)/10000);
//        }
//    }
//}

//double cameraX;
//double planeX, planeY, rayDirX, rayDirY;
//double posX, posY;
//double dirX, dirY;
//double deltaDistX, deltaDistY, perpWallDist;
//double sideDistX, sideDistY;
////
//// Floating Point RayCaster
//int main(void){
//  Clock_Init80MHz(0);
//  LaunchPad_Init();
//  ST7735_InitR(INITR_REDTAB);
//  ST7735_FillScreen(ST7735_BLACK);
//
//  Switch_Init(); // initialize switches
//
//    int worldMap[mapWidth][mapHeight]=
//    {
//      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//      {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//    };
//
//    posX = 22, posY = 12;  //x and y start position
//    dirX = -1/**10000*/, dirY = 0; //initial direction vector
//    planeX = 0, planeY = 0.66;//6600;//0.66; //the 2d raycaster version of camera plane
//
//    //TimerG12_IntArm(80000000/30,2);
//
//    while(1){
//        for(int x = 0; x < screenWidth; x++)
//        {
//            //calculate ray position and direction
////            int32_t cameraX = ((10000 * 2 * x ) /  screenWidth) - 10000; //x-coordinate in camera space
////            int rayDirX = dirX + planeX * cameraX;
////            rayDirX = ((rayDirX == 1) || rayDirX == -1) ? rayDirX*10000 : rayDirX;
////            int rayDirY = dirY + planeY * cameraX;
//
//            cameraX = 2 * x / (double) screenWidth - 1;
//            rayDirX = dirX + ((planeX * cameraX));
//            rayDirY = dirY + ((planeY * cameraX));
//
////            cameraX = ((2*x*10000)/screenWidth) - 10000;
////            rayDirX = dirX + ((planeX * cameraX)/10000);
////            rayDirY = dirY + ((planeY * cameraX)/10000);
//
//
//
//            //which box of the map we're in
//            int mapX = (int) posX;
//            int mapY = (int) posY;
//
//            //length of ray from current position to next x or y-side
////            sideDistX;
////            sideDistY;
////            int sideDistX;
////            int sideDistY;
//
//            //length of ray from one x or y-side to next x or y-side
//            deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//            deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//            //perpWallDist;
//
//            //Fixed Point Method
////            deltaDistX = (rayDirX == 0) ? 0x7FFFFFFF : abs((10000*100000)/rayDirX);
////            deltaDistY = (rayDirY == 0) ? 0x7FFFFFFF : abs((10000*100000)/rayDirY);
//
////            int deltaDistX = (rayDirX == 0) ? 0x7FFFFFFF : abs(10000*1000 / rayDirX);
////            int deltaDistY = (rayDirY == 0) ? 0x7FFFFFFF : abs(10000*1000 / rayDirY);
////            int perpWallDist;
//
//            //what direction to step in x or y-direction (either +1 or -1)
//            int stepX;
//            int stepY;
//
//            int hit = 0; //was there a wall hit?
//            int side; //was a NS or a EW wall hit?
//
//            //calculate step and initial sideDist
//            if (rayDirX < 0)
//            {
//                stepX = -1;
//                sideDistX = (posX - mapX) * deltaDistX;
//            }
//            else
//            {
//                stepX = 1;
//                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//            }
//            if (rayDirY < 0)
//            {
//                stepY = -1;
//                sideDistY = (posY - mapY) * deltaDistY;
//            }
//            else
//            {
//                stepY = 1;
//                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//            }
//
//            //perform DDA
//            while(hit == 0)
//            {
//                //jump to next map square, either in x-direction, or in y-direction
//                if(sideDistX < sideDistY)
//                {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//                }
//                else
//                {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//                }
//                //Check if ray has hit a wall
//                if(worldMap[mapX][mapY] > 0) hit = 1;
//            }
//
//            //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//            if(side == 0) perpWallDist = (sideDistX - deltaDistX);
//            else          perpWallDist = (sideDistY - deltaDistY);
//
//            //Calculate height of line to draw on screen
//            lineHeight = (int)(screenHeight / perpWallDist);
//
//            //Fixzed Point Line Height
//            //lineHeight = (screenHeight * 100000) / perpWallDist;
//
//             //calculate lowest and highest pixel to fill in current stripe
//             int drawStart = -lineHeight / 2 + screenHeight / 2;
//             if(drawStart < 0) drawStart = 0;
//             int drawEnd = lineHeight / 2 + screenHeight / 2;
//             if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;
//
//             uint8_t r, g, b;
////             switch(worldMap[mapX][mapY])
////             {
////               case 1:  r = 255; g = 0; b = 0; if(side==1) {r/=2;}  break; //red
////               case 2:  r = 0; g = 255; b = 0; if(side==1) {g/=2;} break; //green
////               case 3:  r = 0; g = 0; b = 255; if(side==1) {b/=2;}  break; //blue
////               case 4:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
////               default: r = 255; g = 255; b = 0; if(side==1) {r/=2; g/=2;} break; //yellow
////             }
//
//             switch(worldMap[mapX][mapY])
//             {
//               case 1:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               case 2:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               case 3:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               case 4:  r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//               default: r = 255; g = 255; b = 255; if(side==1) {r/=2; g/=2; b/=2;} break; //white
//             }
//
//             //give x and y sides different brightness
//             //if (side == 1) {color = color / 2;}
//
//             ST7735_DrawFastVLine(x, drawStart, drawEnd-drawStart, ST7735_Color565(r, g, b));
//        }
//
//        //timing for input and FPS counter
////        stopTime = SysTick->VAL;
////        frameTime = ((((startTime-stopTime)&0x0FFFFFF)-Offset)*pow(12.5, -9)); //frameTime is the time this frame has taken, in seconds
//
//        //speed modifiers
//        double moveSpeed = 1; //the constant value is in squares/second
//        double rotSpeed = 1; //the constant value is in radians/second
//
//        Clock_Delay(4000000); // 0.5ms -> 40,000 (I think)
//        ST7735_FillScreen(ST7735_BLACK);
//
//        curr_key = Switch_In();
//
//        // forward
//        if (curr_key == 2) {
//            //(posX + dirX) < mapWidth) &
////            check1 = (posX*10000 + (dirX * moveSpeed))/10000;
////            if(worldMap[((posX*10000 + (dirX * moveSpeed))/10000)][posY] == false) {
////                posX = (posX*10000 + (dirX * moveSpeed))/10000;
////            }
//
//            if(worldMap[(int)((posX+ (dirX * moveSpeed)))][(int)posY] == false) {
//                posX = posX + (dirX * moveSpeed);
//            }
//
//            //((posX + dirX) < mapHeight) &
////            check2 = (posY*10000 + (dirY * moveSpeed))/10000;
////            if(worldMap[posX][((posY*10000 + (dirY * moveSpeed))/10000)] == false) {
////                posY = (posY*10000 + (dirY * moveSpeed))/10000;
////            }
//
//            if(worldMap[(int) posX][(int)(posY + (dirY * moveSpeed))] == false) {
//                posY = (posY+ (dirY * moveSpeed));
//            }
//            // Write edge cases for going off screen
//        }
//
//        // backward
//        if (curr_key == 4) {
//            // ((posX + dirX) > 0) &
////            if(worldMap[((posX*10000 - (dirX * moveSpeed))/10000)-1][(posY)] == false) {
////                posX = (posX * 10000 - (dirX * moveSpeed))/10000;
////            }
//
//            if(worldMap[(int) (posX - (dirX * moveSpeed))][(int) (posY)] == false) {
//                posX = (posX - (dirX * moveSpeed));
//            }
//            //((posY + dirY) > 0) &
//            if(worldMap[(int) (posX)][(int) (posY - (dirY * moveSpeed))] == false) {
//                posY = (posY - (dirY * moveSpeed));
//            }
//            // Write edge cases for going off screen
//        }
//
//        // right
//        if (curr_key == 8) {
//            //both camera direction and camera plane must be rotated
//            double oldDirX = dirX;
//            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//
//            // Fixed Point Sol
////            dirX = ((dirX*5403)/10000) - ((dirY * -8414)/10000);
////            dirY = ((oldDirX*-8414)/10000) + ((dirY*5403)/10000);
//
//            double oldPlaneX = planeX;
//            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//
//            //Fixed Point Sol
////            planeX = ((planeX * 5403)/10000) - ((planeY * -8414)/10000);
////            planeY = ((oldPlaneX * -8414)/10000) + ((planeY * 5403)/10000);
//        }
//
//        // left
//        if (curr_key == 1) {
//            double oldDirX = dirX;
//            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
////            dirX = ((dirX*5403)/10000) - ((dirY * 8414)/10000);
////            dirY = ((oldDirX*8414)/10000) + ((dirY*5403)/10000);
//
//            // Fixed Point Sol
//
//            double oldPlaneX = planeX;
//            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//
//            //Fixed Point Sol
////            planeX = ((planeX * 5403)/10000) - ((planeY * 8414)/10000);
////            planeY = ((oldPlaneX * 8414)/10000) + ((planeY * 5403)/10000);
//        }
//    }
//}


// Constants
#define mapWidth 41
#define mapHeight 37
#define screenHeight 160
#define screenWidth 128


const uint8_t worldMap0[mapWidth][mapHeight]=
{
 {1,1,6,6,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const uint8_t worldMap1[mapWidth][mapHeight] =
{
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1},
 {6,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1},
 {6,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1},
 {6,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {6,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
 {1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,7},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const uint8_t worldMap2[41][37]=
{
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


// Dynamic Arm Buffer
// Arm Starts drawing at 69, 160 (x, y) on screen
uint8_t armWidth = 59;
uint8_t armHeight = 38;
uint16_t armBuffer[38][59];
uint16_t armOverlay[2242];
uint8_t handShift = 0;

// Slice and Buffer Declaration
struct slice {
    uint32_t dist;
    uint8_t dStart;
    uint8_t dEnd;
    uint8_t s;
    uint8_t exit;
};
typedef struct slice slice_t;

slice_t sliceBuffer[128];

int posX, posY;
//int cameraX;
int planeX, planeY;//, rayDirX, rayDirY;
int dirX, dirY;
//int deltaDistX, deltaDistY, perpWallDist;
//int sideDistX, sideDistY;
//int side;
//
//int lineHeight;

uint8_t gameFlag = 0;
uint8_t drawFlag = 0;
uint8_t soundEnFlag = 0;

uint32_t inp;
uint32_t moveSpeed = 1;
int32_t adcSamp = 0;
int32_t rotInp = 0;

uint32_t exitDist;
uint32_t gameTimer = 3600; // Can be scaled based on ISR timing

//Animations and Sprites
struct bitmap {
    uint32_t x;
    uint32_t imageSize;
    const uint16_t *imagePtr;
}; typedef struct bitmap bitmap_t;

const bitmap_t Heart[6] = {
                           {21, 210, biggestheart},
                           {19, 210, bigheart},
                           {21, 210, smallheart},
                           {19, 210, smallestheart},
                           {21, 210, smallheart},
                           {19, 210, bigheart}};
const bitmap_t Warning[6] = {
                             {3, 210, warningmostopaque},
                             {1, 210, warningopaque},
                             {3, 210, warningdark},
                             {1, 210, warningdarkest},
                             {3, 210, warningdark},
                             {1, 210, warningopaque}};

const uint16_t *currentheart;
const uint16_t *currentwarning;
uint8_t i = 0, heartx = 20, warningx = 2;

uint8_t noScares = 1;
uint8_t scareDist;

// Starting Properties
typedef enum {English, French} language_t;
const uint8_t (*currWorldMap)[mapHeight];
uint8_t level1, level2, level3;
uint16_t score1, score2, score3, score;

// Level 1
uint8_t exit1_X = 4;
uint8_t exit1_Y = 36;

// Level 2
uint8_t exit2_X = 37;
uint8_t exit2_Y = 36;

uint8_t scare2X = 12;
uint8_t scare2Y = 9;

// Level 3
uint8_t exit3_X = 3;
uint8_t exit3_Y = 36;

uint8_t scare3X = 4;
uint8_t scare3Y = 20;

// Game Over
uint8_t win = 0;

void ADCConvert(int32_t n) {
    //rotInp = (128*n)/4096;
    rotInp = (256*(n-2048))/2048;
}

// Buffer Clear Helper Function
//void BufferClear(uint16_t arr[], uint32_t size) {
//    for (uint32_t b = 0; b < size; b++) {
//        arr[b] = 0;
//    }
//}

// Testing using 30 Hz Game Engine instead of main loop
// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    //Update Game Timer
    if (gameFlag) {
        gameTimer--;
    }
    // 1) sample slide pot
    adcSamp = ADCin();
    // 2) read input switches
    inp = (GPIOB->DIN31_0 & (3<<16)) >> 16;
    // 3) move sprites and animations
    // Hand Animation
    if(gameTimer % 2 == 0) {
        handShift++;
    } else {
        handShift = 0;
    }

    // Heart and Warning Animations
    if((gameTimer >= 0) && (gameTimer < 720)){
            currentheart = Heart[i].imagePtr;
            currentwarning = Warning[i].imagePtr;
            i++;
            if(i == 6){
                i = 0;
            }
        }
        if((gameTimer >= 720) && (gameTimer < 1440)){
            currentheart = Heart[i].imagePtr;
            currentwarning = Warning[i].imagePtr;
            if((gameTimer % 2) == 0){
                i++;
            }
            if(i == 6){
                i = 0;
            }
        }
        if((gameTimer >= 1440) && (gameTimer < 2160)){
            currentheart = Heart[i].imagePtr;
            currentwarning = Warning[i].imagePtr;
            if((gameTimer % 3) == 0){
                i++;
            }
            if(i == 6){
                i = 0;
            }
        }
        if((gameTimer >= 2160) && (gameTimer < 2880)){
            currentheart = Heart[i].imagePtr;
            currentwarning = Warning[i].imagePtr;
            if((gameTimer % 4) == 0){
                i++;
            }
            if(i == 6){
                i = 0;
            }
        }
        if((gameTimer >= 2880) && (gameTimer < 3600)){
            currentheart = Heart[i].imagePtr;
            currentwarning = Warning[i].imagePtr;
            if((gameTimer % 5) == 0){
                i++;
            }
            if(i == 6){
                i = 0;
            }
     }

    // 4) start sounds
    if (soundEnFlag & (inp != 0)) {
        Sound_Start(walking2, 8796, 80000000/110000);
    }

    // Testing constant movement
//    posY += 10000;
//    if (posY >= 230000) {
//        posY = 20000;
//    }

    // 5) set semaphore(s)
    drawFlag = 1;

    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}


// 30 Hz Game Engine Test
int main(void){
    __disable_irq();
    Clock_Init80MHz(0);
    LaunchPad_Init();
    ST7735_InitR(INITR_REDTAB);
    ST7735_FillScreen(ST7735_BLACK);

    Switch_Init(); // initialize switches
    ADCinit();
    Sound_Init();

    soundEnFlag = 1;

    // Starting Game Initialization
    posX = 3*10000, posY = 3*10000;  //x and y start position
    dirX = -1*10000, dirY = 0*10000; //initial direction vector
    planeX = 0, planeY = 6600;//0.66; //the 2d raycaster version of camera plane
    language_t currLanguage = English;

    currWorldMap = worldMap0;
    level1 = 0;
    level2 = 0;
    level3 = 0;

    score1 = 0;
    score2 = 0;
    score3 = 0;

    TimerG12_IntArm(80000000/20,2);
    __enable_irq();

    while (gameFlag == 0) {
      if (currLanguage == English) {
          ST7735_DrawChar(5, 20, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(17, 20, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(23, 20, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(35, 20, 'S', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(47, 20, 'C', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(59, 20, 'A', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(71, 20, 'R', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(83, 20, 'Y', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(95, 20, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(107, 20, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(119, 20, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(113, 20, ' ', ST7735_RED, 0x0, 2);

          ST7735_DrawChar(9, 43, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(21, 43, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(30, 43, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(42, 43, 'M', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(54, 43, 'A', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(66, 43, 'Z', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(78, 43, 'E', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(90, 43, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(102, 43, ' ', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(114, 43, ' ', ST7735_RED, 0x0, 2);
      } else {
          ST7735_DrawChar(5, 20, 'L', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(17, 20, 'A', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(29, 20, 'B', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(41, 20, 'Y', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(53, 20, 'R', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(65, 20, 'I', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(77, 20, 'N', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(89, 20, 'T', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(101, 20, 'H', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(113, 20, 'E', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(9, 43, 'E', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(21, 43, 'F', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(33, 43, 'F', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(45, 43, 'R', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(57, 43, 'A', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(69, 43, 'Y', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(81, 43, 'A', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(93, 43, 'N', ST7735_RED, 0x0, 2);
          ST7735_DrawChar(105, 43, 'T', ST7735_RED, 0x0, 2);
      }

      ST7735_SetCursor(3, 7);
      if (currLanguage == English) {
          ST7735_OutString("    Press UP    ");
      } else {
          ST7735_OutString("Appuyez sur HAUT");
      }

      ST7735_SetCursor(6, 8);
      if (currLanguage == English) {
          ST7735_OutString(" To Play   ");
      } else {
          ST7735_OutString("Pour Jouer");
      }

      ST7735_SetCursor(7, 10);
      if (currLanguage == English) {
          ST7735_OutString("English");
      } else {
          ST7735_OutString("French ");
      }
      // Switch Languages
      if (inp == 0x1) {
          if (currLanguage == English) {
              currLanguage = French;
          } else {
              currLanguage = English;
          }
          // Debouncing
          while (inp == 0x1) {}
      }

      if (inp == 0x2) {
          gameFlag = 1;
          level1 = 1;
      }
  }
  // Main Game Loop
  while(1) {
      // Start Screen

      // Level 1

      if (level1){
        // Check for completion of maze (Exit Reached)
        // Calculate distance to exit
        exitDist = abs(posX/10000 - exit1_X) + abs(posY/10000 - exit1_Y);
        if (exitDist <= 2) {
          gameFlag = 0;
          ST7735_FillScreen(ST7735_BLACK);
          level1 = 0;
          level2 = 1;
          score1 = gameTimer;
          // Initialize new world map and starting values such as position
          posX = 31*10000, posY = 2*10000;
          currWorldMap = worldMap1;
          // Press Continue to continue
          soundEnFlag = 0;
          ST7735_DrawChar(6, 57, 'P', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(12, 57, 'R', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(18, 57, 'E', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(24, 57, 'S', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(30, 57, 'S', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(38, 57, '"', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(43, 57, 'S', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(49, 57, '1', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(53, 57, '"', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(61, 57, 'T', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(67, 57, 'O', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(75, 57, 'C', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(81, 57, 'O', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(87, 57, 'N', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(93, 57, 'T', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(99, 57, 'I', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(105, 57, 'N', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(111, 57, 'U', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(117, 57, 'E', ST7735_GREEN, 0x0, 1);
          while (LaunchPad_InS2() == 0) {

          }
          soundEnFlag = 1;
          gameTimer = 3600;
          gameFlag = 1;
        }

        if (gameTimer == 0) {
          // Show Game Over Screen with current total score
          gameFlag = 0;
          break;
        }

        // Update Heart and Jump Scare Warning animations
        if((gameTimer) < 720){
            heartx = Heart[i].x;
        }else{heartx = 20;}
    }

    // Level 2
    if (level2) {
        // Check for completion of maze (Exit Reached)
        // Calculate distance to exit
        exitDist = abs(posX/10000 - exit2_X) + abs(posY/10000 - exit2_Y);
        if (exitDist <= 2) {
          gameFlag = 0;
          ST7735_FillScreen(ST7735_BLACK);
          level2 = 0;
          level3 = 1;
          score2 = gameTimer;
          // Initialize new world map and starting values such as position
          posX = 4*10000, posY = 3*10000;
          currWorldMap = worldMap2;
          // Press Continue to continue
          soundEnFlag = 0;
          ST7735_DrawChar(6, 57, 'P', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(12, 57, 'R', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(18, 57, 'E', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(24, 57, 'S', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(30, 57, 'S', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(38, 57, '"', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(43, 57, 'S', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(49, 57, '1', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(53, 57, '"', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(61, 57, 'T', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(67, 57, 'O', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(75, 57, 'C', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(81, 57, 'O', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(87, 57, 'N', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(93, 57, 'T', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(99, 57, 'I', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(105, 57, 'N', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(111, 57, 'U', ST7735_GREEN, 0x0, 1);
          ST7735_DrawChar(117, 57, 'E', ST7735_GREEN, 0x0, 1);
          while (LaunchPad_InS2() == 0) {

          }
          soundEnFlag = 1;
          gameTimer = 3600;
          gameFlag = 1;
        }

        if (gameTimer == 0) {
          // Show Game Over Screen with current total score
          gameFlag = 0;
          break;
        }

        // Calculate Warning Distances
        scareDist = abs(posX/10000 - scare2X) + abs(posY/10000 - scare2Y);
        if (scareDist <= 4) {
            soundEnFlag = 0;
            warningx = Warning[i].x;
        } else {warningx = 2; soundEnFlag = 1;}

        // Jump Scare
        if (scareDist <= 1) {
            noScares = 0;
            gameFlag = 0;
            Sound_Start(scream, 7606, 80000000/11000);
            ST7735_DrawBitmap(0, 160, unnamed, 128, 160);
            break;
        }

        // Update Heart and Jump Scare Warning animations
        if((gameTimer) < 720){
            heartx = Heart[i].x;
        }else{heartx = 20;}
    }

    // Level 3
    if (level3) {
        // Check for completion of maze (Exit Reached)
        // Calculate distance to exit
        exitDist = abs(posX/10000 - exit3_X) + abs(posY/10000 - exit3_Y);
        if (exitDist <= 2) {
          gameFlag = 0;
          score3 = gameTimer;
          ST7735_FillScreen(ST7735_BLACK);
          level3 = 0;
          win = 1;
          break;
        }

        if (gameTimer == 0) {
          // Show Game Over Screen with current total score
          gameFlag = 0;
          break;
        }

        // Update Heart and Jump Scare Warning animations
        if((gameTimer) < 720){
            heartx = Heart[i].x;
        }else{heartx = 20;}

        // Calculate Warning Distances
        scareDist = abs(posX/10000 - scare3X) + abs(posY/10000 - scare3Y);
        if (scareDist <= 7) {
            warningx = Warning[i].x;
            soundEnFlag = 0;
        } else {warningx = 2; soundEnFlag = 1;}

        // Jump Scare
        if (scareDist <= 4) {
            noScares = 0;
            gameFlag = 0;
            Sound_Start(scream, 7606, 80000000/11000);
            ST7735_DrawBitmap(0, 160, unnamed, 128, 160);
            break;
        }
    }

    // Only Update screen when semaphore for drawing is set (make sure to set gameFLAG back)
    if (gameFlag) {
        if (drawFlag & noScares) {
            // Create Slice Buffer
            for(int x = 0; x < screenWidth; x++)
            {
                //calculate ray position and direction
                int cameraX = ((2*x*10000)/screenWidth) - 10000;
                int rayDirX = dirX + ((planeX * cameraX)/10000);
                int rayDirY = dirY + ((planeY * cameraX)/10000);

                //which box of the map we're in
                int mapX = (int) posX/10000;
                int mapY = (int) posY/10000;

                //length of ray from one x or y-side to next x or y-side
                int sideDistX;
                int sideDistY;

                //Fixed Point Method
                int deltaDistX = (rayDirX == 0) ? 0x7FFFFFFF : abs((10000*100000)/rayDirX);
                int deltaDistY = (rayDirY == 0) ? 0x7FFFFFFF : abs((10000*100000)/rayDirY);
                int perpWallDist;

                //what direction to step in x or y-direction (either +1 or -1)
                int stepX;
                int stepY;

                int hit = 0; //was there a wall hit?
                int side; //was a NS or a EW wall hit?

                //calculate step and initial sideDist
                if (rayDirX < 0)
                {
                    stepX = -1;
                    sideDistX = ((posX/10000) - mapX) * deltaDistX;
                }
                else
                {
                    stepX = 1;
                    sideDistX = (mapX + 1.0 - (posX/10000)) * deltaDistX;
                }
                if (rayDirY < 0)
                {
                    stepY = -1;
                    sideDistY = ((posY/10000) - mapY) * deltaDistY;
                }
                else
                {
                    stepY = 1;
                    sideDistY = (mapY + 1.0 - (posY/10000)) * deltaDistY;
                }

                //perform DDA
                while(hit == 0)
                {
                    //jump to next map square, either in x-direction, or in y-direction
                    if(sideDistX < sideDistY)
                    {
                     sideDistX += deltaDistX;
                     mapX += stepX;
                     side = 0;
                    }
                    else
                    {
                     sideDistY += deltaDistY;
                     mapY += stepY;
                     side = 1;
                    }
                    //Check if ray has hit a wall
                    if(currWorldMap[mapX][mapY] > 0) hit = 1;
                }

                //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
                if(side == 0) perpWallDist = (sideDistX - deltaDistX);
                else          perpWallDist = (sideDistY - deltaDistY);

                //Fixed Point Line Height
                int lineHeight = (screenHeight * 100000) / perpWallDist;

                 //calculate lowest and highest pixel to fill in current stripe
                 int drawStart = -lineHeight / 2 + screenHeight / 2;
                 if(drawStart < 0) drawStart = 0;
                 int drawEnd = lineHeight / 2 + screenHeight / 2;
                 if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

                 if (perpWallDist/100000 > 0) {
                     sliceBuffer[x].dist = perpWallDist/100000;
                 } else {
                     sliceBuffer[x].dist = 1;
                 }

                 if (currWorldMap[mapX][mapY] == 7) {
                     sliceBuffer[x].exit = 1;
                 } else {
                     sliceBuffer[x].exit = 0;
                 }

                 sliceBuffer[x].dStart = drawStart;
                 sliceBuffer[x].dEnd = drawEnd;
                 sliceBuffer[x].s = side;

            }

            for (uint8_t i = 0; i < 128; i++) {
              // Iterate through Slices and Draw each Slice
              uint8_t r = (255/sliceBuffer[i].dist);
              uint8_t g = (255/sliceBuffer[i].dist);
              uint8_t b = (255/sliceBuffer[i].dist);

              if((sliceBuffer[i].s == 1) && (r/2 != 0)) {
                  // Can change to right shift
                  r /= 2;
                  g /= 2;
                  b /= 2;
              }

              if (sliceBuffer[i].exit) {
                  r = 255;
                  g = 0;
                  b = 0;
              }

              // Outlining for UI and Hand
              uint8_t d_End = (sliceBuffer[i].dEnd >= 160 - armHeight) ? (160 - armHeight) : sliceBuffer[i].dEnd;
              uint8_t d_Start = (sliceBuffer[i].dStart <= 14) ? 15 : sliceBuffer[i].dStart;

              if (i <= 34) {
                  if (sliceBuffer[i].dStart > 14) {
                      ST7735_DrawFastVLine(i, 15, sliceBuffer[i].dStart-15, ST7735_BLACK/*ST7735_Color565(255, 0, 0)*/);
                  }
                  ST7735_DrawFastVLine(i, d_Start, sliceBuffer[i].dEnd - d_Start, ST7735_Color565(r, g, b));
                  ST7735_DrawFastVLine(i, sliceBuffer[i].dEnd, 160-sliceBuffer[i].dEnd, ST7735_BLACK/*ST7735_Color565(0, 255, 0)*/);
              }  else if (i >= 69) {
                  ST7735_DrawFastVLine(i, 0, sliceBuffer[i].dStart, ST7735_BLACK/*ST7735_Color565(255, 0, 0)*/);
                  ST7735_DrawFastVLine(i, sliceBuffer[i].dStart, d_End-sliceBuffer[i].dStart, ST7735_Color565(r, g, b));
                  if (sliceBuffer[i].dEnd < (160 - armHeight)) {
                      ST7735_DrawFastVLine(i, sliceBuffer[i].dEnd, 160-armHeight-sliceBuffer[i].dEnd, ST7735_BLACK/*ST7735_Color565(0, 255, 0)*/);
                  }
              } else {
                  ST7735_DrawFastVLine(i, 0, sliceBuffer[i].dStart, ST7735_BLACK/*ST7735_Color565(255, 0, 0)*/);
                  ST7735_DrawFastVLine(i, sliceBuffer[i].dStart, sliceBuffer[i].dEnd-sliceBuffer[i].dStart, ST7735_Color565(r, g, b));
                  ST7735_DrawFastVLine(i, sliceBuffer[i].dEnd, 160-sliceBuffer[i].dEnd, ST7735_BLACK/*ST7735_Color565(0, 255, 0)*/);
              }
            }

            // Overlay the Hand

            // Clear Arm Inversion Buffer
//            BufferClear(armOverlay, 2242);

            // Create 2D Buffer of sub-background
            for (uint32_t j = 0; j < 59; j++) {
                // Slice is inside arm buffer
                uint8_t r1 = 255/sliceBuffer[69+j].dist;
                uint8_t g1 = 255/sliceBuffer[69+j].dist;
                uint8_t b1 = 255/sliceBuffer[69+j].dist;

                if((sliceBuffer[69+j].s == 1) && (r1/2 != 0)) {
                    // Can change to right shift
                    r1 /= 2;
                    g1 /= 2;
                    b1 /= 2;
                }

                if (sliceBuffer[69+j].exit) {
                      r1 = 255;
                      g1 = 0;
                      b1 = 0;
                }

                uint8_t currDEnd = (sliceBuffer[69+j].dEnd >= 160) ? 160 : sliceBuffer[69+j].dEnd;
                if (currDEnd >= 160 - armHeight) {
                    // Iterate through 2D array column and add slice colors
                    for (uint32_t k = 0; k < (currDEnd - (160-armHeight)); k++) {
                        armBuffer[k][j] = ST7735_Color565(r1, g1, b1);
                    }
                } else {
                    for (uint32_t k = 0; k < 38; k++) {
                        armBuffer[k][j] = 0;
                    }
                }
            }

            // Arm Buffer Inversion to Bitmap
            uint32_t pixel = 0;
            for (int32_t row = 37; row >= 0; row--) {
                for(int32_t col = 0; col < 59; col++) {
                    armOverlay[pixel] = armBuffer[row][col];
                    pixel++;
                }
            }

            // Iterate through inverted arm and update new buffer
            for (uint32_t f = 0; f < 2242; f++) {
                if(handlight[f] > 0) {
                    armOverlay[f] = handlight[f];
                }
            }

            ST7735_DrawBitmap(69, 160-handShift, armOverlay, 59, 38);

            // Icon Motion and Animation Output
            ST7735_DrawBitmap(heartx, 14, currentheart, 15, 14);
            ST7735_DrawBitmap(warningx, 14, currentwarning, 15, 14);

        }
        // Update Position based on user input and play sound

        //Setting Rotation Factors (based on ADC inp)
        if (drawFlag) {
            ADCConvert(adcSamp);

            // forward
            if (inp == 2) {
             //(posX + dirX) < mapWidth) &
             if(currWorldMap[((posX + (dirX * moveSpeed))/10000)][(posY/10000)] == 0) {
                 posX = (posX + (dirX>>2 * moveSpeed));
             }

             //((posX + dirX) < mapHeight) &
             if(currWorldMap[(posX/10000)][((posY + (dirY * moveSpeed))/10000)] == 0) {
                 posY = (posY + (dirY>>2 * moveSpeed));
             }

             // Write edge cases for going off screen
            }

            // backward
            if (inp == 1) {
             // ((posX + dirX) > 0) &
             if(currWorldMap[((posX - (dirX * moveSpeed))/10000)][(posY/10000)] == 0) {
                 posX = (posX- (dirX>>2 * moveSpeed));
             }

             //((posY + dirY) > 0) &
             if(currWorldMap[(posX/10000)][((posY - (dirY * moveSpeed))/10000)] == 0) {
                 posY = (posY - (dirY>>2 * moveSpeed));
             }
             // Write edge cases for going off screen
            }

            if (rotInp < -70) {
                //both camera direction and camera plane must be rotated
                int oldDirX = dirX;
        //            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        //            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

                // Fixed Point Sol
                dirX = ((dirX*(9950))/10000) - ((dirY * (-998))/10000);
                dirY = ((oldDirX*(-998))/10000) + ((dirY*(9950))/10000);

                int oldPlaneX = planeX;
        //            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        //            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);

                //Fixed Point Sol
                planeX = ((planeX * (9950))/10000) - ((planeY * (-998))/10000);
                planeY = ((oldPlaneX * (-998))/10000) + ((planeY * (9950))/10000);

            }

            // left
            if (rotInp > 70) {

                int oldDirX = dirX;
        //            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        //            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

                // Fixed Point Sol
                dirX = ((dirX*(9950))/10000) - ((dirY * (998))/10000);
                dirY = ((oldDirX*(998))/10000) + ((dirY*(9950))/10000);

                int oldPlaneX = planeX;
        //            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        //            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);

                //Fixed Point Sol
                planeX = ((planeX * (9950))/10000) - ((planeY * (998))/10000);
                planeY = ((oldPlaneX * (998))/10000) + ((planeY * (9950))/10000);
            }
        }
        //gameFlag = 0; <---------------- Turn this back to one and move hand outside
    }

  }
// End Game Loop
    soundEnFlag = 0;
    while(SysTick->VAL != 0) {};
    Clock_Delay1ms(1000);
    score = score1 + score2 + score3;

    if (win == 1) {
        if (currLanguage == English) {
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(25, 50, 'H', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(37, 50, 'O', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(49, 50, 'O', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(61, 50, 'R', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(73, 50, 'A', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(85, 50, 'Y', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(95, 50, '!', ST7735_GREEN, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(5, 7);
            ST7735_SetTextColor(ST7735_GREEN);
            ST7735_OutString("You escaped");
            ST7735_SetCursor(6, 8);
            ST7735_OutString("the maze!");
            Clock_Delay1ms(3000);
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(30, 50, 'S', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(42, 50, 'C', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(54, 50, 'O', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(66, 50, 'R', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(78, 50, 'E', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(90, 50, ':', ST7735_YELLOW, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_SetTextColor(ST7735_GREEN);
            ST7735_SetCursor(5, 7);
            ST7735_OutUDec(score);    //temporary score

        } else {
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(22, 40, 'H', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(34, 40, 'O', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(46, 40, 'U', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(58, 40, 'R', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(70, 40, 'R', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(82, 40, 'A', ST7735_GREEN, 0x0, 2);
            ST7735_DrawChar(92, 40, '!', ST7735_GREEN, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(1, 7);
            ST7735_SetTextColor(ST7735_GREEN);
            ST7735_OutString("Vous gagnez");
            ST7735_OutString(" \x82");
            ST7735_OutString("chapp\x82");
            ST7735_SetCursor(4, 8);
            ST7735_OutString("au labyrinthe!");
            Clock_Delay1ms(3000);
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(30, 50, 'S', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(42, 50, 'C', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(54, 50, 'O', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(66, 50, 'R', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(78, 50, 'E', ST7735_YELLOW, 0x0, 2);
            ST7735_DrawChar(90, 50, ':', ST7735_YELLOW, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_SetTextColor(ST7735_GREEN);
            ST7735_SetCursor(5, 7);
            ST7735_OutUDec(score);        //temporary score
        }

    } else {
        if (currLanguage == English) {
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(5, 30, 'G', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(20, 30, 'A', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(35, 30, 'M', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(50, 30, 'E', ST7735_RED, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_DrawChar(67, 30, 'O', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(82, 30, 'V', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(97, 30, 'E', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(112, 30, 'R', ST7735_RED, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(5, 6);
            ST7735_SetTextColor(ST7735_WHITE);
            ST7735_OutString("You ran out");
            ST7735_SetCursor(5, 7);
            ST7735_OutString("of time...");
            Clock_Delay1ms(3000);
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(30, 50, 'S', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(42, 50, 'C', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(54, 50, 'O', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(66, 50, 'R', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(78, 50, 'E', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(90, 50, ':', ST7735_PURPLE, 0x0, 2);
            Clock_Delay1ms(1000);
            // Score
            ST7735_SetTextColor(ST7735_RED);
            ST7735_SetCursor(5, 7);
            ST7735_OutUDec(score);    //temporary score

        } else {
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(5, 30, 'J', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(17, 30, 'E', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(29, 30, 'U', ST7735_RED, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_DrawChar(44, 30, 'T', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(56, 30, 'E', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(68, 30, 'R', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(80, 30, 'M', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(91, 30, 'I', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(102, 30, 'N', ST7735_RED, 0x0, 2);
            ST7735_DrawChar(114, 30, '\x90', ST7735_RED, 0x0, 2);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(5, 6);
            ST7735_SetTextColor(ST7735_WHITE);
            ST7735_OutString("Tu es \x82puis\x82");
            ST7735_SetCursor(5, 7);
            ST7735_OutString("de temps...");
            Clock_Delay1ms(3000);
            ST7735_FillScreen(ST7735_BLACK);
            ST7735_DrawChar(30, 50, 'S', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(42, 50, 'C', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(54, 50, 'O', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(66, 50, 'R', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(78, 50, 'E', ST7735_PURPLE, 0x0, 2);
            ST7735_DrawChar(90, 50, ':', ST7735_PURPLE, 0x0, 2);
            Clock_Delay1ms(1000);
            //score
            ST7735_SetTextColor(ST7735_RED);
            ST7735_SetCursor(5, 7);
            ST7735_OutUDec(score);    //temporary score
        }
    }

    while(1) {

    }
}
