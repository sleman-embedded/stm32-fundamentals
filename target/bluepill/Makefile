blink.elf: main.c linker.ld
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -nostdlib -T linker.ld main.c -o blink.elf

flash: blink.elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program blink.elf verify reset exit"

flash-jlink: blink.elf
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f1x.cfg -c "program blink.elf verify reset exit"

clean:
	rm -f blink.elf