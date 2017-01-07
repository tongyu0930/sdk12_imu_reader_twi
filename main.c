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

//#define APP_TIMER_PRESCALER      0                           /**< Value of the RTC1 PRESCALER register. */
//#define APP_TIMER_OP_QUEUE_SIZE  2                           /**< Size of timer operation queues. */

//#define BUTTON_PREV_ID           0                           /**< Button used to switch the state. */
//#define BUTTON_NEXT_ID           1                           /**< Button used to switch the state. */

//static bsp_indication_t actual_state =  BSP_INDICATE_FIRST;         /**< Currently indicated state. */

//static const char * indications_list[] = BSP_INDICATIONS_LIST;

/**@brief Function for handling bsp events.

void bsp_evt_handler(bsp_event_t evt)
{
    uint32_t err_code;

    char string_on_stack[] = "stack";

    switch (evt)
    {
        case BSP_EVENT_KEY_0: //就是button0
            if (actual_state != BSP_INDICATE_FIRST)
                actual_state--;
            else
                actual_state = BSP_INDICATE_LAST;
            break;

        case BSP_EVENT_KEY_1:

            if (actual_state != BSP_INDICATE_LAST)
                actual_state++;
            else
                actual_state = BSP_INDICATE_FIRST;
            break;

        default:
            return; // no implementation needed
    }
    err_code = bsp_indication_set(actual_state); //这个是根据actual_state来选择LED闪烁模式
    NRF_LOG_INFO("%s\r\n", (uint32_t)indications_list[actual_state]);
    //actual_state就是indications_list这个数组的index。因为这个function他没有return err_code，所以不能像上面那句话那样检查error。
    APP_ERROR_CHECK(err_code);

    NRF_LOG_INFO("%s",nrf_log_push(string_on_stack));
    //nrf_log_push() copies the string into the logger buffer and returns address from the logger buffer

} */


/**@brief Function for initializing low frequency clock.

void clock_initialization()            // 这里看不懂啊
{
    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;

    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0)
    {
        // Do nothing.
    }
} */


/**@brief Function for initializing bsp module.

void bsp_configuration()
{
    uint32_t err_code;

    err_code = bsp_init(BSP_INIT_LED | BSP_INIT_BUTTONS,
                        APP_TIMER_TICKS(100, APP_TIMER_PRESCALER),
                        bsp_evt_handler);
    APP_ERROR_CHECK(err_code);
}
 */

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    //clock_initialization();
    //APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, NULL);
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL)); //就是这句话把uart config了

    NRF_LOG_INFO("BSP example started.\r\n");
    //bsp_configuration();

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
