IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

SDIR=src
ODIR=obj
LDIR=lib

#Libs are included without the lib prefix because -l does that for you
LIBS=-lm

#H files go here
_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#Target object files go here (There basically the c files)
_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#The end program results name
main : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

