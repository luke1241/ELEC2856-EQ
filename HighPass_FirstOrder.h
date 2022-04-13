#ifndef FILTER_HP_FO_H
#define FILTER_HP_FO_H

typedef struct{

    /* Filter Output */
    float out;

    /* Previous filter input */
    float inp;
    
    /* Filter Weights */
    float coeff;

    /* Sampling Frequency (Hz) */
    float fs_Hz;

} HighPass_FirstOrder;

void HighPass_FirstOrder_Init(HighPass_FirstOrder *filt, float fc_Hz, float fs_Hz);

void HighPass_FirstOrder_SetCutoff(HighPass_FirstOrder *filt, float fc_Hz);

float HighPass_FirstOrder_Update(HighPass_FirstOrder *filt, float inp);

#endif