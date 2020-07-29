/*                                                                  
 * POSIX Real Time Example
 * using a single pthread as RT thread
 */
 
#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/mman.h>

#include <iostream>

#include <pigpio.h>

#include "time_cyclic.hpp"

/*

TO BUILD

g++ -o test_periodic_RT_thread_cpp test_periodic_RT_thread.cpp -lpigpio -lrt -lpthread

TO RUN

sudo ./test_periodic_RT_thread_cpp

USEFUL LINKS
*/

using namespace std;
 
int main(int argc, char* argv[])
{
    struct sched_param param;
    pthread_attr_t attr;
    pthread_t thread;
    int ret;

    /* Lock memory */
    if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
        cout << "mlockall failed: %m" << endl;
        exit(-2);
    }

    /* Initialize pthread attributes (default values) */
    ret = pthread_attr_init(&attr);
    if (ret) {
        cout << "init pthread attributes failed" << endl;
        exit(-2);
    }

    /* Set a specific stack size  */
    ret = pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    if (ret) {
        cout << "pthread setstacksize failed" << endl;
        exit(-2);
    }

    /* Set scheduler policy and priority of pthread */
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret) {
        cout << "pthread setschedpolicy failed" << endl;
        exit(-2);
    }
    param.sched_priority = 80;
    ret = pthread_attr_setschedparam(&attr, &param);
    if (ret) {
        cout << "pthread setschedparam failed" << endl;
        exit(-2);
    }

    cout << "Running properly!" << endl; 

    struct period_info pinfo;
    periodic_task_init(&pinfo, 100);

    for (int i = 0; i < 1000 * 1000; i++){
            cout << i << " " << pinfo.next_period.tv_sec << " " << pinfo.next_period.tv_nsec << endl;
            wait_rest_of_period(&pinfo);
    }

    return 0;
}

