#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "xboxControlRumble.h"
#include <errno.h>
#include <stdlib.h>

enum {
    FF_DIR_SOUTH      = 0x0000,
    FF_DIR_WEST       = 0x4000,
    FF_DIR_WEST_NORTH = 0x6000,
    FF_DIR_NORTH      = 0x8000,
    FF_DIR_NORTH_EAST = 0xA000,
    FF_DIR_EAST       = 0xC000
};

int fdXboxController = 0;
struct ff_effect effects[16];
struct input_event play;

int rumbleTest()
{
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = 600 * 1000000L;

    /* Read in arguments */

    char* eventName = extract_controller_eventname();
    printf("%s\n", eventName);
    char device[80];
    snprintf(device, 80, "/dev/input/%s", eventName);


    int magnitude = -1;

    magnitude = 32767;


    if (magnitude < 0 || magnitude > 65535)
        magnitude = 0xC000;



    /* Start */

    printf("Directional Rumble Test\n");

    

    /* prepare effects */
    for (int i = 0; i < 16; i++) {
        effects[i].type = FF_RUMBLE;
        effects[i].id = -1; // set by ioctl
        effects[i].direction = FF_DIR_SOUTH + i * 0x1000;
        effects[i].u.rumble.strong_magnitude = magnitude;
        effects[i].u.rumble.weak_magnitude = magnitude;
        effects[i].replay.length = 500;//330;
        effects[i].replay.delay = 0;
    }

    printf("Press ENTER to upload Rumble effects\n");
    //getchar();


    /* uploading */
    fdXboxController = open(device, O_RDWR);
    for (int i = 0; i < 16; i++) {
        if (ioctl(fdXboxController, EVIOCSFF, &effects[i]) == -1) {
            perror("Error while uploading\n");
            close(fdXboxController);
            return 1;
        }
    }


    printf("Press ENTER to play rumble effects\n");
    //getchar();

    for (int j = 0; j < 2; j++) {
		int i = j % 16;
        memset(&play, 0, sizeof(play));
        play.type = EV_FF;
        play.code = effects[i].id;
        play.value = 1;

        if (write(fdXboxController, (const void*) &play, sizeof(play)) == -1) {
            perror("Error while playing\n");
            close(fdXboxController);
            return 1;
        } else {
            printf("effect %2d, direction: %04x\n", i, effects[i].direction);
        }

        nanosleep(&req, (struct timespec *)NULL);
    }
    
    return 0;
}

void doRumble(int effect, int magnitude)
{
    if(effect > 16 || effect < 0) 
        effect = 8;
    if (magnitude < 0 || magnitude > 65535)
        magnitude = 0xC000;
    
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = 600 * 1000000L;
    
    int i = effect;
    
    char* eventName = extract_controller_eventname();
    printf("%s\n", eventName);
    
    char device[80];
    snprintf(device, 80, "/dev/input/%s", eventName);
    
    if(!fdXboxController)
    {
        /* prepare effects */
        for (int i = 0; i < 16; i++) {
            effects[i].type = FF_RUMBLE;
            effects[i].id = -1; // set by ioctl
            effects[i].direction = FF_DIR_SOUTH + i * 0x1000;
            effects[i].u.rumble.strong_magnitude = magnitude;
            effects[i].u.rumble.weak_magnitude = magnitude;
            effects[i].replay.length = 500;
            effects[i].replay.delay = 0;
        }
    
        /* uploading */
        fdXboxController = open(device, O_RDWR);
        if (ioctl(fdXboxController, EVIOCSFF, &effects[i]) == -1) {
            perror("Error while uploading\n");
            close(fdXboxController);
            return;
        }
    }
    
    memset(&play, 0, sizeof(play));
    play.type = EV_FF;
    play.code = effects[i].id;
    play.value = 1;
    
    for(int k = 0; k < effect; k++)
    {
        if (write(fdXboxController, (const void*) &play, sizeof(play)) == -1) {
            close(fdXboxController);
            perror("Error while playing\n");
            return;
        } else {
            printf("effect %2d, direction: %04x\n", i, effects[i].direction);
        }
        nanosleep(&req, (struct timespec *)NULL);
    }
    
    //close(fd);
}

// 
// https://github.com/kernc/logkeys/issues/89
//
char *extract_controller_eventname()
{
    FILE *fp = NULL;
    char buffer[1024];
    char *eventname = NULL;
    fp = fopen("/proc/bus/input/devices", "r");
    if (!fp) {
        int err = errno;
        fprintf(stderr, "Unable to open file. %s\n", strerror(err));
        return NULL;
    }
    memset(buffer, 0, sizeof(buffer));
    while (fgets(buffer, sizeof(buffer), fp)) {
        char *ptr = NULL;
        if ((ptr = strstr(buffer, "Handlers="))) {
            ptr += strlen("Handlers=");
            ptr = strstr(ptr, "event");
            if (ptr) {
                char *ptr2 = strchr(ptr, ' ');
                if (ptr2)
                    *ptr2 = '\0';
                eventname = strdup(ptr);
                if (!eventname) {
                    fprintf(stderr, "Out of memory.\n");
                    break;
                }
            }
        }
        if (strstr(buffer, "Phys=b8:3f:26:a7:c1:8d")) {
            fprintf(stderr, "Xbox controller event is /dev/input/%s\n", eventname);
            break;
        }
    }
    fclose(fp);
    return eventname;
}
