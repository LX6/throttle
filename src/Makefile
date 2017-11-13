CC      = g++
CFLAGS  = -I/home/lacho/
LDFLAGS = -lcurses -ldb

all: time clean

time: vdata.o time.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: vdata.c vdata.h time.cpp time.h 
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm time

