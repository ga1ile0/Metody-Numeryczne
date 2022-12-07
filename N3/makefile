DIR = $(notdir $(CURDIR))
CO = gcc
LD = $(CO)
CFLAGS = -Wall -std=c99 -pedantic -O
LFLAGS = $(CFLAGS)

NAME1 = N1
NAME2 = N2
NAME3 = N3
NAME4 = N4

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run1 run2 run3 run4
run1: $(EXEC1)
	./$(EXEC1) 
run2: $(EXEC2) 
	./$(EXEC2) 
run3: $(EXEC3) 
	./$(EXEC3) 
run4: $(EXEC4)
	./$(EXEC4)

.PHONY: clean tar
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))
