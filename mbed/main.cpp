#include "mbed.h"
#include "platform/mbed_thread.h"
#define SLEEP_RATE 500

AnalogOut lamppu(PA_4); //PA_4 alias A2
DigitalOut trigger(D8);
DigitalIn echo(D9);

Timer get_time;

float sensor(void);

float sensor(void)
{
    float distance;
    trigger.write(1);
    wait_us(10);
    trigger.write(0);

    while(echo.read() == 0) {}
    get_time.reset();
    get_time.start();

    while(echo.read() == 1) {}
    get_time.stop();
    distance = get_time.read_us();
    distance = distance * 0.03432f / 2.0f;

    return distance;
}

int main()
{
     lamppu.write_u16(0);
     DigitalOut led(LED1);
     
     trigger = 0;
     float distance2;
     
     while(true){
         distance2 = sensor();
         led = !led;
         
         if(distance2 < 15)
         {
             printf("Liiketta tunnistettu\n\r");
             lamppu.write_u16(65534);
             thread_sleep_for(2000);
         }
         else
         {
             lamppu.write_u16(0);
         }
         
         thread_sleep_for(SLEEP_RATE);
    }
}

