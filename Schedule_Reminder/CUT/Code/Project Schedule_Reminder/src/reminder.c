/*******************************************************************************
*
*     FILENAME       :    reminder.c
*
*     DESCRIPTION    :    This file defines the functions for the Project.
*
*******************************************************************************/

#include "reminder.h"

/******************************************************************************
*
*     FUNCTION NAME   :   modify
*
*     DESCRIPTION     :   This function modifies the reminder by SID in the file.
*
*     Parameters     : int line - Line number of schedule in the file.
*                      char *sid - SID which you want to modify.
*                      char *des - new description entered by user.
*                      char *date - new date entered by user.
*                      char *status - new status entered by user.
*******************************************************************************/
void modify(int line, char *sid, char *des, char *date, char *status)
{
    FILE *fptr  = fopen("schedule.csv", "r");
    FILE *ftemp = fopen("replace.txt", "w"); 
    int count;
    char buffer[MAX_BUFF_SIZE];

    /* fopen() return NULL if unable to open file in given mode. */
    if (fptr == NULL || ftemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(0);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, MAX_BUFF_SIZE, fptr)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
            fprintf(ftemp,"%s, %s,%s, %s,\n", sid, des, date, status);
        else
            fputs(buffer, ftemp);
    }


    /* Close all files to release resource */
    fclose(fptr);
    fclose(ftemp);
    
    remove("schedule.csv");
    rename("replace.txt", "schedule.csv");
    
}

/******************************************************************************
*
*     FUNCTION NAME   :   remove_func
*
*     DESCRIPTION     :   This function removes the reminder by SID in the file. 
*
*     Parameters     :  int line - int line - Line number of schedule in the file. 
*     
*******************************************************************************/
void remove_func(int line)
{
    FILE *fptr  = fopen("schedule.csv", "r");
    FILE *ftemp = fopen("replace.txt", "w"); 
    int count;
    char buffer[MAX_BUFF_SIZE];

    /* fopen() return NULL if unable to open file in given mode. */
    if (fptr == NULL || ftemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(0);
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, MAX_BUFF_SIZE, fptr)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
            continue;
        else
            fputs(buffer, ftemp);
    }


    /* Close all files to release resource */
    fclose(fptr);
    fclose(ftemp);
    
    remove("schedule.csv");
    rename("replace.txt", "schedule.csv");
    
}

/******************************************************************************
*
*     FUNCTION NAME   :   add_reminder
*
*     DESCRIPTION     :   This function adds new reminder in the file.
*
*     Parameters     : char *sid - SID for new reminder entered by user.
*                      char *des - Description for the new reminder.
*                      char *date - Date for the new reminder. 
*                      char *status - Status for the new reminder. 
*     
*******************************************************************************/
void add_reminder(char *sid, char *des, char *date, char *status)
{
    FILE *fptr = fopen("schedule.csv", "a");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fptr == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(0);
    }
    
    fprintf(fptr,"%s, %s,%s, %s,\n", sid, des, date, status);
    
    fclose(fptr);
}

/******************************************************************************
*
*     FUNCTION NAME   :   read_schedule
*
*     DESCRIPTION     :   This function reads all reminders from schedule file.
*
*     Parameters     : schedule_t *Schedules - pointer reference for array of structure of structure schedule_t.
*
*     Return Value  : This function return the total no. of reminders from the file. 
*     
*******************************************************************************/ 
int read_schedule(schedule_t *Schedules)
{
    FILE* fp = fopen("schedule.csv", "r");
    int i = 0;
    char buff[MAX_BUFF_SIZE];

    if(fp == NULL)
    {
        printf("\n file failed to open\n");
        perror("Error :");
        exit(0);
    }
    else
    {
        i = 0;
        int field_count = 0;
        int row_count = 0;

        /* This loop is user for tokenizing the schedule sheet and storing in the structure */
        while(fgets(buff, MAX_BUFF_SIZE, fp))
        {
            field_count = 0;
            row_count++;

            char *field = strtok(buff, ",");

            if(row_count == 1)  //for skipping first line which contain labels
                continue;

            /* This loop used for storing the fields in the members of structure */
            while(field)
            {
                if(field_count == 0)
                    strcpy(Schedules[i].s_id, field); 

                if(field_count == 1)
                    strcpy(Schedules[i].des, field); 
 
                if(field_count == 2)
                    strcpy(Schedules[i].date, field); 

                if(field_count == 3)
                    strcpy(Schedules[i].status, field);  

                field = strtok(NULL, ",");
                field_count++;
            }

            i++;
        }
    }

    int number = i;

    fclose(fp);
    
    return number;
}

void show_reminders(schedule_t *Schedules, int tnum, char *user_date)
{
    int i;
    int res, res2;
    int flag = 0;
    for(i = 0; i < tnum; i++)
    {
        res = 1;
        res2 = 1;
        res = strcmp(user_date, Schedules[i].date);
        res2 = strcmp(Schedules[i].status, " Yes");

        if(res == 0 && res2 == 0)
	{
	    flag = 1;
            printf("\nSID = %s\nDescription = %s\n", Schedules[i].s_id, Schedules[i].des);
	}  
    }
    
    if(flag == 0)
        printf("\nThere is no reminder\n");
}
