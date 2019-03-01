#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>

bool printReturnCode=false;
int interval=0;
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
                printf("Set interval to %d\n", interval);
                break;
            case 't':
                strcpy(timeFormat, argv[optind-1]);
                printf("Set time format to %s\n", timeFormat);
                break;
            case 'l':
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
    return 0;
}
