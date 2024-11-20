CC: gcc
CFLAGS: -o
all: build
build:
	$(CC) $(CFLAGS) main.c ./lib/structs.c ./lib/utils.c ./cJSON/cJSON.c -o main
run:
	$(CC) $(CFLAGS) main.c ./lib/structs.c ./lib/utils.c ./cJSON/cJSON.c -o main; ./main; rm main
clean:
	rm main
