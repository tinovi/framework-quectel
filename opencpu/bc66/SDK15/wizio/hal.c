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

#include <hal.h>

//////////////////////////////////////////////////////////////////////////////////////
//  GPIO
//
//      Befiore use init pin, call Ql_GPIO_Init();
//      pin = MTK_GPIO_ID (look arduino pin table)
//////////////////////////////////////////////////////////////////////////////////////

static GPIO_BASE_REGISTER_T *gpio_base = (GPIO_BASE_REGISTER_T *)(GPIO_BASE);

int hal_gpio_set_direction(uint32_t pin, uint32_t direction) // 0 = input, 1 = output
{
    if (pin > 36)
        return -2;
    uint32_t no = pin / 32;
    uint32_t remainder = pin % 32;
    if (direction)
        gpio_base->GPIO_DIR.SET[no] = (1 << remainder);
    else
        gpio_base->GPIO_DIR.CLR[no] = (1 << remainder);
    return 0;
}

int hal_gpio_get_input(uint32_t pin, uint32_t *p)
{
    if (pin > 36)
        return -2;
    if (!p)
        return -1;
    uint32_t no = pin / 32;
    uint32_t remainder = pin % 32;
    uint32_t temp = gpio_base->GPIO_DIN.R[no];
    *p = temp & (1 << remainder) ? 1 : 0;
    return 0;
}

int hal_gpio_set_output(uint32_t pin, uint32_t data)
{
    if (pin > 36)
        return -2;
    uint32_t no = pin / 32;
    uint32_t remainder = pin % 32;
    if (data)
        gpio_base->GPIO_DOUT.SET[no] = (1 << remainder);
    else
        gpio_base->GPIO_DOUT.CLR[no] = (1 << remainder);
    return 0;
}

int hal_gpio_set_driving_current(uint32_t pin, hal_gpio_driving_current_t driving)
{
    uint32_t *reg = (uint32_t *)0xA20C0000; // config_0.GPIO_DRV.RW[0]   0xA20D0000
    if (pin > 36)
        return -2;
    if (pin > 15)
    {
        if ((pin - 16) < 14)
        {
            pin -= 16;
            reg++; // config_0.GPIO_DRV.RW[1]
        }
        else
        {
            pin -= 30;
            reg += 0x10000; // config_1.GPIO_DRV.RW[0]   0xA20D0000
        }
    }
    *reg &= ~(3 << 2 * pin);
    *reg |= (driving << 2 * pin);
    return 0;
}

int hal_pinmux_set_function(uint32_t gpio_pin, uint8_t function_index)
{

    if ((unsigned int)gpio_pin > 36)
        return -2;
    if (function_index > 8u)
        return -1;

    //TODO
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//  GPT
//      GPT4 is userware, connected to 1Mhz
//      GPT5 is userware, connected to 32K
//////////////////////////////////////////////////////////////////////////////////////
void gpt_open_clock_source(void)
{
    if (REG_32(0xA21D0300) & 0x800000)
        REG_32(0xA21D0320) = 0x800000;
}

void gpt_start_free_run_timer(GPT_REGISTER_T *gpt, uint32_t clock_source, uint32_t divide) // (GPT4, 0, 12) for 1MHz
{
    uint32_t clk;
    gpt = gpt;
    clk = clock_source | divide;
    gpt_open_clock_source();
    gpt->GPT_CLK = clk;
    gpt->GPT_CON_UNION.GPT_CON = 0x301;
}

uint32_t gpt_convert_ms_to_32k_count(uint32_t ms)
{
    return 6 * ms / 100 + 7 * ms / 10 + 32 * ms + 8 * ms / 1000;
}

void gpt_delay_time(GPT_REGISTER_T *gpt, const uint32_t count)
{
    volatile uint32_t begin;
    volatile uint32_t tmp;
    begin = gpt->GPT_COUNT;
    tmp = count + begin + 1;
    if (tmp <= begin)
    {
        while (gpt->GPT_COUNT >= begin)
            ;
        while (gpt->GPT_COUNT < tmp)
            ;
    }
    else
    {
        while (gpt->GPT_COUNT >= begin && gpt->GPT_COUNT < tmp)
            ;
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//  PWM
//      OpenCPU use PWM_1
//////////////////////////////////////////////////////////////////////////////////////
int hal_pwm_set_duty_cycle(PWM_REGISTER_T *pwm, uint32_t duty_cycle)
{
    if (0 == pwm)
        return -1;
    if (duty_cycle > pwm->PWM_COUNT)
        duty_cycle = pwm->PWM_COUNT;
    pwm->PWM_THRESH = duty_cycle;
    return 0;
}

