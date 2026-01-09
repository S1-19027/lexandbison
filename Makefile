# Makefile for SysY semantic analyzer (flex + bison)

CC      := gcc
BISON   := bison
FLEX    := flex
CFLAGS  := -g -Wall
LDFLAGS := -lfl

TARGET  := parser
OBJS    := parser.tab.o lex.yy.o semantic.o
HEADERS := ast.h semantic.h

.PHONY: all clean run test-all rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Bison generates parser.tab.c and parser.tab.h
parser.tab.c parser.tab.h: parser.y
	$(BISON) -d -v parser.y

# Flex generates lex.yy.c and requires the header from bison
lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

# Object compilation rules
semantic.o: semantic.c $(HEADERS)
	$(CC) $(CFLAGS) -c semantic.c

parser.tab.o: parser.tab.c $(HEADERS)
	$(CC) $(CFLAGS) -c parser.tab.c

lex.yy.o: lex.yy.c $(HEADERS)
	$(CC) $(CFLAGS) -c lex.yy.c

# Run with: make run file=testX.sy
run: $(TARGET)
	@if [ -z "$(file)" ]; then \
	  echo "Usage: make run file=your.sy"; exit 1; \
	fi
	./$(TARGET) "$(file)"

# Quick loop over test*.sy
test-all: $(TARGET)
	@for f in test*.sy; do \
	  echo "=== $$f ==="; \
	  ./$(TARGET) "$$f"; \
	  echo; \
	done

rebuild: clean all

clean:
	rm -f $(TARGET) $(OBJS) parser.tab.c parser.tab.h lex.yy.c parser.output
