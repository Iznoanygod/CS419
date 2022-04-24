#include <stdlib.h>
#include <stdio.h>

static unsigned long
sdbm(unsigned char *str) {
    unsigned long hash = 0;
    int c;
    while(c = *str++)
        hash = c + ( hash << 6) + (hash << 16) - hash;
    return hash;
}

char rng_gen(unsigned long prev_seq) {
    int m = 256;
    int a = 1103515245;
    int c = 12345;
    return (a * prev_seq + c) % m;
}

int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Error occured\n");
        exit(0);
    }
    FILE *input_file;
    FILE *output_file;
    char *password;
    char input_buffer[2048];

    password = argv[1];
    input_file = fopen(argv[2], "r");
    output_file = fopen(argv[3], "w+");

    if(input_file == NULL || output_file == NULL) {
        printf("Error occured\n");
        exit(0);
    }

    unsigned long hash = sdbm(password);
    char rng_val = rng_gen(hash);
    
    int read_in;
    while(read_in = fread(input_buffer, 1, 2048, input_file)) {
        for(int i = 0; i < read_in; i++) {
            input_buffer[i] = rng_val ^ input_buffer[i];
            rng_val = rng_gen(rng_val);
        }
        fwrite(input_buffer, 1, read_in, output_file);
    }
}
