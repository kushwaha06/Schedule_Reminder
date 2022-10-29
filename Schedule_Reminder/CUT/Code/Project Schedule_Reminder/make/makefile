PROJ=$(HOME)/Schedule_Reminder
INC = $(PROJ)/include
SRC = $(PROJ)/src
BIN = $(PROJ)/bin
OBJ = $(PROJ)/obj
CFLAGS = -c -g -Wall
GCC = gcc
IFLAGS = -I $(INC)


all : $(BIN)/output   


$(BIN)/output : $(OBJ)/main.o $(OBJ)/reminder.o
		$(GCC) -o $(BIN)/output $(OBJ)/main.o $(OBJ)/reminder.o


$(OBJ)/main.o : $(SRC)/main.c
		$(GCC) -o $(OBJ)/main.o $(CFLAGS) $(SRC)/main.c $(IFLAGS)


$(OBJ)/reminder.o : $(SRC)/reminder.c
		$(GCC) -o $(OBJ)/reminder.o $(CFLAGS) $(SRC)/reminder.c $(IFLAGS)


clean :
	rm $(BIN)/output
	rm $(OBJ)/*.o
				
