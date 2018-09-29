CC = gcc -fPIC 
LDFLAGS = -lm

# set DEBUG options
ifdef DEBUG
CFLAGS = -Wall -Wextra -ggdb -pg -DDEBUG
else
CFLAGS = -Wall -O2
endif

#name all the object files
OBJS = main.c variables.c hash_table.c command_parser.c read.c additional_functions.c builtin_commands.c excute_command.c file_writer.c file_reader.c batch_runner.c

all : shell

shell : $(OBJS)
	$(CC) $(LDFLAGS) -o main $^

debug :
	make all DEBUG=1

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^

doxy :
	doxygen Doxyfile

clean :
	rm -rf $(OBJS) main
