/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

const float HD_SCALAR = 2.0;

const float UV_ALPHA = 1.0;
const float UV_BETA = 1.0;
const float UV_GAMMA = 1.0;
const float UV_DELTA = 1.0;

const float UVA_A_COEF = 2.22;
const float UVA_B_COEF = 1.33;
const float UVA_C_COEF = 2.95;
const float UVA_D_COEF = 1.75;

void VEML6075_init();
float VEML6075_uva(void);
float VEML6075_uvb(void);
float VEML6075_uvi(void);

/* [] END OF FILE */
