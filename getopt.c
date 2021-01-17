#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>


bool printReturnCode=false;
bool timeFormatSet=false;
bool limitSet=false;
bool intervalSet=false;


int interval=0;
char timeFormat[100];
int limitOfIterations=0;//0 for infinity

int main(int argc, char *argv[])
{
    fclose(stderr);
    
    int progStartIndex=-1;
    int opt=-1;
    //copying argv into argv2
    char **argv2=calloc(argc, sizeof(char *));
    for(int i=0;i<argc;i++){
        argv2[i]=calloc(100, sizeof(char));
        strcpy(argv2[i], argv[i]);
    }
    for(int i=0;i<argc;i++){
        printf("i=%d, argv2[%d]=%s\n", i, i, argv2[i]);
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
    // for(int i=0;i<argc;i++){
    //     printf("i=%d, argv2[%d]=%s\n", i, i, argv2[i]);
    // }
    // // printf("\noptind=%d\n", optind);
    // printf("argc=%d\tprogStartIndex=%d\n\n", argc, progStartIndex);
    // printf("argv[%d]=%s\n", progStartIndex, argv[progStartIndex]);
    progStartIndex=optind;
    int length=argc-progStartIndex;
    // char *args[length];
    char command[256];
    int index=0;
    // for(int i=0;i<length;i++) args[i]=calloc(100,sizeof(char));
    for(int i=0;i<length;i++){
        // printf("argv2[%d]=%s\n", i, argv2[i]);
        sprintf(command, "%s %s", command, argv2[i+progStartIndex]);
        
        // strcpy(args[i], argv2[i+progStartIndex]);
        // printf("args[%d]=%s\n", i, args[i]);
    }
    printf("----------------args----------------------\n");
    printf("ommand: %s\n", command);
    // for(int i=0;i<length;i++) printf("args[%d]=%s\n", i, args[i]);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include <unistd.h>
// #include <getopt.h>

// bool printReturnCode=false;
// int interval=0;
// char timeFormat[100];
// int limitOfIterations=0;//0 for infinity

// int main(int argc, char *argv[])
// {
//     fclose(stderr);
//     int progStartIndex=-1;
//     int opt=-1;
//     // dub2(, 2);
//     while((opt=getopt(argc, argv, "ci:t:l:"))!=-1){
//         // printf("in while\n");
//         switch (opt)
//         {
//             case 'c':
//                 printReturnCode=true;
//                 printf("print Return code true\n");
//                 break;
//             case 'i':
//                 interval=atoi(argv[optind-1]);
//                 printf("Set interval to %d\n", interval);
//                 break;
//             case 't':
//                 strcpy(timeFormat, argv[optind-1]);
//                 printf("Set time format to %s\n", timeFormat);
//                 break;
//             case 'l':
//                 limitOfIterations=atoi(argv[optind-1]);
//                 printf("Set limit to %d\n", limitOfIterations);
//                 break;
//             case '?':
//                 printf("Option is needed\n");
//                 break;            
//             default:
//                 printf("default\n");
//                 break;
//         }
//     }
//     // printf("optind %d\n", optind);
//     progStartIndex=optind;
//     return 0;
// }
