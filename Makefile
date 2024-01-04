TARGET = lang-ant
CC = clang
FLAGS = -Wall --pedantic

SRCDIR = src
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(BINDIR)/%.o)


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) $(FLAGS) -o $@

$(BINDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	@$(CC) $(FLAGS) -c $< -o $@

test: $(BINDIR)/$(TARGET)
	$(BINDIR)/$(TARGET) 20 20 10 e round

.PHONY: clean
clean:
	@rm -f $(BINDIR)/*
