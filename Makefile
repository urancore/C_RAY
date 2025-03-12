CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MT $@ -MMD -MP -MF $(D)/$*.d

O = out
D = $(O)/.deps
LIB = -lopengl32 -lgdi32 -luser32 -lwinmm
SRC_COMMON = bind.c input.c main.c global.c map.c misc.c renderer.c text.c cmd.c sound.c sys_win.c zone.c R_renderer.c initfuncs.c game.c hud.c event.c
SRC_RAY = ray.c
SRC_EDITOR = editor.c

BIN_RAY = $(O)/ray.exe
BIN_EDITOR = $(O)/editor.exe

OBJS_COMMON = $(SRC_COMMON:%.c=$(O)/%.o)
DEPS = $(SRC_COMMON:%.c=$(D)/%.d)
OBJS_RAY = $(SRC_RAY:%.c=$(O)/%.o)
DEPS += $(SRC_RAY:%.c=$(D)/%.d)
OBJS_EDITOR = $(SRC_EDITOR:%.c=$(O)/%.o)
DEPS += $(SRC_EDITOR:%.c=$(D)/%.d)

.PHONY: ray editor clean

ray: $(D) $(BIN_RAY)
	$(BIN_RAY)

editor: $(D) $(BIN_EDITOR)
	$(BIN_EDITOR)

clean:
	rm -f $(OBJS_COMMON) $(OBJS_RAY) $(OBJS_EDITOR) $(DEPS) $(BIN_RAY) $(BIN_EDITOR)

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
