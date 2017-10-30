DB_FLAGS	= -Wall -g -ggdb -O3 -lexif -lglut -fopenmp

LINK_LIBS	=  -lm -fopenmp

CFLAGS		= $(INC_FLAGS) $(DB_FLAGS)
LFLAGS		= $(LINK_FLAGS)

CC		= g++
CP		= cp
RM		= rm
LS		= ls

PROGS1		= g25s6c1a  
OUT1     = g25s6c1a.o  

PROGS2		= g25s6c2a compz 
OUT2     = g25s6c2a.o compz.o

PROGS3		= g25s6c3a compz 
OUT3     = g25s6c3a.o compz.o

PROGS4		= g25s6c3a2 compz 
OUT4     = g25s6c3a2.o compz.o

PROGS5		= g25s6c3b compz 
OUT5     = g25s6c3b.o compz.o

PROGS6		= g25s6c1b compz 
OUT6     = g25s6c1b.o compz.o

all: comp link clean

comp: comp1 comp2 comp3 comp4 comp5 comp6

comp1: 
	for fname in $(PROGS1); do $(CC) $(CFLAGS) -c $$fname.cpp ; done

comp2:
	for fname in $(PROGS2); do $(CC) $(CFLAGS) -c $$fname.cpp ; done
	
comp3:
	for fname in $(PROGS3); do $(CC) $(CFLAGS) -c $$fname.cpp ; done
	
comp4:
	for fname in $(PROGS4); do $(CC) $(CFLAGS) -c $$fname.cpp ; done

comp5:
	for fname in $(PROGS5); do $(CC) $(CFLAGS) -c $$fname.cpp ; done
	
comp6:
	for fname in $(PROGS6); do $(CC) $(CFLAGS) -c $$fname.cpp ; done
	
link: link1 link2 link3 link4 link5 link6

link1: 
	$(CC) $(OUT1) $(LFLAGS) $(LINK_LIBS)  -o p1a

link2: 
	$(CC) $(OUT2) $(LFLAGS) $(LINK_LIBS)  -o p2a
	
link3: 
	$(CC) $(OUT3) $(LFLAGS) $(LINK_LIBS)  -o p3a	

link4: 
	$(CC) $(OUT4) $(LFLAGS) $(LINK_LIBS)  -o p3a2	

link5: 
	$(CC) $(OUT5) $(LFLAGS) $(LINK_LIBS)  -o p3b	
	
link6: 
	$(CC) $(OUT6) $(LFLAGS) $(LINK_LIBS)  -o p1b

clean:
	$(RM) -f *~ *.o $(PROGS1)
	$(RM) -f *~ *.o $(PROGS2)
	$(RM) -f *~ *.o $(PROGS3)
	$(RM) -f *~ *.o $(PROGS4)
	$(RM) -f *~ *.o $(PROGS5)
	$(RM) -f *~ *.o $(PROGS6)
	
