SRCS = shell.c makedir.c grepp.c mv.c cd.c cp.c remove.c cat.c call.c
TARG = shell
CC = gcc
OPTS = -Wall -O
LIBS = -lm -lreadline

OBJS = $(SRCS:.c=.o)
all: $(TARG)
$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARG)