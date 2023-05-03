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

/*
ASSUMPTIONS / DESIGN DECISIONS:
    - It is assumed upon first start, a default schedule is already given.
        - Default schedule taken from example given in Git website (https://github.com/benwhite45/coding-exercise)

    - It is assumed 1 = "ON" and 0 = "OFF".
    
    - Decided to go for character array, with index starting at least significant digit (right going left)
        - Upon reaching index 0 (and 24hrs elapsed), index will restart at least significant digit (47) and repeat process.
*/

/*
TESTS PERFORMED:
    - Performed test by setting TIME_DURATION_SECONDS to 5 seconds instead of 1800.
            - Observing first 16 outputs (using default schedule) "0000111111111111"
                1. Confirm 12 "ON" is printed
                    - PASS
                2. Confirm 4 "OFF" is printed
                    - PASS
*/

/*
WHAT I COULD DO GIVEN MORE TIME:
    1.  I would continue looking into thread/child alternatives on Windows to complete task 1 (listening to STDIN), with main aspect of program 
        (timer, printing "ON" and "OFF") continuing to function in parallel.
            - Or, invest time to set up code on Linux via Windows SubSystem for Linux 2 on my system, 
              to leverage POSIX / parent-child capabilities.

    2.  Although Step 2 has been completed, it is inefficient, due to constant CPU core utilisation without any breaks.
        With more time, I could look at implementing a suitable solution to make process sleep and being less CPU intensive.
        (Maybe used sleep()
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
