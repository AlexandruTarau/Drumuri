CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: drumuri

run-p1:
	./drumuri

drumuri: drumuri.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Vom șterge executabilele.
clean:
	rm -f drumuri
