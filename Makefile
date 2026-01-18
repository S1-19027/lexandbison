# Makefile for SysY semantic analyzer (flex + bison)

CC      := gcc
BISON   := bison
FLEX    := flex
CFLAGS  := -g -Wall
LDFLAGS := -lfl

# RISC-V toolchain (change if needed)
RISCV_GCC     ?= riscv64-unknown-elf-gcc
RISCV_OBJDUMP ?= riscv64-unknown-elf-objdump
RISCV_OBJCOPY ?= riscv64-unknown-elf-objcopy
RISCV_FLAGS   := -march=rv32im -mabi=ilp32

TARGET  := parser
OBJS    := parser.tab.o lex.yy.o semantic.o irgen.o codegen.o
HEADERS := ast.h semantic.h irgen.h codegen.h

.PHONY: all clean run test-all rebuild
.PHONY: riscv-all clean-riscv toolcheck

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

irgen.o: irgen.c $(HEADERS)
	$(CC) $(CFLAGS) -c irgen.c

codegen.o: codegen.c $(HEADERS)
	$(CC) $(CFLAGS) -c codegen.c

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

# Pattern rule: generate assembly from .sy using our parser
%.s: %.sy $(TARGET)
	./$(TARGET) "$<" >/dev/null

# Assemble .s to object (.o) for RV32
%.o: %.s
	$(RISCV_GCC) $(RISCV_FLAGS) -c "$<" -o "$@"

# Convert .o to raw binary (.bin)
%.bin: %.o
	$(RISCV_OBJCOPY) -O binary "$<" "$@"

# Disassemble object to readable dump
%.dump: %.o
	$(RISCV_OBJDUMP) -d -M no-aliases -M numeric "$<" > "$@"

# Build machine code for all test_ir*.sy
riscv-all: $(patsubst %.sy,%.o,$(wildcard test_ir*.sy)) \
	          $(patsubst %.sy,%.bin,$(wildcard test_ir*.sy)) \
	          $(patsubst %.sy,%.dump,$(wildcard test_ir*.sy))
	@echo "Built RISC-V objects/binaries for test_ir*.sy"

# Check toolchain availability
toolcheck:
	@command -v $(RISCV_GCC) >/dev/null 2>&1 || { echo "Missing $(RISCV_GCC). Install gcc-riscv64-unknown-elf."; exit 1; }
	@command -v $(RISCV_OBJCOPY) >/dev/null 2>&1 || { echo "Missing $(RISCV_OBJCOPY)."; exit 1; }
	@command -v $(RISCV_OBJDUMP) >/dev/null 2>&1 || { echo "Missing $(RISCV_OBJDUMP)."; exit 1; }
	@echo "RISC-V toolchain OK"

clean-riscv:
	rm -f *.s *.o *.bin *.dump

rebuild: clean all

clean:
	rm -f $(TARGET) $(OBJS) parser.tab.c parser.tab.h lex.yy.c parser.output
