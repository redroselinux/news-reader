CC      := gcc
CFLAGS  := -O3 -std=c23 -Wall -Wextra
SRCS     = $(wildcard src/*.c)
OBJS     = $(SRCS:src/%.c=build/%.o)
TARGET  := news-reader
STD     := -std=c23
PREFIX  := /usr
DESTDIR :=

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(STD) -o $@ $^ -lcurl

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c -o $@ $

build:
	mkdir -p build

clean:
	rm -rf build

distclean: clean
	rm -f $(TARGET)

install: $(TARGET)
	install -D -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

.PHONY: all clean install distclean
