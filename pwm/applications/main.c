#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

/* ʹ��PWM�豸 */
struct rt_device_pwm  *pwm_device = RT_NULL; //���� pwm �豸ָ��
/***** ������ ��ض������� ********/
//void MX_TIM3_Init(void);
#define BEEP_PWM_DEVICE  "pwm5"  //��ʱ��5
#define BEEP_PWM_CH      1       //ͨ��1
int main(void)
{


    int count = 1;
#if 0
    /* ����PWM�豸 */
    pwm_device = (struct rt_device_pwm *)rt_device_find(BEEP_PWM_DEVICE);
    if (pwm_device == RT_NULL)
    {
        rt_kprintf("pwm device %s not found!\n", BEEP_PWM_DEVICE);
        return -RT_ERROR;
    }
    rt_pwm_set(pwm_device, BEEP_PWM_CH, 1000000000, 500000000);   //channel,period,pulse
    rt_pwm_enable(pwm_device, BEEP_PWM_CH);                 //ʹ�ܷ�������Ӧ�� PWM ͨ��
#endif
    while (count++)
    {
//        LOG_D("Hello RT-Thread!");
        rt_thread_mdelay(10);
    }

    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


