#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 130

void main(int argc, char *argv[]){
        char myLine[MAXLINE];
        FILE *fp;
        int flag = 0;
        int totalHours = 0;
        int totalMins = 0;
        int minsInt = 0;
        int hoursInt = 0;
        int n = 0;

        //open the file
        if ((fp = fopen(argv[3], "r")) == NULL){
                printf("cannot open file %s\n", argv[1]);
                exit(1);
        }

        //loop thru contents of file and add to variables
        while (fgets(myLine, MAXLINE, fp) != NULL){
                char myLineCopy[MAXLINE];
                strcpy(myLineCopy, myLine);
                //with space as the delimiter, place each token in variable
                char *loginID, *term, *ip, *dayOfweek, *month, *day, *start, *dash, *end, *time;
                loginID = strtok(myLine, " ");
                term = strtok(NULL, " ");
                ip = strtok(NULL, " ");
                dayOfweek = strtok(NULL, " ");
                month = strtok(NULL, " ");
                day = strtok(NULL, " ");
                start = strtok(NULL, " ");
                dash = strtok(NULL, " ");
                end = strtok(NULL, " ");
                time = strtok(NULL, " ");
				
		//test for cmdline options: -c is ip class, -u is for loginID
                if (strcmp(argv[1], "-c") == 0){
                        //get first octet and place in ipInt variable
                        char* IPclass = strtok(ip, ".");
                        int ipInt = atoi(IPclass);

                        //test first octet for ip class and print
                        if (ipInt > 0 && ipInt < 127 && strcmp(argv[2], "A") == 0){
                                printf("%s", myLineCopy);
                        }
                        if (ipInt > 127 && ipInt <= 191 && strcmp(argv[2], "B") == 0){
                                printf("%s", myLineCopy);
                        }
                        if (ipInt > 191 && ipInt <= 223 && strcmp(argv[2], "C") == 0){
                                printf("%s", myLineCopy);
                        }
                }
                if (strcmp(argv[1], "-u") == 0 && strcmp(argv[2], loginID) == 0){
                        //if first loop, output statement
                        if (flag == 0){
                                printf("\nLogin records for %s:\n\n", argv[2]);
                        }
                        flag = 1;
                        n++;

                        //print log of specified user
                        printf("%s", myLineCopy);

                        //get total minues
                        char *minsStart = &time[4];
                        char *minsEnd = &time[6];
                        char *mins = (char *)calloc(1, minsEnd - minsStart + 1); //+1 for null terminated string
                        memcpy(mins, minsStart, minsEnd - minsStart);
                        minsInt = atoi(mins);
                        totalMins = totalMins + minsInt;
                        free(mins);

                        //get total hours
                        char *hoursStart = &time[1];
                        char *hoursEnd = &time[3];
                        char *hours = (char *)calloc(1, hoursEnd - hoursStart + 1); //+1 for null termination
                        memcpy(hours, hoursStart, hoursEnd - hoursStart);
                        hoursInt = atoi(hours);
                        totalHours = totalHours + hoursInt;
                        free(hours);
                }
        }

        //output total amount of time the user was logged in
        if (strcmp(argv[1], "-u") == 0){
                int quotient = totalMins / 60;
                totalHours = totalHours + quotient;
                totalMins = totalMins % 60;
                if (n > 0){
                        printf("\n%s has spent %d hour and %d minutes on the system.\n\n", argv[2], totalHours, totalMins);

                }else{
                        printf("\nNo login record has been found for %s.\n\n", argv[2]);
                }
        }
}
