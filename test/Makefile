CC=gcc
CFLAGS=-g -Wall -Werror -Wextra
NAME=testing

$(NAME): test_list.o
	$(CC) $(CFLAGS) -llist -o testing test_list.o

test_list.o: test_list.c 
	$(CC) -c $(CFLAGS) test_list.c

.PHONY: clean fclean

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
