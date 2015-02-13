CC=g++
INC=-I ./include/
FLAG=-g
LIB=
SRC=./src/
OBJ=$(SRC)/emap.o $(SRC)/box.o $(SRC)/hox_box.o $(SRC)/ho_box.o $(SRC)/tools.o $(SRC)/box_tools.o
EXE=main

default: $(EXE)

$(EXE): $(EXE).o $(OBJ)
	$(CC) $(FLAG) $(LIB) $(INC) -o $@ $@.o $(OBJ)

.C.o:
	$(CC) -c $(FLAG) $(INC) -o $@ $<

clean: 
	rm -f $(EXE)
	rm -f $(EXE).o
	rm -f $(OBJ)

