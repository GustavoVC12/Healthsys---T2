CC = gcc
CFLAGS = -std=c11 -O2 -w    # -w suprime warnings para ignorar sugestões não críticas
TARGET = healthsys
OBJ = main.o bdpacientes.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: main.c bdpacientes.h
	$(CC) $(CFLAGS) -c main.c

bdpacientes.o: bdpacientes.c bdpacientes.h
	$(CC) $(CFLAGS) -c bdpacientes.c

clean:
	rm -f $(OBJ) $(TARGET)
