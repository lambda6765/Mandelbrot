CC = g++
CFLAGS = -O3 -lgd -Wall
OBJS = mandelbrot mandelbrot.png

all: mandelbrot

mandelbrot: mandelbrot.cpp
	$(CC) -o $@ $(CFLAGS) $<

clean:
	@rm -f $(OBJS)
