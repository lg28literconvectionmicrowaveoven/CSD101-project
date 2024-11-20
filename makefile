CC: gcc
CFLAGS: -o
SRC: main.c ./lib/structs.c ./lib/utils.c ./cJSON/cJSON.c
all: build
build:
	$(CC) $(CFLAGS) $(SRC) -o main
run:
	$(CC) $(CFLAGS) $(SRC )-o main; ./main; rm main
clean:
	rm main
