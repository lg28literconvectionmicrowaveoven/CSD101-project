CC: gcc
CFLAGS: -o
all: build
build:
	$(CC) $(CFLAGS) main.c structs.c utils.c ./cJSON/cJSON.c ./cJSON/cJSON_Utils.c -o main
run:
	$(CC) $(CFLAGS) main.c structs.c utils.c ./cJSON/cJSON.c ./cJSON/cJSON_Utils.c -o main; ./main; rm main
clean:
	rm main
