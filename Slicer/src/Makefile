EXEC := slicer

CXX := gcc
F= -std=c11 -g -Ofast

all:
	@flex glue.l
	$(CXX) -o $(EXEC) lex.yy.c $(FLAGS)

clean:
	rm -rf lex.yy.c $(EXEC)
