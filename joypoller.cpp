#include "joypoller.h"
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
//#include <QDebug>


input_event joypoller::eventInterpreter(input_event *EV){
    input_event newEv; //define new event
    //separate into KEY or ABS event
    if(EV->type == EV_KEY){
        newEv = kmapper(EV);
    } else if(EV->type == EV_ABS){
        if(EV->code == 17 || 16 || 2 || 5){ //edgecases caused by controller driver
            newEv = kmapper(EV);
            //not yet configured for analog input besauce lazy
        } else {
            //newEv = amapper(&EV);
            return newEv;
        }
    }
    return newEv;
}

input_event joypoller::kmapper(input_event *EV){ //remaps the controller code to more coherent directions
    input_event tmp; //tmp medium for storage of return struct
    tmp.type = EV->type;
    tmp.code = EV->code;
    tmp.value = EV->value;
    switch (EV->code){ //mapping of direction
    case 17: //up and down dpad
        if (EV->value > 0){
            tmp.code = LDOWN;
        } else if(EV->value < 0) {
            tmp.code = LUP;
        } else if(EV->value == 0){
            tmp.code = TERMY;
        }
        break;
    case 16: //left n rite dpad
        if (EV->value > 0){
            tmp.code = LRIGHT;
        } else if (EV->value < 0){
            tmp.code = LLEFT;
        } else if (EV->value == 0){
            tmp.code = TERMX;
        }
        break;
    case 2: //L2
        EV->value = 1;
        break;
    case 5: //R2
        EV->value = 1;
        break;
    default:
        break;
    }
    if(EV->code == TRIANG || EV->code == CROSS || EV->code == CIRCLE || EV->code == SQUARE){ //catches button return press
        if(EV->value != 1){
            tmp.code = tmp.code + 30; //translates into new return code
        }
    }
    return tmp;
}

void debug_translator(int code){ //translates the code into a string
    switch(code){
    case LUP:
        std::cout  << "dpad up" << std::endl;
        break;
    case LDOWN:
        std::cout  << "dpad down" << std::endl;
        break;
    case LLEFT:
        std::cout  << "dpad left" << std::endl;
        break;
    case LRIGHT:
        std::cout  << "dpad right" << std::endl;
        break;
    case TRIANG: //dpad up r
        std::cout  << "triangle" << std::endl;
        break;
    case CROSS: //dpad down r
        std::cout  << "cross" << std::endl;
        break;
    case SQUARE: //dpad left r
        std::cout  << "square" << std::endl;
        break;
    case CIRCLE: //dpad right r
        std::cout  << "circle" << std::endl;
        break;
    case L1: //L1
        std::cout  << "L1" << std::endl;
        break;
    case R1: //R1
        std::cout  << "R1" << std::endl;
        break;
    case L2: //L2
        std::cout  << "L2" << std::endl;
        break;
    case R2: //R2
        std::cout  << "R2" << std::endl;
        break;
    case start: //start
        std::cout  << "Start" << std::endl;
        break;
    case select: //select
        std::cout  << "select" << std::endl;
        break;
    default:
        break;
    }
}
/*Æ
switch (code){
    case 0:
        tmpmap.source = "left analog x";
        tmpmap.value = val;
        break;
    case 1:
        tmpmap.source = "left analog y";
        tmpmap.value = val;
        break;
    case 3:
        tmpmap.source = "right analog x";
        tmpmap.value = val;
        break;
    case 4:
        tmpmap.source = "right analog y";
        tmpmap.value = val;
        break;
    default:
        break;
}

 */
//not used RN
/*
input_event joypoller::amapper(unsigned short code, unsigned int val){
    thing tmpmap;
        switch (code){
        case 0:
            tmpmap.source = "left analog x";
            tmpmap.value = val;
            break;
        case 1:
            tmpmap.source = "left analog y";
            tmpmap.value = val;
            break;
        case 3:
            tmpmap.source = "right analog x";
            tmpmap.value = val;
            break;
        case 4:
            tmpmap.source = "right analog y";
            tmpmap.value = val;
            break;
        default:
            break;
    }
    return tmpmap;
}
*/
