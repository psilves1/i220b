PROJECT = key-value

CFLAGS = -g -Wall -std=c11
LDFLAGS = -lm
SRC_FILES=	main.c\
		main.o\
		Makefile\
		key-value.o\
		key-value.h\
		key-value.c\
		process-file.o\
		process-file.h\
		process-file.c\
		README

$(PROJECT):	key-value.o main.o process-file.o
		$(CC) key-value.o main.o process-file.o $(LDFLAGS)  -o $@


dist:			$(PROJECT).tar.gz

$(PROJECT).tar.gz:	$(SRC_FILES)
			tar -cf $(PROJECT).tar $(SRC_FILES)
			gzip -f $(PROJECT).tar

depend:
		$(CC) -MM $(CPPFLAGS) *.c

clean:
		rm -f *.o $(PROJECT) $(PROJECT).tar.gz

main.o: main.c process-file.h
key-value.o: key-value.c key-value.h
process-file.o: process-file.c process-file.h key-value.h
#automatically generated dependencies produced by make depend 
