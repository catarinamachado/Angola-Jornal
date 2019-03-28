EXEC := transformer

CXX := gcc
FLAGS := -std=c11 -g -Ofast
GLIB := `pkg-config --cflags --libs glib-2.0`
INCD := -I ../include

all:
	@flex transformer.l
	$(CXX) -o $(EXEC) Angola.c lex.yy.c $(FLAGS) $(GLIB) $(INCD)

clean:
	rm -rf lex.yy.c $(EXEC)
