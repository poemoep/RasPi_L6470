CC            = gcc
CFLAGS        = -O4 -Wall -I/usr/local/include 
LDFLAGS       = -L/usr/local/lib
LIBS          = -lwiringPi -lm
MAINOBJS      = L6470.o main.o
GENOBJS       = L6470.o generator.o
USERH	      = L6470_user.h
USERHEADER    = user
GENPROGRAM    = gen
PROGRAM       = test

all:            $(PROGRAM) $(GENPROGRAM)

$(PROGRAM):     $(MAINOBJS)
	$(CC) $(MAINOBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

$(GENPROGRAM):  $(GENOBJS)
	$(CC) $(GENOBJS) $(LDFLAGS) $(LIBS) -o $(GENPROGRAM)

$(USERHEADER):  $(GENPROGRAM)
	./$(GENPROGRAM) > temp.h
	echo "#if 0" >> temp.h
	cat $(USERH) >> temp.h
	echo "#endif" >> temp.h
	rm $(USERH)
	mv temp.h $(USERH)

clean:;         rm -f *.o *~ $(PROGRAM) $(GENPROGRAM)
