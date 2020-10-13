SRC_DIR := .
TEST_DIR := ./test

CC := gcc
STD := c99
CFLAGS := -g -std=$(STD) -O -Werror -Wall -Wextra -pedantic
CMOCKA := -lcmocka
APPROVALS := -lapprovals

ifeq ($(OS),Windows_NT)
	EXE := .exe
else
	EXE := .
	CFLAGS += -fPIC
endif

SRC_SRC := $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ := $(SRC_SRC:.c=.o)

TEST_SRC := $(wildcard $(TEST_DIR)/*Test.c)
TEST_EXE := $(TEST_SRC:.c=$(EXE))

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@
.SECONDARY: $(SRC_OBJ)

$(TEST_DIR)/%$(EXE): $(TEST_DIR)/%.c ${SRC_OBJ}
	$(CC) $(CFLAGS) ${SRC_OBJ} $< $(CMOCKA) -o $@

$(TEST_DIR)/%$(EXE): $(TEST_DIR)/%.c ${SRC_OBJ}
	$(CC) $(CFLAGS) ${SRC_OBJ} -I$(SRC_DIR) $< $(CMOCKA) $(APPROVALS) -o $@

.PHONY: test
test: ${TEST_EXE}
	for exe in ${TEST_EXE}; do $$exe || exit; done

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(TEST_DIR)/*.o $(TEST_DIR)/*$(EXE) $(TEST_DIR)/*.received.*
	rm -r -f Default
