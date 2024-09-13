/*
 * Switch.c
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
//void Switch_Init(void){
    // write this
  
//}
// return current state of switches
//uint32_t Switch_In(void){
    // write this
 // return 0; //replace this your code
//}


// My EXTRA CODE
const uint32_t in_init = 0x00040081;

// **************Key_Init*********************
// Initialize piano key inputs on PB19-PB16
// Input: none
// Output: none
void Switch_Init(void){
// Assumes LaunchPad_Init has been called
// I.e., PortB has already been reset and activated (do not reset PortB here again)
    IOMUX->SECCFG.PINCM[PB16INDEX] = in_init;
    IOMUX->SECCFG.PINCM[PB17INDEX] = in_init;
//    IOMUX->SECCFG.PINCM[PB18INDEX] = in_init;
    //IOMUX->SECCFG.PINCM[PB19INDEX] = in_init;

}

// **************Key_In*********************
// Input from piano key inputs on PB19-PB16
// Input: none
// Output: 0 to 15 depending on keys
//   0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2, 0x08 is just Key3
uint32_t Switch_In(void){
    uint32_t inp = (GPIOB->DIN31_0 & (15<<16)) >> 16;
    return inp;
}
