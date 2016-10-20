CC = g++
LD = g++
CFLAGS = `sdl-config --cflags`
LDFLAGS = `sdl-config --libs` -lSDL_image -lpng
RM   = /bin/rm -f

.PHONY: clean
all: savesurf savescreen saveglscreen
savesurf: savesurf.o pngfuncs.o
	$(LD) $(LDFLAGS) -s -o savesurf savesurf.o pngfuncs.o
savescreen: savescreen.o pngfuncs.o
	$(LD) $(LDFLAGS) -s -o savescreen savescreen.o pngfuncs.o
saveglscreen: saveglscreen.o pngfuncs.o
	$(LD) $(LDFLAGS) -lGL -s -o saveglscreen saveglscreen.o pngfuncs.o
savesurf.o: savesurf.c
	$(CC) $(CFLAGS) -c savesurf.c
savescreen.o: savescreen.c
	$(CC) $(CFLAGS) -c savescreen.c
saveglscreen.o: saveglscreen.c
	$(CC) $(CFLAGS) -c saveglscreen.c
pngfuncs.o: pngfuncs.c
	$(CC) $(CFLAGS) -c pngfuncs.c
clean:
	$(RM) *~ pngfuncs.o savesurf.o savesurf savescreen.o savescreen saveglscreen.o saveglscreen
