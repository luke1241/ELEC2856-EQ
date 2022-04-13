#include "mbed.h"
#include "HighPass_FirstOrder.c"
#include "LowPass_FirstOrder.c"


#define LPF_FREQ_MAX 500
#define HPF_FREQ_MIN 100

// The sinewave is created on this pin
// Adjust analog output pin name to your board spec.
AnalogIn inputSig(PC_0);

AnalogOut  aout1(PA_4);
AnalogOut  aout2(PA_5);
DigitalOut dout(LED1);

AnalogIn lowAmpIn(PA_0);
AnalogIn lowFreqIn(PA_1);

AnalogIn highAmpIn(PB_0);
AnalogIn highFreqIn(PC_1);

const float offset = 0.5f; 
const float pi     = 3.14159265358979;

float lowAmp;
float lowFreq;

float highAmp;
float highFreq;

int main()
{

    while(true){

        lowAmp = lowAmpIn.read();
        lowFreq = lowFreqIn.read() * LPF_FREQ_MAX;

        highAmp = highAmpIn.read();
        highFreq = 20000 - (highFreqIn.read() * (20000 - HPF_FREQ_MIN));

        int    n = 1000;
        float  input[n];
        float  noise[n];
        float  noisyInput[n];
        float  hpFilteredOutput[n];
        float  lpFilteredOutput[n];
        float  bpFilteredOutput[n];
        float  eqOut[n];
        float  amplitude = 0.1f;
        float  rads = 0.0;

        //Declaring the filter struct variable
        HighPass_FirstOrder hpFilt;
        LowPass_FirstOrder lpFilt;

        
        //Initialise the filter coefficient (the weight)
        HighPass_FirstOrder_Init(&hpFilt, 2000.0f, 48000.0f);
        LowPass_FirstOrder_Init(&lpFilt, 100.0f, 48000.0f);

        HighPass_FirstOrder_SetCutoff(&hpFilt, highFreq);
        LowPass_FirstOrder_SetCutoff(&lpFilt, lowFreq);

        for(int i=0;i<n;i++){   

                input[i] = inputSig.read() - offset;
                //rads          = (pi * i) / 100.0f;
                //noise[i]      = (float)(amplitude * (cos(10*rads + pi))); // 'noise' is 2500 Hz
                //input[i]      = (float)(amplitude * (cos(rads + pi))); // base signal is 250 Hz
                //noisyInput[i] = input[i] + noise[i];

                
                HighPass_FirstOrder_Update(&hpFilt, input[i]);
                hpFilteredOutput[i] = hpFilt.out * highAmp;
                
                LowPass_FirstOrder_Update(&lpFilt, input[i]);
                lpFilteredOutput[i] = lpFilt.out * lowAmp;

               // eqOut[i] = input[i] - lpFilteredOutput[i];
                
                aout1.write(hpFilteredOutput[i]+offset);
                aout2.write(lpFilteredOutput[i]+offset);
            } 
            

            dout = !dout;
            //ThisThread::sleep_for(10ms);

    }
}

/*


            */



