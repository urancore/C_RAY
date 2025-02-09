CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MT $@ -MMD -MP -MF $(D)/$*.d

O = out
D = $(O)/.deps

SRC = main.c map.c misc.c renderer.c
LIB = -lopengl32 -lgdi32 -luser32
BIN = $(O)/c_ray.exe

OBJS = $(SRC:%.c=$(O)/%.o)
DEPS = $(SRC:%.c=$(D)/%.d)

.PHONY: all clean

all: $(D) $(BIN)
	$(BIN)

clean:
	rm -f $(OBJS) $(DEPS) $(BIN)

$(D):
	mkdir -p $(D)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(BIN)

$(O)/%.o: %.c $(D)/%.d
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

$(DEPS):

include $(wildcard $(DEPS))
