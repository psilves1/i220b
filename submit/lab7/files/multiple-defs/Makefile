CFLAGS = -g -Wall -std=c11

multiple-defs: 	main.o f.o
		$(CC) main.o f.o $(LDFLAGS) -o $@

.PHONY:		clean
clean:
		rm -f *.o multiple-defs

main.o: main.c f.h
f.o: f.c f.h
