src = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard lib/**/*.c)
obj = $(src:.c=.o)

LDFLAGS = -Wl,-subsystem,console -lm -lphysfs -mwindows -lmingw32 -lSDL2main -lSDL2
CFLAGS = -Wall -O3 -march=native -mtune=native -s -Iinclude -std=gnu99

ifdef STATIC
LDFLAGS += -LC:/msys64/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -lmingw32 -ldxerr8 -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -mwindows -Wl,--no-undefined -pipe -Wl,--dynamicbase,--high-entropy-va,--nxcompat,--default-image-base-high
CFLAGS += -static-libgcc -static -march=x86-64
else
CFLAGS += -march=native -mtune=native
endif

monroe.exe: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(obj) monroe.exe
