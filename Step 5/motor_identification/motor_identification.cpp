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

g++ -o motor_identification_cpp motor_identification.cpp drv8838.cpp rotary_encoder.cpp -lpigpio -lrt -lpthread

TO RUN

sudo ./motor_identification_cpp

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

    drv8838 drv(16, 20);
    re_decoder dec(7, 8);

    ofstream myfile;
    myfile.open ("motor_identification.csv");  

    struct period_info pinfo;
    periodic_task_init(&pinfo, 50);

    float T = 0.05;

    float Sensor = 0;
    float Delta_Sensor = 0;
    float Prev_Sensor = 0;
    float Output = 0;
    float Input = 0;

    drv.setDirection(FORWARD);

    for (int i = 0; i <= 5; i++) {
        for(int j = 0; j < 20; j++) { // 1 second
            Input = i*50;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }
    }

    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 20; j++) { // 1 second
            Input = (4-i)*50;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }
    }

    drv.setDirection(BACKWARD);

    for (int i = 0; i <= 5; i++) {
        for(int j = 0; j < 20; j++) { // 1 second
            Input = i*50;
            drv.setSpeed(i*50);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }
    }

    for (int i = 0; i < 5; i++) {
        for(int j = 0; j < 20; j++) { // 1 second
            Input = (4-i)*50;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;
            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }
    }

    drv.setDirection(FORWARD);

    for (int i = 0; i <= 2; i++) {
        for(int j = 0; j < 40; j++) { // 2 seconds
            Input = (2-i)*100+50;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }

        for(int j = 0; j < 40; j++) { // 2 seconds
            Input = 0;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }
    }

    drv.setDirection(BACKWARD);

    for (int i = 0; i <= 2; i++) {
        for(int j = 0; j < 40; j++) { // 2 seconds
            Input = (2-i)*100+50;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }

        for(int j = 0; j < 40; j++) { // 2 seconds
            Input = 0;
            drv.setSpeed(Input);

            Sensor = dec.re_get_counts();
            Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
            Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

            Prev_Sensor = Sensor;

            myfile << Input << ";" << Output << endl;
            wait_rest_of_period(&pinfo);
        }
    }   

    drv.setDirection(FORWARD);

    for (int i = 0; i < 256; i++) {
        Input = i;
        drv.setSpeed(Input);

        Sensor = dec.re_get_counts();
        Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
        Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

        Prev_Sensor = Sensor;

        myfile << Input << ";" << Output << endl;
        wait_rest_of_period(&pinfo);
    }

    for (int i = 0; i < 256; i++) {
        Input = (255 - i);
        drv.setSpeed(Input);

        Sensor = dec.re_get_counts();
        Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
        Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

        Prev_Sensor = Sensor;

        myfile << Input << ";" << Output << endl;
        wait_rest_of_period(&pinfo);
    }

    drv.setDirection(BACKWARD);

    for (int i = 0; i < 256; i++) {
        Input = i;
        drv.setSpeed(Input);

        Sensor = dec.re_get_counts();
        Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
        Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

        Prev_Sensor = Sensor;

        myfile << Input << ";" << Output << endl;
        wait_rest_of_period(&pinfo);
    }

    for (int i = 0; i < 256; i++) {
        Input = (255 - i);
        drv.setSpeed(Input);

        Sensor = dec.re_get_counts();
        Delta_Sensor = (float) abs(Prev_Sensor - Sensor);
        Output = (2 * M_PI * (Delta_Sensor / ((float)(CPR * MRR * QER)))) / T;

        Prev_Sensor = Sensor;

        myfile << Input << ";" << Output << endl;
        wait_rest_of_period(&pinfo);
    }

    drv.setSpeed(0);
    myfile.close();
    return 0;
}

