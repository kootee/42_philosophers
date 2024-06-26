NAME := philo
CC := gcc
BUILD_DIR := build
BIN_DIR := bin
CFLAGS ?= -Wextra -Wall -Werror -Wunreachable-code -Ofast -pthread -g
DEBUG_FLAGS ?= -fsanitize=thread
debug ?= 0

HEADERS	= -I ./include

SRCS	= 	main.c \
			error_handling.c \
			philo_init.c \
			philo_routines.c \
			philo_utils.c 

OBJS	= ${SRCS:.c=.o}

ifeq (${debug}, 1)
	CFLAGS := ${CFLAGS} ${DEBUG_FLAGS}
else
	CFLAGS := ${CFLAGS}
endif

all: ${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -o $@ -c $< ${HEADERS}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${HEADERS} -o ${NAME}

clean:
	@rm -rf ${OBJS}
	@echo "cleaning"

fclean: clean
	@rm -rf ${NAME}
	@echo "fcleaning"

re: clean all

.PHONY: all, clean, fclean, re