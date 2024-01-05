#ifndef JOYPOLLER_H
#define JOYPOLLER_H

#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
//#include <QDebug>


//legend of the controller buttons and axis code
// Dpad-Left (Axis)
    // Up - Code 17 - (-1)
    // Down - Code 17 - (1)
    // Left - Code 16 - (-1)
    // Right - Code 16 - (1)

//Dpad-Right (Key)
    // Up - Code 301 - (1)
    // Down - Code 304 - (1)
    // Left - Code 307 - (1)
    // Right - Code 305 - (1)

// Stick Left (Axis)
    // Up - Code 1 - (-32768)
    // Down - Code 1 - (32768)
    // Left - Code 0 - (-32768)
    // Right - Code 0 - (32768)

// Stick Right (Axis)
    // Up - Code 4 - (-32768)
    // Down - Code 4 - (32768)
    // Left - Code 3 - (-32768)
    // Right - Code 3 - (32768)

//Bumpers (Key)
    // L1 - Code 310 - (1)
    // R1 - Code 311 - (1)

//Bumpers (Axis

    // L2 - Code 2 - (255)
    // R2 - Code 5 - (255)

//Others (Key)
    // Start - Code 315 - (1)
    // Select - Code 314 - (1)



//Key Defines
//dpad left
#define LUP 17
#define LDOWN 18
#define LLEFT 16
#define LRIGHT 15
#define DLTMT 14

//dpad right
#define TRIANG 308
#define CROSS 304
#define SQUARE 307
#define CIRCLE 305

//Stick left
#define LXA 0
#define LYA 1

//stick right
#define RXA 3
#define RYA 4

// bumpers
#define L1 310
#define L2 2
#define R1 311
#define R2 5

//rest
#define start 315
#define select 314


class joypoller {
public:

    //function
    input_event eventInterpreter(input_event *event); //converts the int code to a button
    int eventFileConnector(char event_path); //establishes connection between file descriptor and Qt (not currently used and/or implenmented)
    //event handleEvent(); //executed upon an event (may be unneded)

private:
    //variables

    //function 
    input_event kmapper(input_event *event); //remapper for keys
    input_event amapper(input_event *event); //remapper for jøystick
};

void debug_translator(int val);

#endif // JOYPOLLER_H
