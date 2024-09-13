# Scary Maze: Decimal Fixed Point Raycaster
> By Jerin Andrews

## Introduction
To preface, the Raycaster project was a final project of our choice in my Embedded Systems course. In this project I developed and converted a floating point raycaster to a decimal fixed point raycaster and optimized memory usage for maintaining and updating the drawing buffer.

### Implemented Using:
+ [C](https://devdocs.io/c/)
+ [MSPM0 Microcontroller](https://software-dl.ti.com/msp430/esd/MSPM0-SDK/1_00_00_04/docs/english/MSPM0_SDK_Documentation_Overview.html)


## Overview
### Demo
[Full Demo](https://www.youtube.com/watch?v=zPbL96ubVow)

### Optimizations and Design
+ **Floating Point to Fixed Point Math**

  >Commonly raycasters are designed using floating point math, but due to the use of an embedded system, a time critical system, the math must be simplified in order to reduce processing cost and improve overall efficiency. To do this, I converted the floating point math to fixed-point math, more specifically decimal fixed point math. To do this, I took each math operation and equation used in creating the raycaster (i.e. wall height calulations, depth calculations, etc.) and scaled its source values by a multiple of 10. This preserved a set (based on the scaling factor) decimal places in whole number format to perform the calculations with only integers.

+ **Optimized Memory Usage for Drawing Buffer**
  >Initially, I planned on storing each pixel's binary value (0 and 1, off and on respectively) in a image buffer the same size as the screen (128x160), but I quickly ran into memory limitations. To optimize from using a buffer the size of the screen, I converted the drawing process to draw each vertical strip at a time instead of drawing each pixel at a time. Since the built in drawing algorithm's time complexity (and total output time) would be about the same as before, this new method would focus on purely reducing memory usage. To draw each vertical strip, I created a struct that defined each vertical strips properties such as its starting point and ending point. Now, since the program would only need to store an array of structs with a size limited to the width of the screen in pixels multiplied by the bytes for each property.

+ **No Flicker Image Overlay**
  >To handle image overlay, which when normally implemented by just drawing an image over another, would cause screen flicker since the screen is constantly redrawn to update the frame. To fix this I made a separate buffer for overlaying images. Since the built in drawing buffer algorithm uses an inverted version of a drawing buffer to output the image upright, I made a separate algorithm to reverse the image buffer (to be upright initially) and then cut the vertical strips meant to be in that portion of the screen and inserted it into the image buffer. Finally I reversed the image again and outputted using the drawing buffer function.

### In Development 
https://github.com/user-attachments/assets/1278c269-a73e-4bd3-9c6a-8441654272cd

<div align="center">
<img src="https://github.com/user-attachments/assets/2df7e6d3-21fa-417a-bcbe-f13ef3440062" alt="IMG_1957" width="500" height="600">
</div>

### Circuit
![IMG_2354_2](https://github.com/user-attachments/assets/05ab0f76-e1bf-478b-89c1-e82b06e5b16e)
> Top Circuit: 8 Bit DAC (Audio Output), Bottom Circuit: Display (ST7735R), Left Circuit: Inputs (ADC and Buttons), Center: MSPM0 Microcontroller

### Possible Additions:
+ Although decimal fixed point math is highly efficient, I can improve efficiency by switching to binary fixed point. This would reduce the number of assembly operations for any calculations since to convert values (or scale values) to binary fixed point values, the cost is one binary shift instruction. Decimal fixed point math, on the other hand, uses division by multiples of 10, which would require a significant amount more instruction calls (since division isn't a built-in instruction).
