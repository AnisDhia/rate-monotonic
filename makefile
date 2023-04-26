CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
SRC_DIR = ./src
OUT_DIR = ./bin
TARGET = rma

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SRCS))

$(OUT_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< 

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)
