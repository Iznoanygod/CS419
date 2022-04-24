#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static unsigned long
sdbm(unsigned char *str) {
    unsigned long hash = 0;
    int c;
    while(c = *str++)
        hash = c + ( hash << 6) + (hash << 16) - hash;
    return hash;
}

void xor_block(char* text, char* key) {
    for(int i = 0; i < 16; i++) {
        text[i] = text[i] ^ key[i];
    }
}

char rng_gen(unsigned long prev_seq) {
    int m = 256;
    int a = 1103515245;
    int c = 12345;
    return (a * prev_seq + c) % m;
}

void shuffle(char* key, char* block) {
    for(int i = 15; i > -1; i--) {
        int first = key[i] & 0xf;
        int second = (key[i] >> 4) & 0xf;
        char temp = block[first];
        block[first] = block[second];
        block[second] = temp;
    }
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
    char initialization_vector[16];
    char ciphertext_block[16];
    char plaintext_block[16];
    char keystream_block[16];
    for(int i = 0; i < 16; i++) {
        initialization_vector[i] = rng_val;
        rng_val = rng_gen(rng_val);
    }
    int read_in;
    char first_loop = 1;
    while(read_in = fread(ciphertext_block, 1, 16, input_file)) {
        if(!first_loop) {
            fwrite(plaintext_block, 1, 16, output_file);
        }

        for(int i = 0; i < 16; i++) {
            keystream_block[i] = rng_val;
            rng_val = rng_gen(rng_val);
        }
        for(int i = 0; i < 16; i++) {
            plaintext_block[i] = ciphertext_block[i] ^ keystream_block[i];
        }
        shuffle(keystream_block, plaintext_block);
        xor_block(plaintext_block, initialization_vector);
        //fwrite(plaintext_block, 1, 16, output_file);
        first_loop = 0;
        for(int i = 0; i < 16; i++) {
            initialization_vector[i] = ciphertext_block[i];
        }
    }
    int truncate = plaintext_block[15];
    fwrite(plaintext_block, 1, 16 - truncate, output_file);
}
