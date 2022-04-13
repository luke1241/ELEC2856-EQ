#include "HighPass_FirstOrder.h"

void HighPass_FirstOrder_Init(HighPass_FirstOrder *filt, float fc_Hz, float fs_Hz) {

    /* Store sampling frequency and compute filter weights */
    filt->fs_Hz = fs_Hz;

    HighPass_FirstOrder_SetCutoff(filt, fc_Hz);

    /* Reset Ouput */
    filt->out = 0.0f;
    filt->inp = 0.0f;

}

void HighPass_FirstOrder_SetCutoff(HighPass_FirstOrder *filt, float fc_Hz) {

    /* Clamp cut-off frequency: 0 <= fc <= fs/2 */
    if (fc_Hz > (0.5f * filt->fs_Hz)){

        fc_Hz = 0.5f * filt->fs_Hz;

    } else if (fc_Hz < 0.0f){

        fc_Hz = 0.0f;
    }

    /* Compute and Store Filter Weights */
    float alpha = 6.28318530718f * fc_Hz / filt->fs_Hz; /* alpha = 2*pi*fc / fs */

    filt->coeff = 1.0f / (1.0f + alpha); /* 1 / (1+alpha) */
}

float HighPass_FirstOrder_Update(HighPass_FirstOrder *filt, float inp) {
    
    /* Perform IIR filter update to compute newest output sample
    * Vout[n] = 1 = / (1+ alpha) * (Vin[n] - Vin[n-1] + Vout[n-1])
    */

    filt->out = filt->coeff * (inp - filt->inp + filt->out);

    /*Clamp output: -1 < out < +1 */
    if (filt->out >1.0f){

        filt->out = 1.0f;

    } else if (filt->out <-1.0f) {

        filt->out = -1.0f;

    }
    /* Return Filter Output */
    return filt->out;
}
