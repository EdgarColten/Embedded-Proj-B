/*
 * OutputDriver.h
 *
 *  Created on: Sep 26, 2024
 *      Author: LogMa
 */

#include <cstdint>
#include "main.h"
#include "stm32l4xx_hal.h"

//Custom includes
#include "cpp_main.h"
#include "displayQueue.h"
#include "Queue.h"
#include "waveQueue.h"

#ifndef INC_OUTPUTDRIVER_H_
#define INC_OUTPUTDRIVER_H_

#define PI 3.1415926535
#define MAX_SIZE 4096
#define SIZE 255
#define CPU_CLK 80000000

#define PHASE_SHIFT 32 //value to shift the outWave buffer for the delay

class OutputDriver{ // @suppress("Miss copy constructor or assignment operator")
private:

	//IPC attributes
	displayQueue* oledQueue;
	waveQueue* signalQueue;


	//Core attributes
	uint32_t oldFreq1;
	uint32_t oldAmp1;
	uint32_t oldShape1;

	uint32_t freq1;
	uint32_t amp1;
	uint32_t autoReload1;

	uint32_t oldFreq2;
	uint32_t oldAmp2;
	uint32_t oldShape2;

	uint32_t freq2;
	uint32_t amp2;
	uint32_t offset;
	uint32_t autoReload2;

	uint8_t channel;

	//Output wave tables
	uint32_t outWave1[SIZE];
	uint32_t outWave2[SIZE];

	const uint32_t sineWave[SIZE] = {
			2047, 2096, 2145, 2194, 2242, 2291, 2339, 2388,
			2436, 2484, 2531, 2579, 2626, 2672, 2718, 2764,
			2810, 2855, 2899, 2943, 2986, 3029, 3071, 3113,
			3154, 3194, 3234, 3273, 3311, 3348, 3385, 3420,
			3455, 3489, 3523, 3555, 3586, 3617, 3646, 3675,
			3702, 3729, 3754, 3779, 3802, 3824, 3846, 3866,
			3885, 3903, 3920, 3935, 3950, 3963, 3975, 3987,
			3996, 4005, 4013, 4019, 4024, 4028, 4031, 4032,
			4032, 4032, 4029, 4026, 4022, 4016, 4009, 4001,
			3992, 3981, 3970, 3957, 3943, 3928, 3911, 3894,
			3875, 3856, 3835, 3813, 3790, 3766, 3742, 3716,
			3688, 3660, 3631, 3602, 3571, 3539, 3506, 3472,
			3438, 3403, 3366, 3329, 3292, 3253, 3214, 3174,
			3134, 3092, 3050, 3008, 2965, 2921, 2877, 2832,
			2787, 2741, 2695, 2649, 2602, 2555, 2508, 2460,
			2412, 2364, 2315, 2267, 2218, 2169, 2120, 2071,
			2023, 1974, 1925, 1876, 1827, 1779, 1730, 1682,
			1634, 1586, 1539, 1492, 1445, 1399, 1353, 1307,
			1262, 1217, 1173, 1129, 1086, 1044, 1002, 960,
			920, 880, 841, 802, 765, 728, 691, 656, 622, 588,
			555, 523, 492, 463, 434, 406, 378, 352, 328, 304,
			281, 259, 238, 219, 200, 183, 166, 151, 137, 124,
			113, 102, 93, 85, 78, 72, 68, 65, 62, 62, 62, 63,
			66, 70, 75, 81, 89, 98, 107, 119, 131, 144, 159,
			174, 191, 209, 228, 248, 270, 292, 315, 340,
			365, 392, 419, 448, 477, 508, 539, 571, 605, 639,
			674, 709, 746, 783, 821, 860, 900, 940, 981, 1023,
			1065, 1108, 1151, 1195, 1239, 1284, 1330, 1376, 1422,
			1468, 1515, 1563, 1610, 1658, 1706, 1755, 1803, 1852,
			1900, 1949, 1998
	};


	const uint32_t squareWave[SIZE] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	const uint32_t pulseWave[SIZE] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	uint32_t holdOutWave2[SIZE];

	//Setting wave type
	enum waveType shape1; //delay is only for channel 2
	enum waveType shape2; //delay is only for channel 2

	enum waveType shapeHold;


	//packing values for the display
	displayValues dValues;


public:
	OutputDriver(waveQueue*,displayQueue*);
	void update_Channel();
	void calculateAutoReload1();
	void calculateAutoReload2();


	void setAttributes1(waveProp);
	void setAttributes2(waveProp);

	void generateWave(uint8_t);
	void setAutoReload(TIM_HandleTypeDef*,uint8_t);
	void resetCounter(TIM_HandleTypeDef*,uint8_t);

	void delaySet();

	void pack();

};

#endif /* INC_OUTPUTDRIVER_H_ */
