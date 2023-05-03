#include<stdio.h>
#include<time.h>

/*
TASK UNDERSTANDING:
    - Schedule
        - Binary string of 48.
            - DESIGN:  Could use character array[48+'\0'] or a double data type to hold that many bits?
        - Digit/bit represents heater state per half hour period
    - Schedules received via STDIN
        - Can be updated anytime via STDIN, so need system to keep listening and updating schedule.
    - Prints "on" or "off" to STDOUT at appropriate times.
*/

#define TIME_DURATION_SECONDS 1800 //Determines seconds to wait until we consult scheduler. 1800s = 30 minutes.
#define ARRAY_SIZE 49 //Determines total array size to store 48 digits plus '\0' null terminator.

int main()
{
    //Variable declarations
    char cSchedule[ARRAY_SIZE] = { "000000001010101011111111000011110000111111111111\0"};
    unsigned iIndex = ARRAY_SIZE - 2;  //Start from least significant bit
    time_t tTimer = time(NULL) + TIME_DURATION_SECONDS; //Determine when timer will expire.

    while (1)
    {
        /*TASK 1:  Listening for stdin, update schedule upon receiving update*/



        /*TASK 2:  Observe time and print "ON", "OFF" depending on time and schedule.*/
        time_t tCurrentTime = time(NULL);  //Retrieve current time for comparison

        if (tTimer == tCurrentTime) //If 30 minutes elapsed
        {
            if ('1' == cSchedule[iIndex])  //IF digit is 1 then print "ON", else "OFF", as per specification
                printf("ON\n");
            else
                printf("OFF\n");

            // DESIGN DECISION:  
            // Once 24hours elapsed and all bits observed, we will move index back to least significant.
            // then repeat the process for next 24 hours.
            if (0 == iIndex) //IF at index 0, restart from position of least significant bit
                iIndex = ARRAY_SIZE - 2;
            else //decrement normally
                iIndex--;  

            //Recalculate when timer should next expire.
            tTimer = tCurrentTime + TIME_DURATION_SECONDS;
        }
    }

    return 0;
}
