CC = g++
CFLAGS = -g -O3 -Wfatal-errors -Wno-deprecated -D__USE_MINGW_ANSI_STDIO
INCLUDEDIRS = -I./SOCO_SI -I./fastFractal-CEC2008
OBJS = main.o lshade.o search_algorithm.o 
F7OBJS = RanQD1.o  RanTable.o  FastFractal.o  DoubleDip.o  FractalFunction1D.o UnitFunction1D.o
FUNCTOBJS = funsoft.o

lshade.exe : $(OBJS)  $(FUNCTOBJS) $(F7OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FUNCTOBJS) $(F7OBJS) -o lshade.exe

$(OBJS) : main.cc lshade.cc search_algorithm.cc
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c main.cc lshade.cc search_algorithm.cc
	
$(FUNCTOBJS) : SOCO_SI/funsoft.cpp
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c SOCO_SI/funsoft.cpp
  
$(F7OBJS) : ./fastFractal-CEC2008/RanQD1.cpp  ./fastFractal-CEC2008/RanTable.cpp  ./fastFractal-CEC2008/FastFractal.cpp  ./fastFractal-CEC2008/DoubleDip.cpp  ./fastFractal-CEC2008/FractalFunction1D.cpp ./fastFractal-CEC2008/UnitFunction1D.cpp
  $(CC) $(CFLAGS) $(INCLUDEDIRS) -c ./fastFractal-CEC2008/RanQD1.cpp  ./fastFractal-CEC2008/RanTable.cpp  ./fastFractal-CEC2008/FastFractal.cpp  ./fastFractal-CEC2008/DoubleDip.cpp  ./fastFractal-CEC2008/FractalFunction1D.cpp ./fastFractal-CEC2008/UnitFunction1D.cpp

	
.PHONY: clean

clean:
	rm -rf *.o