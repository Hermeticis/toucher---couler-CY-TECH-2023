CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -fsanitize=address

SRC = main.c matrix.c common.c jeu.c boat.c

OBJ = $(SRC:.c=.o)

EXEC = mon_programme

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
