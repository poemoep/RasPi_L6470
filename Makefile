CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include 
LDFLAGS       = -L/usr/local/lib
LIBS          = -lwiringPi -lm
MAINOBJS      = L6470.o main.o
GENOBJS       = L6470.o generator.o
GENPROGRAM    = gen
PROGRAM       = test

all:            $(PROGRAM) $(GENPROGRAM)

$(PROGRAM):     $(MAINOBJS)
	$(CC) $(MAINOBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

$(GENPROGRAM):  $(GENOBJS)
	$(CC) $(GENOBJS) $(LDFLAGS) $(LIBS) -o $(GENPROGRAM)


clean:;         rm -f *.o *~ $(PROGRAM) $(GENPROGRAM)
