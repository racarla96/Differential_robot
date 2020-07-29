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
#include <fstream>

#include <pigpio.h>

#include "time_cyclic.hpp"

#include "drv8838.hpp"
#include "rotary_encoder.hpp"

/*

TO BUILD

g++ -o control_position_cpp control_position.cpp drv8838.cpp rotary_encoder.cpp -lpigpio -lrt -lpthread

TO RUN

sudo ./control_position_cpp

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

    if (gpioInitialise() < 0) return 1;

    cout << "Running properly!" << endl; 

    drv8838 drv(16, 20);
    re_decoder dec(7, 8);

    ofstream myfile;
    myfile.open ("pos_control.csv");  

    struct period_info pinfo;
    periodic_task_init(&pinfo, 100);

    float SAT = 255;

    float Sensor = 0;
    float Referencia = 10640; // 1 revolution
    float Kp = 0.075;
    float Kd = 0.001;
    float Ki = 0;
    float T = 0.1;
    
    float Proporcional = 0;
    float Integral = 0;
    float Derivativo = 0;
    float Control = 0;
    int int_control = 0;
    float Error = 0;
    float Error_0 = 0;

    for (int i = 0; i < 50; i++){
        Sensor = dec.re_get_counts();

        Error = Sensor - Referencia;
        Proporcional = Error * Kp;
        //Integral = Integral + Error * Ki * T;
        Derivativo = (Error - Error_0) * Kd / T;
        Error_0 = Error;
        Control = Proporcional + Integral + Derivativo;

        int_control = (int) Control;

        if (int_control > 0) {
            if (abs(int_control) > SAT) int_control = SAT;
            drv.setDirection(FORWARD);
            drv.setSpeed(abs(int_control));
        } else if (int_control < 0) {
            if (abs(int_control) > SAT) int_control = SAT;
            drv.setDirection(BACKWARD);
            drv.setSpeed(abs(int_control));
        } else {
            drv.setSpeed(0);
        }

        //myfile << i << ";" << pinfo.next_period.tv_sec << ";" << pinfo.next_period.tv_nsec << ";";
        myfile << Referencia << ";" << Sensor << ";" << Error << ";" << int_control << ";"  << Control << endl;
        wait_rest_of_period(&pinfo);
    }

    drv.setSpeed(0);
    myfile.close();
    return 0;
}

