TARGET = test

all: rm-elf $(TARGET).elf
	flycast $(TARGET).elf
	make clean

linux:
	gcc $(TARGET).c -o $(TARGET) -l SDL -l SDL_image
	./$(TARGET)
	rm $(TARGET)

include $(KOS_BASE)/Makefile.rules

$(TARGET).elf: $(TARGET).o
	kos-cc -o $(TARGET).elf $(TARGET).o -L$(KOS_BASE)/lib -lgcc -lSDL -lSDL_image -lpng -lz -ljpeg -lSDL -lSDL_mixer_126 -loggvorbisplay -ltremor -lm $(KOS_LIBS)

rm-elf:
	-rm -f $(TARGET).elf

clean: rm-elf
	-rm -f $(TARGET).o
