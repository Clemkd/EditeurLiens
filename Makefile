CC=gcc
CFLAGS=-Wall -Werror -g -c
OBJ= $(SRC:.c=.o)

all: test_API_read test_API_write test_affichage_sections

test_affichage_sections: test_affichage_sections.o affichage_sections.o API.o
	$(CC) -g -o $@ $^ -lm

test_API_read: test_API_read.o API.o
	$(CC) -g -o $@ $^ -lm
	
test_API_write: test_API_write.o API.o
	$(CC) -g -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) $<

clean   :
	rm -f $(OBJ) ./*~
	rm -f *.o *.*~

affichage_sections.o: affichage_sections.h API.h
API.o: API.h
