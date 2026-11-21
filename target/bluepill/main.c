#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004)
#define GPIOC_ODR   (*(volatile uint32_t *)0x4001100C)

void reset_handler(void)
{
    RCC_APB2ENR |= (1 << 4);                                /* IOPCEN */
    GPIOC_CRH = (GPIOC_CRH & ~(0xF << 20)) | (0x2 << 20);   /* PC13 output 2MHz push-pull */

    while(1)
    {
        GPIOC_ODR ^= (1 << 13);
        for (volatile uint32_t i = 0; i < 1000000; i++);
    }
}

/* stack pointer + reset vector */
__attribute__((section(".vectors")))
void *vectors[] = {
    (void *)0x20005000,
    reset_handler
};