PROJECT = mergetars
HEADERS = $(PROJECT).h
OBJ = mergetars.o make_dirs.o globals.o merge_check.o make_merged_tar.o

C99 = cc -std=c99
CFLAGS = -Wall -pedantic -Werror

$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm

%.o : %.c $(HEADERS)
	$(C99) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)
