CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = test_lis3mdl
OBJS = i2c.o lis3mdl.o test_lis3mdl.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

i2c.o: i2c.c i2c.h
	$(CC) $(CFLAGS) -c i2c.c

lis3mdl.o: lis3mdl.c lis3mdl.h i2c.h
	$(CC) $(CFLAGS) -c lis3mdl.c

test_lis3mdl.o: test_lis3mdl.c lis3mdl.h i2c.h
	$(CC) $(CFLAGS) -c test_lis3mdl.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
