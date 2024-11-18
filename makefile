CC: gcc
CFLAGS: -o
all: build
build:
	$(CC) $(CFLAGS) main.c structs.c -o main
run:
	$(CC) $(CFLAGS) main.c structs.c -o main; ./main; rm main
clean:
	rm main
