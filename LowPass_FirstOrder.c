#include "LowPass_FirstOrder.h"

void LowPass_FirstOrder_Init(LowPass_FirstOrder *filt, float fc_Hz, float fs_Hz) {

    /* Store sampling frequency and compute filter weights */
    filt->fs_Hz = fs_Hz;

    LowPass_FirstOrder_SetCutoff(filt, fc_Hz);

    /* Reset Ouput */
    filt->out = 0.0f;

}

void LowPass_FirstOrder_SetCutoff(LowPass_FirstOrder *filt, float fc_Hz) {

    /* Clamp cut-off frequency: 0 <= fc <= fs/2 */
    if (fc_Hz > (0.5f * filt->fs_Hz)){

        fc_Hz = 0.5f * filt->fs_Hz;

    } else if (fc_Hz < 0.0f){

        fc_Hz = 0.0f;
    }

    /* Compute and Store Filter Weights */
    float alpha = 6.28318530718f * fc_Hz / filt->fs_Hz; /* alpha = 2*pi*fc / fs */

    filt->coeff[0] = alpha / (1.0f + alpha); /* alpha / (1+alpha) */
    filt->coeff[1] = 1.0f / (1.0f + alpha); /* 1 / (1+alpha) */
}

float LowPass_FirstOrder_Update(LowPass_FirstOrder *filt, float inp) {
    
    /* Perform IIR filter update to compute newest output sample
    * Vout[n] = alpha / (1+alpha) * Vin[n] + 1 / (1+alpha) * Vout[n-1]
    */

    filt->out = filt->coeff[0] * inp + filt->coeff[1] * filt->out;

    /*Clamp output: -1 < out < +1 */
    if (filt->out >1.0f){

        filt->out = 1.0f;

    } else if (filt->out <-1.0f) {

        filt->out = -1.0f;

    }

    /* Return Filter Output */
    return filt->out;

}