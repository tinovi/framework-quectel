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
////////////////////////////////////////////////////////////////////////////

#ifndef HAL_H_
#define HAL_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <mt2625.h>

//////////////////////////////////////////////////////////////////////////////////////
//  GPIO
//
//      Befiore use init pin, call Ql_GPIO_Init();  
//      pin = MTK_GPIO_ID (look arduino pin table)
//////////////////////////////////////////////////////////////////////////////////////
int hal_gpio_set_direction(uint32_t pin, uint32_t direction); // 0 = input, 1 = output
int hal_gpio_get_input(uint32_t pin, uint32_t *pData);
int hal_gpio_set_output(uint32_t pin, uint32_t data);

#ifdef __cplusplus
}
#endif
#endif