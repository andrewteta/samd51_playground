#include <atmel_start.h>

#define LED GPIO(GPIO_PORTA, 23)

static void LED_Timer_cb(const struct timer_task *const timer_task)
{
	gpio_toggle_pin_level(LED);
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	gpio_set_port_direction(GPIO_PORTA, 0xffffffff, GPIO_DIRECTION_OUT);
	gpio_set_port_level(GPIO_PORTA, 0xffffffff, 0);

	gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);
	// gpio_set_pin_pull_mode(LED, GPIO_PULL_OFF);

	// i2c_m_sync_enable(&I2C_0);

	// usart_sync_enable(&USART_1);
	static struct timer_task LED_Timer;
	LED_Timer.interval = 5;
	LED_Timer.cb       = LED_Timer_cb;
	LED_Timer.mode     = TIMER_TASK_REPEAT;

	timer_set_clock_cycles_per_tick(&TIMER_0, 1);
	timer_add_task(&TIMER_0, &LED_Timer);
	timer_start(&TIMER_0);

	/* Replace with your application code */
	while (1) {
	}
}
