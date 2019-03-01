#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

bool printReturnCode=false;
bool timeFormatSet=false;
bool limitSet=false;
bool intervalSet=false;

int interval=10000;//in millis
char timeFormat[100];
int limitOfIterations=0;//0 for infinity



int main(int argc, char *argv[])
{
    fclose(stderr);
    int progStartIndex=-1;
    int opt=-1;
    // dub2(, 2);
    while((opt=getopt(argc, argv, "ci:t:l:"))!=-1){
        // printf("in while\n");
        switch (opt)
        {
            case 'c':
                printReturnCode=true;
                printf("print Return code true\n");
                break;
            case 'i':
                interval=atoi(argv[optind-1]);
                intervalSet=true;
                printf("Set interval to %d\n", interval);
                break;
            case 't':
                timeFormatSet=true;
                strcpy(timeFormat, argv[optind-1]);
                printf("Set time format to %s\n", timeFormat);
                break;
            case 'l':
                limitSet=true;
                limitOfIterations=atoi(argv[optind-1]);
                printf("Set limit to %d\n", limitOfIterations);
                break;
            case '?':
                printf("Option is needed\n");
                break;            
            default:
                printf("default\n");
                break;
        }
    }
    // printf("optind %d\n", optind);
    progStartIndex=optind;
    int counter=0;
    while(counter<limitOfIterations || limitSet==false){
        if(timeFormatSet){
            char currentTime[100];
            time_t curTime=time(NULL);
            struct tm* locTime=localtime(&curTime);
            strftime(currentTime, 100, timeFormat, locTime);
            printf("currentTime - %s\n", currentTime);
        }
        usleep(interval*1000);
        counter++;
    }
    return 0;
}