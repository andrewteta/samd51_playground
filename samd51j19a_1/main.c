#include <atmel_start.h>

#define LED GPIO(GPIO_PORTA, 23)

static inline void set_all_gpio_low(void)
{
	gpio_set_port_direction(GPIO_PORTA, 0xffffffff, GPIO_DIRECTION_OUT);
	gpio_set_port_level(GPIO_PORTA, 0xffffffff, 0);
	gpio_set_port_direction(GPIO_PORTB, 0xffffffff, GPIO_DIRECTION_OUT);
	gpio_set_port_level(GPIO_PORTB, 0xffffffff, 0);
	gpio_set_port_direction(GPIO_PORTC, 0xffffffff, GPIO_DIRECTION_OUT);
	gpio_set_port_level(GPIO_PORTC, 0xffffffff, 0);
	gpio_set_port_direction(GPIO_PORTD, 0xffffffff, GPIO_DIRECTION_OUT);
	gpio_set_port_level(GPIO_PORTD, 0xffffffff, 0);
	gpio_set_port_direction(GPIO_PORTE, 0xffffffff, GPIO_DIRECTION_OUT);
	gpio_set_port_level(GPIO_PORTE, 0xffffffff, 0);
}

static void LED_Timer_cb(const struct timer_task *const timer_task)
{
	gpio_toggle_pin_level(LED);
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	set_all_gpio_low();

	gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);

	static struct timer_task LED_Timer_task0;
	LED_Timer_task0.interval = 1;
	LED_Timer_task0.cb       = LED_Timer_cb;
	LED_Timer_task0.mode     = TIMER_TASK_REPEAT;

	// timer_set_clock_cycles_per_tick(&TIMER_0, 1);
	timer_add_task(&TIMER_0, &LED_Timer_task0);
	timer_start(&TIMER_0);

	/* Replace with your application code */
	while (1) {
	}
}
