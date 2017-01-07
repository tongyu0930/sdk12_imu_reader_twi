/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 *
 * @defgroup bsp_example_main main.c
 * @{
 * @ingroup bsp_example
 * @brief BSP Example Application main file.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "bsp.h"
#include "nrf_error.h"
#include "app_mpu.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME "APP" //这就是每条信息的前缀 // 这句话必须放在这里。。。。
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


void mpu_setup(void)
{
    ret_code_t ret_code;
    ret_code = mpu_init();
    APP_ERROR_CHECK(ret_code); // Check for errors in return value

    // Setup and configure the MPU with intial values
    mpu_config_t p_mpu_config = MPU_DEFAULT_CONFIG(); // Load default values
    p_mpu_config.smplrt_div = 19;   // Change sampelrate. Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV). 19 gives a sample rate of 50Hz
    p_mpu_config.accel_config.afs_sel = AFS_2G; // Set accelerometer full scale range to 2G
    ret_code = mpu_config(&p_mpu_config); // Configure the MPU with above values
    APP_ERROR_CHECK(ret_code); // Check for errors in return value
}


/**
 * @brief Function for application main entry.
 */
int main(void) // 考虑下要不要用uart例子里的语句来print，是不是用这个log info要耗用更多资源？
{
	uint32_t err_code = NRF_SUCCESS;
	LEDS_CONFIGURE(LEDS_MASK);
    LEDS_OFF(LEDS_MASK);
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL)); //就是这句话把uart config了
    									 //printf(" dahaha"); //这句话在这里无效，为什么？
    char string_on_stack[] =  __TIME__;
    NRF_LOG_INFO("\033[2J\033[;HMPU simple example. Compiled @ %s\r\n", nrf_log_push(string_on_stack));

    mpu_setup();

    accel_values_t acc_values;
    int sample_number = 0;

    while (true)
    {
        NRF_LOG_FLUSH();
        __SEV();
        __WFE(); // wait for event
        __WFE();

        err_code = mpu_read_accel(&acc_values);
        APP_ERROR_CHECK(err_code);
        NRF_LOG_INFO("\033[3;1HSample # %d\r\nX: %06d\r\nY: %06d\r\nZ: %06d", ++sample_number, acc_values.x, acc_values.y, acc_values.z);
        if(acc_values.x == 0){nrf_gpio_pin_toggle(LED_1);}
        nrf_delay_ms(250);
    }
}


/** @} */
