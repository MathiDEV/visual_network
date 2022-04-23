CC = gcc
src = pathfinding.c \
	src/any_utils.c \
	src/my_split.c \
	src/frees.c \
	src/parse/build_four.c \
	src/parse/build_links_with_the_four.c \
	src/parse/parse_utils.c \
	src/parse/read_standard.c \
	src/graph/create.c \
	src/solver/bfs.c \
	src/solver/second_bfs.c \
	src/solver/fct_list.c \
	src/solver/fct_list2.c \
	src/solver/looper.c \
	src/solver/looper2.c \
	src/solver/output.c \
	src/printer/print_moves.c \
	src/printer/multiple_strlen.c \
	src/printer/my_putchar.c \
	src/printer/my_putstr.c \
	src/printer/my_put_nbr.c \
	src/printer/sort.c

NAME = pathfinding
CFLAGS = -Iinclude -g3

OBJ = ${src:.c=.o}
CRIT_FLAGS = --coverage -lcriterion -I include
CRIT_FILES1 = src/*.c
CRIT_TEST1 = tests/*.c
CRIT_FILES_TOTAL = $(CRIT_FILES1)
CRIT_TEST_TOTAL = $(CRIT_TEST1)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	gcc -o ${NAME} ${OBJ}
all : ${NAME}

clean :
	rm -rf ${OBJ}

fclean : clean
	rm -rf ${NAME}

check :
	make -s re

clean_test:
	rm -f *.gcno
	rm -f *.gcda
	rm -f unit_tests

test_crit: clean_test
	$(CC) -o unit_tests $(CRIT_FILES_TOTAL) $(CRIT_TEST_TOTAL) $(CRIT_FLAGS)

tests_run: test_crit
	./unit_tests

re : fclean all

.PHONY: re tests_run test_crit clean_test check fclean clean all
