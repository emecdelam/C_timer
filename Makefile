CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
LIBS = -lm

EXAMPLE = example
SOURCES = example.c timer.c
HEADERS = timer.h


all: $(EXAMPLE)

$(EXAMPLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(LIBS)

run: $(EXAMPLE)
	./$(EXAMPLE)

plot:
	python3 ./plot.py

clean:
	rm -f $(EXAMPLE)
	rm *.csv
	rm *.png


