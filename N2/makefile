DIR = $(notdir $(CURDIR))
CXXFLAGS = -Wall -Wextra
LDFLAGS = -Wall -Wextra
LDLIBS = -lm

NAME1 = N1
NAME2 = N2

.PHONY: clean all
all: N1.x N2.x N3.x N4.x

N1.x: N1.o
N1.o: N1.cpp

N2.x: N2.o
N2.o: N2.cpp

N3.x: N3.o
N3.o: N3.cpp

N4.x: N4.o
N4.o: N4.cpp

%.x: %.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run1: N1.x
	./N1.x

run2: N2.x
	./N2.x

run3: N3.x
	./N3.x

run4: N4.x
	./N4.x

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )