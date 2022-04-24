#include <stdlib.h>
#include <stdio.h>

char encrypt(char key, char text) {
    return (key + text) % 256;
}

int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Error occured\n");
        exit(0);
    }

    FILE *key_file;
    FILE *input_file;
    FILE *output_file;
    char key_buffer[2048];
    char input_buffer[2048];
    int key_size;

    key_file = fopen(argv[1], "r");
    input_file = fopen(argv[2], "r");
    output_file = fopen(argv[3], "w+");

    if(key_file == NULL || input_file == NULL || output_file == NULL) {
        printf("Error occured\n");
        exit(0);
    }

    key_size = fread(key_buffer, 1, 2048, key_file);
    
    int key_tracker = 0;
    int read_in;
    while(read_in = fread(input_buffer, 1, 2048, input_file)) {
        for(int i = 0; i < read_in; i++) {
            input_buffer[i] = encrypt(key_buffer[key_tracker], input_buffer[i]);
            key_tracker = (key_tracker + 1) % key_size;
        }
        fwrite(input_buffer, 1, read_in, output_file);
    }
}
