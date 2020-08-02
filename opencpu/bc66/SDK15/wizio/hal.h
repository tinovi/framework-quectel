////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Georgi Angelov
//      Basic library and helpers for Arduino
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
// Helper for fast access
// Usage: #include <hal.h>
//
////////////////////////////////////////////////////////////////////////////

#ifndef HAL_H_
#define HAL_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <mt2625.h>

#define REG_32(addr)                    (*(volatile uint32_t*)(addr))
#define REG_16(addr)                    (*(volatile uint16_t*)(addr))

//////////////////////////////////////////////////////////////////////////////////////
//  SYSTICK
// 		Oscilator   = 13M ???
//		ReloadValue = 0x10000000;
//////////////////////////////////////////////////////////////////////////////////////
#define GET_SYS_TICK 					SysTick.VAL	
	
//////////////////////////////////////////////////////////////////////////////////////
//  GPIO
//
//      Befiore use init pin, call Ql_GPIO_Init();  
//      pin = MTK_GPIO_ID (look arduino pin table)
//////////////////////////////////////////////////////////////////////////////////////
int hal_gpio_set_direction(uint32_t pin, uint32_t direction); // 0 = input, 1 = output
int hal_gpio_get_input(uint32_t pin, uint32_t *pData);
int hal_gpio_set_output(uint32_t pin, uint32_t data);

typedef enum
{
	HAL_GPIO_DRIVING_CURRENT_4MA = 0x0,
	HAL_GPIO_DRIVING_CURRENT_8MA = 0x1,
	HAL_GPIO_DRIVING_CURRENT_12MA = 0x2,
	HAL_GPIO_DRIVING_CURRENT_16MA = 0x3,
} hal_gpio_driving_current_t;
int hal_gpio_set_driving_current(uint32_t pin, hal_gpio_driving_current_t driving);

int hal_pinmux_set_function(uint32_t gpio_pin, uint8_t function_index); // TODO
	
//////////////////////////////////////////////////////////////////////////////////////
//  GPT
//      GPT4 is userware, connected to 1Mhz
//      GPT5 is userware, connected to 32K
//////////////////////////////////////////////////////////////////////////////////////
#define GPT_CURRENT_COUNT(G)     G->GPT_COUNT
uint32_t gpt_convert_ms_to_32k_count(uint32_t ms);
void gpt_delay_time(GPT_REGISTER_T *gpt /*GPT4, GPT5*/, const uint32_t count);

//////////////////////////////////////////////////////////////////////////////////////
//  PWM
//      OpenCPU use PWM_1
//////////////////////////////////////////////////////////////////////////////////////
int hal_pwm_set_duty_cycle(PWM_REGISTER_T *pwm, uint32_t duty_cycle);	
	
#ifdef __cplusplus
}
#endif
#endif
