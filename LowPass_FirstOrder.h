#ifndef FILTER_LP_FO_H
#define FILTER_LP_FO_H

typedef struct{

    /* Filter Output */
    float out;

    /* Filter Weights */
    float coeff[2];

    /* Sampling Frequency (Hz) */
    float fs_Hz;

} LowPass_FirstOrder;

void LowPass_FirstOrder_Init(LowPass_FirstOrder *filt, float fc_Hz, float fs_Hz);

void LowPass_FirstOrder_SetCutoff(LowPass_FirstOrder *filt, float fc_Hz);

float LowPass_FirstOrder_Update(LowPass_FirstOrder *filt, float inp);

#endif

