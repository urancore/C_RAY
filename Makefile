CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MT $@ -MMD -MP -MF $(D)/$*.d

SRC = main.c renderer.c
LIBS = -lopengl32 -lgdi32 -luser32
BIN = c_ray.exe

O = out
D = $(O)/.deps
OBJS = $(SRC:%.c=$(O)/%.o)
DEPS = $(SRC:%.c=$(D)/%.d)

.PHONY: all clean

all: $(D) $(O)/$(BIN)
	$(O)/$(BIN)

clean:
	rm -f $(OBJS) $(DEPS) $(BIN)

$(D):
	mkdir -p $(D)

$(O)/$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(O)/$(BIN)

$(O)/%.o: %.c $(D)/%.d
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@

$(DEPS):

include $(wildcard $(DEPS))