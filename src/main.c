#include <stdint.h>

#define PERIPH_BASE 0x40000000UL

#define RCC_BASE_OFFSET 0x21000UL // For clock gating
#define RCC_AHBENR_OFFSET 0x14UL // RCC AHB Enable Register Offset. GPIOAEN bit 17
#define GPIOAEN (1U << 17)

#define GPIOA_OFFSET 0x8000000UL
#define GPIOA_MODER_OFFSET 0x00UL //MODER5 General Purpose Output = 0b01. Input = 0b00.

#define GPIOA_ODR_OFFSET 0x14UL
#define GPIOA_IDR_OFFSET 0x10UL

#define PIN3 (1U << 3)
#define PIN4 (1U << 4)
#define PIN6 (1U << 6)
#define PIN7 (1U << 7)

#define GPIOA_AHBENR 	(*(volatile uint32_t*)(PERIPH_BASE + RCC_BASE_OFFSET + RCC_AHBENR_OFFSET))
#define GPIOA_MODER 	(*(volatile uint32_t*)(PERIPH_BASE + GPIOA_OFFSET + GPIOA_MODER_OFFSET))
#define GPIOA_ODR 		(*(volatile uint32_t*)(PERIPH_BASE + GPIOA_OFFSET + GPIOA_ODR_OFFSET))
#define GPIOA_IDR 		(*(volatile uint32_t*)(PERIPH_BASE + GPIOA_OFFSET + GPIOA_IDR_OFFSET))

int main(void)
{
	// Enable GPIOA Clock
	GPIOA_AHBENR |= GPIOAEN;

	// Set Pin 3 (SW1) as General Purpose Output
	GPIOA_MODER &= ~(1U << 7);
	GPIOA_MODER |= (1U << 6);

	// Set Pin 4 (SW2) as General Purpose Output
	GPIOA_MODER &= ~(1U << 9);
	GPIOA_MODER |= (1U << 8);

	// Set Pin 6 (SW_UP) as Input
	GPIOA_MODER &= ~(1U << 12);
	GPIOA_MODER &= ~(1U << 13);

	// Set Pin 7 (SW_DWN) as Input
	GPIOA_MODER &= ~(1U << 14);
	GPIOA_MODER &= ~(1U << 15);

	while(1)
	{
		if(!(GPIOA_IDR & (PIN6)))
		{
			GPIOA_ODR &= ~PIN4;
			GPIOA_ODR |= PIN3;
		}
		else if(!(GPIOA_IDR & (PIN7)))
		{
			GPIOA_ODR &= ~PIN3;
			GPIOA_ODR |= PIN4;
		}
		else
		{
			GPIOA_ODR &= ~PIN3;
			GPIOA_ODR &= ~PIN4;
		}
	}
}
