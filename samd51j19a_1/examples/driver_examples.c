/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
}

/**
 * Example of using DAC_0 to generate waveform.
 */
void DAC_0_example(void)
{
	uint16_t i = 0;

	dac_sync_enable_channel(&DAC_0, 0);

	for (;;) {
		dac_sync_write(&DAC_0, 0, &i, 1);
		i = (i + 1) % 1024;
	}
}

/* CRC Data in flash */
COMPILER_ALIGNED(4)
static const uint32_t crc_datas[] = {0x00000000,
                                     0x11111111,
                                     0x22222222,
                                     0x33333333,
                                     0x44444444,
                                     0x55555555,
                                     0x66666666,
                                     0x77777777,
                                     0x88888888,
                                     0x99999999};

/**
 * Example of using CRC_0 to Calculate CRC32 for a buffer.
 */
void CRC_0_example(void)
{
	/* The initial value used for the CRC32 calculation usually be 0xFFFFFFFF,
	 * but can be, for example, the result of a previous CRC32 calculation if
	 * generating a common CRC32 of separate memory blocks.
	 */
	uint32_t crc = 0xFFFFFFFF;
	uint32_t crc2;
	uint32_t ind;

	crc_sync_enable(&CRC_0);
	crc_sync_crc32(&CRC_0, (uint32_t *)crc_datas, 10, &crc);

	/* The read value must be complemented to match standard CRC32
	 * implementations or kept non-inverted if used as starting point for
	 * subsequent CRC32 calculations.
	 */
	crc ^= 0xFFFFFFFF;

	/* Calculate the same data with subsequent CRC32 calculations, the result
	 * should be same as previous way.
	 */
	crc2 = 0xFFFFFFFF;
	for (ind = 0; ind < 10; ind++) {
		crc_sync_crc32(&CRC_0, (uint32_t *)&crc_datas[ind], 1, &crc2);
	}
	crc2 ^= 0xFFFFFFFF;

	/* The calculate result should be same. */
	while (crc != crc2)
		;
}

/**
 * Example of using QUAD_SPI_0 to get N25Q256A status value,
 * and check bit 0 which indicate embedded operation is busy or not.
 */
void QUAD_SPI_0_example(void)
{
	uint8_t              status = 0xFF;
	struct _qspi_command cmd    = {
        .inst_frame.bits.inst_en  = 1,
        .inst_frame.bits.data_en  = 1,
        .inst_frame.bits.tfr_type = QSPI_READ_ACCESS,
        .instruction              = 0x05,
        .buf_len                  = 1,
        .rx_buf                   = &status,
    };

	qspi_sync_enable(&QUAD_SPI_0);
	while (status & (1 << 0)) {
		qspi_sync_serial_run_command(&QUAD_SPI_0, &cmd);
	}
	qspi_sync_deinit(&QUAD_SPI_0);
}

/**
 * Example of using SPI_0 to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_0[12] = "Hello World!";

void SPI_0_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);

	spi_m_sync_enable(&SPI_0);
	io_write(io, example_SPI_0, 12);
}

void I2C_0_example(void)
{
	struct io_descriptor *I2C_0_io;

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x12, I2C_M_SEVEN);
	io_write(I2C_0_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using USART_1 to write "Hello World" using the IO abstraction.
 */
void USART_1_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_1, &io);
	usart_sync_enable(&USART_1);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

void delay_example(void)
{
	delay_ms(5000);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_set_parameters(&PWM_0, 10000, 5000);
	pwm_enable(&PWM_0);
}

static struct timer_task TIMER_1_task1, TIMER_1_task2;

/**
 * Example of using TIMER_1.
 */
static void TIMER_1_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_1_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_1_example(void)
{
	TIMER_1_task1.interval = 100;
	TIMER_1_task1.cb       = TIMER_1_task1_cb;
	TIMER_1_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_1_task2.interval = 200;
	TIMER_1_task2.cb       = TIMER_1_task2_cb;
	TIMER_1_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_1, &TIMER_1_task1);
	timer_add_task(&TIMER_1, &TIMER_1_task2);
	timer_start(&TIMER_1);
}

/**
 * Example of using TIMER_0.
 */
struct timer_task TIMER_0_task1, TIMER_0_task2;

static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}

/**
 * Example of using RAND_0 to generate waveform.
 */
void RAND_0_example(void)
{
	uint32_t random_n[4];
	rand_sync_enable(&RAND_0);
	random_n[0] = rand_sync_read32(&RAND_0);
	random_n[1] = rand_sync_read32(&RAND_0);
	rand_sync_read_buf32(&RAND_0, &random_n[2], 2);
	if (random_n[0] == random_n[1]) {
		/* halt */
		while (1)
			;
	}
	if (random_n[2] == random_n[3]) {
		/* halt */
		while (1)
			;
	}
}
