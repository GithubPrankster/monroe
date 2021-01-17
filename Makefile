src = $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard lib/**/*.c)
obj = $(src:.c=.o)

CFLAGS = -Wall -O3 -march=native -mtune=native -s -Iinclude -std=gnu99
LDFLAGS = -Wl,-subsystem,console -lm -lphysfs -mwindows -lmingw32 -lopengl32 -lSDL2main -lSDL2

monroe.exe: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(obj) monroe.exe
