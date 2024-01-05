#include <iostream>
#include "joypoller.h"


//testbench for the 
int main(){
    //new instance of the joypoller
    joypoller controller1;
    const char *devicePath = "/dev/input/event23";

    joypoller controller2;
    const char *devicePath2 = "/dev/input/event24";

    int fd = open(devicePath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return 1;
    }

    int fd2 = open(devicePath2, O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening device");
        return 1;
    }

    struct input_event ev;

    struct input_event translated;

        
    struct input_event ev2;

    struct input_event translated2;


    while(true){
        
        ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));
        if (bytesRead == sizeof(struct input_event) && ev.value != 0) {
            translated =  controller1.eventInterpreter(&ev);

            debug_translator(translated.code);
            //debug_translator(translated.code);
            //std::cout << "org code " << ev.code << " tanslated code: " << translated.code << std::endl;
        }
        

        //controller 2
        ssize_t bytesRead2 = read(fd2, &ev2, sizeof(struct input_event));
        if (bytesRead2 == sizeof(struct input_event) && ev2.value != 0) {
            translated2 =  controller2.eventInterpreter(&ev2);
            std::cout << "P2 ";
            debug_translator(translated2.code);
            //debug_translator(translated.code);
            //std::cout << "org code " << ev.code << " tanslated code: " << translated.code << std::endl;
        }
        
    }


    return 0;
}


/*
int fuck() {
    const char *devicePath = "/dev/input/event0";

    int fd = open(devicePath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return 1;
    }

    struct input_event ev;

    while (true) {

        ssize_t bytesRead = read(fd, &ev, sizeof(struct input_event));

        if (bytesRead == -1) {
            perror("Error reading event");
            close(fd);
            return 1;
        }

        if (bytesRead == sizeof(struct input_event)) {
            if (ev.type == EV_KEY) {
                std::cout << "Key event: " << ev.code << " State: " << ev.value << std::endl;
            } else if (ev.type == EV_ABS) {
                //std::cout << "Absolute axis event: " << ev.code << " Value: " << ev.value << std::endl;
                qInfo() << "Absolute axis event: " << ev.code << " Value: " << ev.value;
            }
            // Add more conditions based on the event types you want to handle
        }
    }

    close(fd);
    return 0;
}
*/

