#include <stdint.h>

#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830)
#define GPIOA_MODER (*(volatile uint32_t *)0x40020000)
#define GPIOA_ODR   (*(volatile uint32_t *)0x40020014)

void reset_handler(void)
{
    RCC_AHB1ENR |= (1 << 0);                                    // GPIOAEN
    GPIOA_MODER = (GPIOA_MODER & ~(0x3 << 10)) | (0x1 << 10);   // PA5 output

    while(1)
    {
        GPIOA_ODR ^= (1 << 5);
        for(volatile uint32_t i = 0; i < 2000000; i++);
    }
}

/* stack pointer + reset vector */
__attribute__((section(".vectors")))
void *vectors[] = {
    (void *)0x20018000,
    reset_handler
};