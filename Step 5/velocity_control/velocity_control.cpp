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

g++ -o velocity_control_cpp velocity_control.cpp drv8838.cpp rotary_encoder.cpp -lpigpio -lrt -lpthread

TO RUN

sudo ./velocity_control_cpp

USEFUL LINKS
*/

#define M_PI 3.14159265358979323846  /* pi */

#define CPR 7   // Counts per revolution
#define MRR 380 // Motor reduction ratio
#define QER 4   // Quadrature encoder resolution

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

    // Left Motor
    //drv8838 drv(3, 2);
    //re_decoder dec(15, 18);
    // Right Motor
    drv8838 drv(22, 27);
    re_decoder dec(23, 24);

    ofstream myfile;
    myfile.open ("vel_control.csv");  

    struct period_info pinfo;
    periodic_task_init(&pinfo, 100);

    float SAT = 255;

    float Kp = 0;
    float Kd = 0;
    float Ki = 150;
    float T = 0.05;

    long Prev_Sensor = 0;
    long Delta_Sensor = 0;
    float Sensor = 0;
    float Referencia = 2; // rad/s - Max: 10.90 - Min: 
    float Input = 0;
    
    float Proporcional = 0;
    float Integral = 0;
    float Derivativo = 0;
    float Control = 0;
    int int_control = 0;
    float Error = 0;
    float Error_0 = 0;

    int direction = FORWARD;
    if (Referencia < 0) {
        Referencia = -Referencia;
        direction = BACKWARD;
        drv.setDirection(direction);
    }

    for (int i = 0; i < 100; i++) {
        Sensor = dec.re_get_counts();
        Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
        Input = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

        Error = Referencia - Input;
        Proporcional = Error * Kp;
        Integral = Integral + Error * Ki * T;
        Derivativo = (Error - Error_0) * Kd / T;

        Prev_Sensor = Sensor;
        Error_0 = Error;
        
        Control = Proporcional + Integral + Derivativo;

        int_control = (int) Control;
        if (int_control > SAT) int_control = SAT;
        if (int_control < 0) int_control = 0;
        drv.setSpeed(int_control);

        //myfile << i << ";" << pinfo.next_period.tv_sec << ";" << pinfo.next_period.tv_nsec << ";";
        //myfile << Referencia << ";" << Input << ";" << Error << ";" << int_control << ";"  << Control << endl;
        cout << Referencia << ";" << Input << ";" << Error << ";" << int_control << endl;
        wait_rest_of_period(&pinfo);
    }

    drv.setSpeed(0);
    myfile.close();
    return 0;
}

