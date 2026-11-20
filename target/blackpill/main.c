#include <stdint.h>

#define RCC_AHB1ENR (*(volatile uint32_t *)0x40023830)
#define GPIOC_MODER (*(volatile uint32_t *)0x40020800)
#define GPIOC_ODR   (*(volatile uint32_t *)0x40020814)

void reset_handler(void)
{
    RCC_AHB1ENR |= (1 << 2);                                    // GPIOCEN
    GPIOC_MODER = (GPIOC_MODER & ~(0x3 << 26)) | (0x1 << 26);   // PC13 output

    while(1)
    {
        GPIOC_ODR ^= (1 << 13);
        for(volatile uint32_t i = 0; i < 200000; i++);
    }
}

/* stack pointer + reset vector */
__attribute__((section(".vectors")))
void *vectors[] = {
    (void *)0x20020000,
    reset_handler
};