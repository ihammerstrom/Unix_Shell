CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -Wall -g
OBJECTS = tokenizer.o pwd.o cd.o ShellMain.o
OBJECTSsh = showenv.o tokenizer.o
OBJECTSfr = regexp.o fref.o tokenizer.o

EXES = ShellMain


ShellMain:	$(OBJECTS) ShellMain.h showenv fref
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS)

%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

showenv:	$(OBJECTSsh)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTSsh)

fref:	$(OBJECTSfr)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTSfr)

clean:
	rm -f *.o $(EXES)

