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
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_error.h"

#define NRF_LOG_MODULE_NAME "APP" //这就是每条信息的前缀 // 这句话必须放在这里。。。。
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


/**
 * @brief Function for application main entry.
 */
int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL)); //就是这句话把uart config了
    NRF_LOG_INFO("BSP example started.\r\n"); // 考虑下要不要用uart例子里的语句来print，是不是用这个log info要耗用更多资源？
    //printf(" dahaha"); //这句话无效，为什么？

    while (true)
    {
        NRF_LOG_FLUSH();
        __SEV();
        __WFE(); // wait for event
        __WFE();
        // no implementation needed
    }
}


/** @} */
