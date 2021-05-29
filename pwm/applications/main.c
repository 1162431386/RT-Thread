#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

/* ʹ��PWM�豸 */
struct rt_device_pwm  *pwm_device = RT_NULL; //���� pwm �豸ָ��
/***** ������ ��ض������� ********/
//void MX_TIM3_Init(void);
#define BEEP_PWM_DEVICE  "pwm5"  //��ʱ��5
#define BEEP_PWM_CH      1       //ͨ��1
/***************************************************************/
/* defined the LED0 pin: PB1 */

#define PULSE_ENCODER_DEV_NAME    "pulse3"    /* ������������� */

static int pulse_encoder_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_device_t pulse_encoder_dev = RT_NULL;   /* ����������豸��� */

    rt_int32_t count;

    /* ��������������豸 */
    pulse_encoder_dev = rt_device_find(PULSE_ENCODER_DEV_NAME);
    if (pulse_encoder_dev == RT_NULL)
    {
        rt_kprintf("pulse encoder sample run failed! can't find %s device!\n", PULSE_ENCODER_DEV_NAME);
        return RT_ERROR;
    }

    /* ��ֻ����ʽ���豸 */
    ret = rt_device_open(pulse_encoder_dev, RT_DEVICE_OFLAG_RDONLY);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", PULSE_ENCODER_DEV_NAME);
        return ret;
    }else
        {
                rt_kprintf("open %s device success!\n", PULSE_ENCODER_DEV_NAME);
        }

   for(rt_uint32_t i = 0; i <= 10; i++)
    {
        rt_thread_mdelay(500);
        /* ��ȡ�������������ֵ */
        rt_device_read(pulse_encoder_dev, 0, &count, 1);
        /* ����������������ֵ */
        rt_device_control(pulse_encoder_dev, PULSE_ENCODER_CMD_CLEAR_COUNT, RT_NULL);
        rt_kprintf("get count %d\n",count);
    }

    rt_device_close(pulse_encoder_dev);
    return ret;
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(pulse_encoder_sample, pulse encoder sample);


#if 1
int main(void)
{


    int count = 1;

    /* ����PWM�豸 */
    pwm_device = (struct rt_device_pwm *)rt_device_find(BEEP_PWM_DEVICE);
    if (pwm_device == RT_NULL)
    {
        rt_kprintf("pwm device %s not found!\n", BEEP_PWM_DEVICE);
        return -RT_ERROR;
    }
    rt_pwm_set(pwm_device, BEEP_PWM_CH, 500000, 250000);   //channel,period,pulse
    rt_pwm_enable(pwm_device, BEEP_PWM_CH);                 //ʹ�ܷ�������Ӧ�� PWM ͨ��

    while (count++)
    {
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}

#endif

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


