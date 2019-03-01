#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

bool printReturnCode=false;
bool timeFormatSet=false;
bool limitSet=false;
bool intervalSet=false;

int interval=10000;//in millis
char timeFormat[100];
int limitOfIterations=0;//0 for infinity

int runCommand(char *command);

int runCommand(char *command){
    int pid=fork();
    if(pid==0){
        printf("run command\n");
        execlp("/bin/sh","sh", "-c", command, NULL);
        // execvp(, command);
        // printf("run \"%s\"\n", command);
        // execvp()
        // exit(3);
    }else if(pid==-1){
        exit(-1);
    }else
    {
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("child exits with status %d\n", WEXITSTATUS(status));
            return WEXITSTATUS(status);
        }
    }
    
}
int main(int argc, char *argv[])
{
    fclose(stderr);
    int progStartIndex=-1;
    int opt=-1;
    // dub2(, 2);
    char **argv2=calloc(argc, sizeof(char *));
    for(int i=0;i<argc;i++){
        argv2[i]=calloc(100, sizeof(char));
        strcpy(argv2[i], argv[i]);
    }
    while((opt=getopt(argc, argv, "+ci:t:l:"))!=-1){
    // printf("in while\n");
        switch (opt)
        {
            case 'c':
                if(printReturnCode==false){
                    printReturnCode=true;
                    printf("print Return code true\n");
                }
                break;
            case 'i':
                if(intervalSet==false){
                    interval=atoi(argv[optind-1]);
                    intervalSet=true;
                    printf("Set interval to %d\n", interval);
                }
                break;
            case 't':
                if(timeFormatSet==false){
                    timeFormatSet=true;
                    strcpy(timeFormat, argv[optind-1]);
                    printf("Set time format to %s\n", timeFormat);
                }
                break;
            case 'l':
            if(limitSet==false){
                limitSet=true;
                limitOfIterations=atoi(argv[optind-1]);
                printf("Set limit to %d\n", limitOfIterations);
            }
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
    int length=argc-progStartIndex;
    char command[256];
    for(int i=0;i<length;i++){
        sprintf(command, "%s %s", command, argv2[i+progStartIndex]);
    }
    printf("command: %s\n", command);

    // progStartIndex=optind;
    int counter=0;
    while(counter<limitOfIterations || limitSet==false){
        if(timeFormatSet){
            char currentTime[100];
            time_t curTime=time(NULL);
            struct tm* locTime=localtime(&curTime);
            strftime(currentTime, 100, timeFormat, locTime);
            printf("currentTime - %s\n", currentTime);
        }
        runCommand(command);
        usleep(interval*1000);
        counter++;
    }
    return 0;
}