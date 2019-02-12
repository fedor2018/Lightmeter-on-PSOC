
/* ========================================
 *
 The following firmware was developed by Cypress Semiconductor
This work is licensed under a Creative Commons Attribution 3.0 Unported License.
http://creativecommons.org/licenses/by/3.0/deed.en_US
You are free to:
-To Share — to copy, distribute and transmit the work 
-To Remix — to adapt the work 
-To make commercial use of the work
* ========================================
*/

/*
  LCDShield.cpp - Arduino Library to control a Nokia 6100 LCD, 
  specifically that found on SparkFun's Color LCD Shield.
  This code should work for both Epson and Phillips display drivers 
  normally found on the Color LCD Shield.
	
  License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
  to use and abuse this code however you'd like. If you find it useful
  please attribute, and SHARE-ALIKE!
  
  This is based on code by Mark Sproul, and Peter Davenport.
  Thanks to Coleman Sellers and Harold Timmis for help getting it to work with the Phillips Driver 7-31-2011
*/ 

#include "device.h"
#include "ColorLCDShield.h"

uint8 driver;

uint8 x_offset;
uint8 y_offset;

//Main function parameters
#define TOTAL_ADC_SAMPLES 1024
#define TOTAL_SELECTED_SAMPLES 128
#define TIME_SCALE_ARRAY 10

uint8 realSamples[TOTAL_ADC_SAMPLES];	//Real samples holder
uint16 realsamplescounter;	//Counter

uint8 avgofrealsamples;	//A variable to hold the average of all the realsamples 

uint8 sampledValue[TOTAL_SELECTED_SAMPLES] = {0};	//Array to hold sample values to be displayed
uint8 samplesCounter;	//Counter

//Interrupt flags
extern uint8 voltagescale_flag;
extern uint8 timescale_flag;
extern uint8 parameters_flag;

//Scaling factors
uint8 voltagescale = 1;
uint8 timescale = 1;

//Time scale values......Enter your values to fit in the desired frequency signal onto the Color LCD
uint16 time_scale_values[TIME_SCALE_ARRAY] = {2, 50, 125, 200, 255, 400, 500, 700, 800, 1000};

//Functions called from main
//Display the wave parameters
void displayparameters(void)
{
	uint8 minvalue = 0, maxvalue = 0, maxfound, minfound, dispval;
	uint16 minpos, maxpos, diff, diff1;
	float convert;
	
	maxpos = 3;	//The search for the max value starts, keeping the third value of the realsamples array as the max value
	maxfound = 0;	// Max value is not yet found!
	while(maxfound!=1 && maxpos!= (TOTAL_ADC_SAMPLES-1))
	{
		//Compare the current value with 3 values neighbouring to it 
		if((realSamples[maxpos - 3] <= realSamples[maxpos]) && (realSamples[maxpos - 2] <= realSamples[maxpos]) 
		&& (realSamples[maxpos - 1] <= realSamples[maxpos]) && (realSamples[maxpos + 1] <= realSamples[maxpos]) 
		&& (realSamples[maxpos + 2] <= realSamples[maxpos]) && (realSamples[maxpos + 3] <= realSamples[maxpos]))
		{	
			maxfound = 1;	// First max value in the real samples array is found
			maxvalue = realSamples[maxpos];	// Notethe value of first max value
			
		}
		else
		{
			maxpos = maxpos + 1;	// Increment the index 
				
		}
		
	}
	
	minfound = 0;	//The search for the min value starts, keeping the third value of the realsamples array as the min value
	minpos = 3;	//Min value is not yet found!
	while(minfound!=1 && minpos!= (TOTAL_ADC_SAMPLES-1))
	{
		//Compare the current value with 3 values neighbouring to it 
		if( (realSamples[minpos - 3] >= realSamples[minpos]) && (realSamples[minpos - 2] >= realSamples[minpos]) 
		&& (realSamples[minpos - 1] >= realSamples[minpos]) && (realSamples[minpos + 1] >= realSamples[minpos]) 
		&& (realSamples[minpos + 2] >= realSamples[minpos]) && (realSamples[minpos + 3] >= realSamples[minpos]))
		{	
			minfound = 1;	// First min value in the real samples array is found
			minvalue = realSamples[minpos];	// Notethe value of first min value
		}
		else
		{
			minpos = minpos + 1;	// Increment the index 
				
		}
	}
	if((minfound == 1) && (maxfound == 1))	// If both min and max values are found then display the parameters of signal else display ?
	{
			diff = maxvalue - minvalue;	// Find the difference between the max and min values
			convert = diff * 3.3 /128;	// Calculate the Vp-p 
			/* Display the amplitude */
			setStr("Vpp=", 30, 8, RED, BLACK);
			diff = convert;
			setChar(diff + 48, 64, 40, RED, BLACK);
			setChar('.', 64, 48, RED, BLACK);
			convert = convert - diff;
			convert = convert * 10;
			diff = convert;
			setChar(diff + 48, 64, 55, RED, BLACK);
			convert = convert - diff;
			convert = convert*10;
			diff = convert;
			setChar(diff + 48, 64, 64, RED, BLACK);
			
			/* Find the diference between the max value and min value positions */
			if(maxpos > minpos)
			{
				diff = maxpos - minpos;
			}
			else
			{ diff = minpos - maxpos; 
			}
			
			/* Calculate the frequency */
			diff = 2*diff;
			convert = 400000/((PWM_ReadPeriod()+1)*diff);
			diff = (uint16)convert;
			
			/* Display the frequency */
			setStr("Frequency=", 72, 4, RED, BLACK);
			
			diff1 =diff;
			diff1 = diff1%10;
			dispval = (uint8)diff1;
			setChar(dispval + 48, 110 , 64, RED, BLACK);
			diff = diff/10;
			
			diff1 =diff;
			diff1 = diff1%10;
			dispval = (uint8)diff1;
			setChar(dispval + 48, 110 , 56, RED, BLACK);
			diff = diff/10;
			
			diff1 =diff;
			diff1 = diff1%10;
			dispval = (uint8)diff1;
			setChar(dispval + 48, 110 , 48, RED, BLACK);
			diff = diff/10;
			
			diff1 =diff;
			diff1 = diff1%10;
			dispval = (uint8)diff1;
			setChar(dispval + 48, 110 , 40, RED, BLACK);
			diff = diff/10;
			
			diff1 =diff;
			diff1 = diff1%10;
			dispval = (uint8)diff1;
			setChar(dispval + 48, 110 , 32, RED, BLACK);
			diff = diff/10;
			
	}
	else
	{
			setChar('V', 124, 8, RED, BLACK);
			setChar('p', 124, 16, RED, BLACK);
			setChar('p', 124, 24, RED, BLACK);
			setChar('=', 124, 32, RED, BLACK);
			setChar('?', 124, 40, RED, BLACK);
			setChar(' ', 124, 48, RED, BLACK);
			setChar(' ', 124, 55, RED, BLACK);
	}
}

//Collect real samples
void collectSamplesfunc(void)
{
	ADC_Start();		// Start the ADC
	ADC_IRQ_Enable();	// Enable the ADC interrupt
	
	realsamplescounter = 0;	// Initialise the samples counter
	
	ADC_StartConvert();	// Start the ADC conversion
	
	
	// Accumulate 1024 samples 
	while(realsamplescounter != (TOTAL_ADC_SAMPLES - 1))
	{
		// wait
	}
	
	ADC_StopConvert();	//Stop the ADC conversion
	ADC_Stop();	//Stop the ADC
}

//Find out the average of all the collected samples
void averageSamplesfunc(void)
{
float sum = 0;
	for(realsamplescounter = 1; realsamplescounter < TOTAL_ADC_SAMPLES -1 ; realsamplescounter++)
	{
		sum = sum + realSamples[realsamplescounter];
	}
	sum = sum/realsamplescounter ;
	sum = sum/voltagescale;
	avgofrealsamples = (uint8)sum;
}

//Select suitable samples to be displayed on GLCD
void selectSamplesfunc(void)
{	
	realsamplescounter = 0;
	
	while( realsamplescounter != (TOTAL_ADC_SAMPLES - TOTAL_SELECTED_SAMPLES ))
	{
		// Select 127 samples starting with value, greater than the average value and its neighbouring value greater than its value
		if((realSamples[realsamplescounter] > (avgofrealsamples)) && (realSamples[realsamplescounter + 1] >= realSamples[realsamplescounter]))
		{
			for(samplesCounter = 0; samplesCounter < (TOTAL_SELECTED_SAMPLES -1); samplesCounter++)
			{	
				sampledValue[samplesCounter] = ( realSamples[realsamplescounter]/voltagescale) ;
				realsamplescounter++;
			}
			break;
		}
		realsamplescounter++;
	}
}

//Display the selected samples on GLCD
void displaySamplesfunc(void)
{
//Display the Waveform
	for(samplesCounter = 1; samplesCounter < (TOTAL_SELECTED_SAMPLES-1); samplesCounter++)
	{
		setLine(0 , samplesCounter, 132, samplesCounter, BLACK);	//Clear the previously written pixel
		
		setLine((128 -  sampledValue[samplesCounter]) , samplesCounter,(128 - sampledValue[samplesCounter - 1]),samplesCounter - 1, GREEN);

	}
}

void main()
{	
	uint8 localcounter;
	
	SPIM_Start();	// Start the SPIM component
	PWM_Start();	// Start the PWM component
	
	PWM_WritePeriod(time_scale_values[0]);	//Write the period of the PWM with the first value in the time_scale_value array
	
	Clock_PWM_Start();	// Start the clocks for PWM, SPIM and Debouncer
	Clock_SPIM_Start();
	Clock_Button_Start();	
	
	/* Initialise the Color LCD */
	driver = 0;
	on();
	init(PHILIPS,0);  	// Initializes lcd, using an PHILIPS driver
  	contrast(-51);  	// -51's usually a good contrast value
  	clear(BLACK);  		// oooh, black!
	////////////////////////////////////////
	
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
	
	// Clear any pending interrupts 
	isr_Voltage_Scale_ClearPending();
	isr_Time_Scale_ClearPending();
	isr_Parameters_ClearPending();
	
	// Start all the isrs
	isr_Voltage_Scale_Start();
	isr_Time_Scale_Start();
	isr_Parameters_Start();
	
	
	for(;;)
    {	

		collectSamplesfunc();	// Collect the samples
		averageSamplesfunc();	// Average the collected samples
		selectSamplesfunc();	// Select the suitable samples
		displaySamplesfunc();	// Display the selected samples
		
		// Check for voltage scale flag
		if(voltagescale_flag)
		{
			voltagescale_flag = 0x00;	// Clear the flag
			voltagescale = (voltagescale + 1) % 5;	// Increment the voltagescale value
			if(voltagescale == 0)
			{
				voltagescale = 1;	// If voltagescale value is 0 set it to 1
			}
			
		}
		
		// Check for time scale flag
		if(timescale_flag)
		{
			timescale_flag = 0x00;	// Clear the flag
			timescale = (timescale + 1)% TIME_SCALE_ARRAY;	// Increment the timescale value 
			PWM_WritePeriod(time_scale_values[timescale]);	// Write the period of PWM with the corresponding value in time_scale_values array

		}
		
		// Check for the parameter flag
		if(parameters_flag)
		{
			parameters_flag = 0;	// Clear the flag
			clear(BLACK);
			for(localcounter = 0; localcounter <10; localcounter++)
			{
				displayparameters();	//Display the parameters of the signal
				CyDelay(500);			// Provide a delay of 0.5s 
				collectSamplesfunc();	//Collect the samples to find their parameters
			}
			clear(BLACK);	//Clear the display
		}

    }
}

/* [] END OF FILE */
