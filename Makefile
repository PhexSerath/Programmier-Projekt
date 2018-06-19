#!/usr/bin/make
.SUFFIXES:
SRC = prog.c
TAR = prog
OBJ = prog.o

BUILD_DIR = build
TEST_DIR = programmierprojekt/test_cases
EXAMPELS= $(wildcard $(TEST_DIR)/*.dat)
NAME= $(notdir $(EXAMPELS))
CFLAGS = -std=gnu11 -c -g
echo= echo

$(BUILD_DIR):
	mkdir -p $@

#cp -f $< $@

LIST = $(foreach ele, $(NAME), $(TO))
TO = cp -f $(TEST_DIR)/$(ele) $(BUILD_DIR)/$(ele);

TEST = example01.dat

ls:

copy:
	@$(LIST)
	cp -f $(SRC) $(BUILD_DIR)/$(SRC)

%.o: %.c
	cd $(BUILD_DIR) && $(CC) $(CFLAGS) $^ -o $@

%: %.o
	cd $(BUILD_DIR) && $(CC) -o $@ $^
	
all: clean copy $(TAR)

run: all
	cd $(BUILD_DIR) && ./prog < $(TEST)

runLog: all
	cd $(BUILD_DIR) && ./prog < $(TEST) > log.txt

clean:
	cd $(BUILD_DIR) && $(RM) $(RMFILES) $(TAR) $(OBJ)
	
val: all
	cd $(BUILD_DIR) && G_SLICE=always-malloc G_DEBUG=gc-friendly  valgrind -v --tool=memcheck --leak-check=full --show-leak-kinds=all --num-callers=40 --log-file=valgrind.log ./prog < $(TEST)