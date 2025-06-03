#include <stdint.h>

#define PERIPH_BASE 0x40000000UL

#define RCC_BASE_OFFSET 0x21000UL // For clock gating
#define RCC_AHBENR_OFFSET 0x14UL // RCC AHB Enable Register Offset. GPIOAEN bit 17
#define GPIOAEN (1U << 17)

#define GPIOA_OFFSET 0x8000000UL
#define GPIOA_MODER_OFFSET 0x00UL //MODER5 General Purpose Output = 0b01

#define GPIOA_ODR_OFFSET 0x14UL
#define PIN3 (1U << 3)
#define PIN4 (1U << 4)

#define GPIOA_AHBENR 	(*(volatile uint32_t*)(PERIPH_BASE + RCC_BASE_OFFSET + RCC_AHBENR_OFFSET))
#define GPIOA_MODER 	(*(volatile uint32_t*)(PERIPH_BASE + GPIOA_OFFSET + GPIOA_MODER_OFFSET))
#define GPIOA_ODR 		(*(volatile uint32_t*)(PERIPH_BASE + GPIOA_OFFSET + GPIOA_ODR_OFFSET))

int main(void)
{
	// Enable GPIOA Clock
	GPIOA_AHBENR |= GPIOAEN;

	// Set Pin 3 as General Purpose Output
	GPIOA_MODER &= ~(1U << 7);
	GPIOA_MODER |= (1U << 6);

	// Set Pin 4 as General Purpose Output
	GPIOA_MODER &= ~(1U << 9);
	GPIOA_MODER |= (1U << 8);

	while(1)
	{
		GPIOA_ODR &= ~PIN4;
		GPIOA_ODR |= PIN3;
	}
}
