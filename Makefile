CFLAGS = -std=c11 -Wall -Werror -Wextra
OBJDIR = build
OBJS = $(OBJDIR)/input.o $(OBJDIR)/main.o $(OBJDIR)/parser.o $(OBJDIR)/shell.o 

all: mysh

mysh: $(OBJS)
	gcc $^ -o $@ -lreadline

$(OBJDIR)/input.o : src/input.c include/input.h | $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o : src/main.c include/shell.h | $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR)/parser.o : src/parser.c include/parser.h | $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR)/shell.o : src/shell.c include/shell.h include/parser.h include/input.h | $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm mysh

rebuild: clean all

.PHONY: all clean rebuild