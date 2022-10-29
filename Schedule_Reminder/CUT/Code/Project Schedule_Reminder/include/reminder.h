/*******************************************************************************
*
*     FILENAME       :    reminder.h
*
*     DESCRIPTION    :    This file defines the structure used in the project.
*
*******************************************************************************/
#ifndef __REMINDER_H__
#define __REMINDER_H__

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

/********************** Macros Declaration *************************************/
#define MAX_BUFF_SIZE 100
#define DT_SIZE 30
#define DES_SIZE 150
#define SID_SIZE 15
#define ST_SIZE 10
#define MAX_SCHEDULE 200

/********************** Structure Definition **********************************/
typedef struct schedule
{
    char s_id[SID_SIZE];
    char des[DES_SIZE];
    char date[DT_SIZE];
    char status[ST_SIZE];
}schedule_t;

/********************** Functions Declaration **********************************/
void modify(int line, char *sid, char *des, char *date, char *status);
void remove_func(int line);
void add_reminder(char *sid, char *des, char *date, char *status);
int read_schedule(schedule_t *Schedules);
void show_reminders(schedule_t *Schedules, int tnum, char *user_date);

#endif
