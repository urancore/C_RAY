CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MT $@ -MMD -MP -MF $(D)/$*.d

O = out
D = $(O)/.deps
LIB = -lkernel32 -luser32
SRC = sys_win.c

BIN_RAY = $(O)/stupid3dtry.exe

OBJS_COMMON = $(SRC:%.c=$(O)/%.o)
DEPS = $(SRC:%.c=$(D)/%.d)

.PHONY: all clean

all: $(D) $(BIN_RAY)
	$(BIN_RAY)

clean:
	rm -f $(OBJS_COMMON) $(OBJS_RAY) $(OBJS_EDITOR) $(DEPS) $(BIN)

$(D):
	mkdir -p $(D)

$(BIN_RAY): $(OBJS_COMMON) $(OBJS_RAY)
	$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_RAY) $(LIB) -o $(BIN_RAY)

$(BIN_EDITOR): $(OBJS_COMMON) $(OBJS_EDITOR)
	$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_EDITOR) $(LIB) -o $(BIN_EDITOR)

$(O)/%.o: %.c $(D)/%.d
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

$(DEPS):

include $(wildcard $(DEPS))
