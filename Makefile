CC = gcc
TARGET = my_ps

all:
	$(CC) my_ps.c -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) x1.txt x2.txt merged.txt
