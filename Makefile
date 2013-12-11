CFLAGS = -Wall -DDEBUG=1
CC = c++


compile:
	$(CC) $(CFLAGS) main.cpp -o converter.out

run: compile
	./converter.out ./The.Big.Bang.Theory.S07E02.avi

clean:
	rm *.out