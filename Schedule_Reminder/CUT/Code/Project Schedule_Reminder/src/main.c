/*******************************************************************************
*
*     FILENAME       :    main.c
*
*     DESCRIPTION    :    This file defines the main function.
*                         It is used for performing different operations.
*
*******************************************************************************/

#include "reminder.h"

int main()
{

    schedule_t Schedules[MAX_SCHEDULE];    
    int tschedule = read_schedule(Schedules);
    int i;
    int line, choice;
    char sid[SID_SIZE];
    char des[DES_SIZE];
    char date[DT_SIZE];
    char status[ST_SIZE];
    int res = 1;
    
    do
    {
        printf( "\n1.Display all reminders\n");
        printf("2.Remove the reminder\n");
        printf("3.Modify the reminder\n");
        printf("4.Add new reminder\n");
        printf("5.Show the reminders for a date\n");
        printf("6.Show the reminders for today\n");
        printf("7.Exit \n");
        printf("\nEnter your choice - ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: {
                        /* Display all reminders */ 
                        tschedule = read_schedule(Schedules);
                        printf("\nTotal Number of Schedule = %d\n", tschedule);
                        printf("\nSID, Description, Date, Status");

                        for(i = 0; i < tschedule; i++)   
                            printf("\n%s, %s, %s, %s", Schedules[i].s_id, Schedules[i].des, Schedules[i].date, Schedules[i].status);
                        printf("\n");
                        break;
                    }

            case 2: {
                         /* Perform deletion */
                        printf("\nEnter the SID of the reminder - ");
                        scanf("%s", sid);

                        for(i = 0; i < tschedule; i++)
                        {
                            res = strcmp(sid, Schedules[i].s_id);
                            
                            if(res == 0)
                            {
                                 line = i+2;
                                 break;
                            }
                        }
                        
                        if(res != 0)
                            printf("\nYou entered invalid SID\n");
                        else
                        {
                            remove_func(line);
                            printf("\nGiven SID is removed\n");
                        }

                        res = 1; 
                       
                        break;
                    }

            case 3: {
                        /* Perform Modification */
                        printf("\nEnter the SID of the reminder - ");
                        scanf("%s", sid);
                        getchar();

                        for(i = 0; i < tschedule; i++)
                        {
                            res = strcmp(sid, Schedules[i].s_id);
                            
                            if(res == 0)
                            {
                                 line = i+2;
                                 break;
                            }
                        }
                        
                        if(res != 0)
                            printf("\nYou entered invalid SID\n");
                        else
                        {
                            printf("Enter Description - ");
                            gets(des);
                            printf("Enter Date in dd/mm/yy format - ");
                            gets(date);
                            printf("Enter Status - ");
                            gets(status);
                            modify(line, sid, des, date, status);
                                 
                            printf("\nGiven SID is modified\n");
                        }
                        res = 1;   
                       
                        break;
                    }
          
            case 4: {
                        /* Adding new reminder */
                        tschedule = read_schedule(Schedules);

                        printf("\nEnter the SID of the reminder - ");
                        scanf("%s", sid);

                        int flag = 0;
                        res = 1;
                        for(i = 0; i < tschedule; i++)
                        {
                            res = strcmp(sid, Schedules[i].s_id);
             
                            if(res == 0)
                            {
                                flag = 1;
                                break;
                            }
                        }
                        
                        if(flag == 1)
                            printf("\nThis SID is already exist\n");
                        else
                        { 
                            getchar();
                            printf("Enter Description - ");
                            gets(des);
                            printf("Enter Date in dd/mm/yy format - ");
                            gets(date);
                            printf("Enter Status - ");
                            gets(status);

                            add_reminder(sid, des, date, status);
                            printf("\nNew reminder is successfully added\n");
                        }
                        flag = 0;
                        res = 1;

                        break;
                    }

            case 5 : {
                        /* Display reminders for the given date*/ 
                        tschedule = read_schedule(Schedules);
                        char u_date[DT_SIZE];
                        printf("\nEnter the date in dd/mm/yy format - ");
                        scanf("%s", u_date);
                        show_reminders(Schedules, tschedule, u_date);
                        
                        break;
                    }
                        
            case 6 : {
                        /* Display reminders for today*/ 
                        tschedule = read_schedule(Schedules);

                        char today_date[DT_SIZE];
                        time_t t;
                        struct tm *DT;
                        time(&t);
                        DT = localtime(&t);
                        strftime(today_date, DT_SIZE, "%d/%m/%y", DT);

                        printf("\n====Reminders for today====\n");
                        show_reminders(Schedules, tschedule, today_date);
                        
                        break;
                    }

            case 7 : exit(0);

            default: {
                        printf("\nPlease enter a valid option\n");
                        break;
                     }
        }
    }while(choice != 7);

    return 0;
}
