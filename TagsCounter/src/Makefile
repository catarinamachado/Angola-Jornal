EXEC := tag_counter

CXX := gcc
FLAGS := -std=c11 -g -Ofast
GLIB := `pkg-config --cflags --libs glib-2.0`
INCD := -I ../include

all:
	@flex counter.l
	$(CXX) -o $(EXEC) MultiSet.c lex.yy.c $(FLAGS) $(GLIB) $(INCD)

clean:
	rm -rf lex.yy.c $(EXEC)
