CC=gcc
INCDIRS=-I.
OPT=-O0
CFLAGS=-Wall -Wextra -g $(INCDIRS) $(OPT)

CFILES=TP2main.c ListeChainee.c
OBJECTS=TP2main.o ListeChainee.o

BINARY= tp2

.PHONY: run
run: $(BINARY)
    ./$(BINARY) txt_Test.txt

all: $(BINARY)

$(BINARY): $(OBJECTS)
		$(CC) -o $@ $^

# expression reguliere '%', si on veut construire quoique ce soit .o, ça doit dépendre de qlqchose.c
%.o:%.c
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
		rm -rf $(BINARY) $(OBJECTS)


# projet : TP2main.o ListeChainee.o
# 	gcc TP2main.o ListeChainee.o -o projet

# TP2main.o : TP2main.c ListeChainee.h
# 	gcc -c main.c

# ListeChainee.o : ListeChainee.c ListeChainee.h
# 	gcc -c ListeChainee.c
