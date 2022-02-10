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

// static void LED_Timer_cb(const struct timer_task *const timer_task)
// {
// 	// gpio_toggle_pin_level(LED);
// 	PORT->Group[GPIO_PORTA].OUTTGL.reg = (1 << 23);
// }

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	set_all_gpio_low();

	// gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);

	// static struct timer_task LED_Timer_task0;
	// LED_Timer_task0.interval = 1;
	// LED_Timer_task0.cb       = LED_Timer_cb;
	// LED_Timer_task0.mode     = TIMER_TASK_REPEAT;

	// // timer_set_clock_cycles_per_tick(&TIMER_0, 1);
	// timer_add_task(&TIMER_0, &LED_Timer_task0);
	// _timer_set_period(&TIMER_0.device, 100);
	// timer_start(&TIMER_0);

	
	pwm_set_parameters(&PWM_0, 7, 3.5);
	pwm_enable(&PWM_0);
	gpio_set_pin_function(GPIO(GPIO_PORTA, 4), GPIO_PIN_FUNCTION_E); // for TC

	// configure tcc1 fror multiple compare output
	hri_mclk_set_APBBMASK_TCC1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TCC1_GCLK_ID, GCLK_PCHCTRL_GEN_GCLK0_Val | (1 << GCLK_PCHCTRL_CHEN_Pos));
	gpio_set_pin_function(GPIO(GPIO_PORTB, 8), GPIO_PIN_FUNCTION_G); // set PORT IO for TCC alternate function
	TCC1->CTRLA.reg &= ~(TCC_CTRLA_ENABLE);
	TCC1->CTRLA.reg |= (TCC_CTRLA_SWRST); // put TCC in SW reset
	TCC1->CTRLA.reg |= TCC_CTRLA_PRESCALER_DIV1;
	TCC1->CTRLA.reg |= TCC_CTRLA_PRESCSYNC_PRESC;
	TCC1->WAVE.reg |= TCC_WAVE_WAVEGEN_NPWM | TCC_WAVE_POL0;
	TCC1->PER.reg = 1024;
	TCC1->CC[4].reg = 24;

	TCC1->CTRLA.reg |= TCC_CTRLA_ENABLE;
	TCC1->CTRLBSET.reg |= TCC_CTRLBSET_CMD_RETRIGGER;
	TCC1->EVCTRL.reg |= TCC_EVCTRL_EVACT0_START;

	/* Replace with your application code */
	while (1) {
		gpio_toggle_pin_level(GPIO(GPIO_PORTA, 9));
		delay_ms(500);
	}
}
