CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MT $@ -MMD -MP -MF $(D)/$*.d

O = out
D = $(O)/.deps
LIB = -lkernel32 -luser32
SRC = sys_win.c engine.c common.c zone.c gl_vidnt.c

BIN = $(O)/stupid3dtry.exe

OBJS = $(SRC:%.c=$(O)/%.o)
DEPS = $(SRC:%.c=$(D)/%.d)

.PHONY: all clean

all: $(D) $(BIN)
	$(BIN)

clean:
	rm -f $(OBJS_) $(DEPS) $(BIN)

$(D):
	mkdir -p $(D)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Wl,-subsystem,windows $(LIB) -o $(BIN)

$(O)/%.o: %.c $(D)/%.d
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

$(DEPS):

include $(wildcard $(DEPS))
