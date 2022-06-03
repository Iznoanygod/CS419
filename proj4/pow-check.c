#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>

int leading_bits(const char *hash, int len) {
    int leading = 0;
    for(int i = 0; i < len; i++) {
        if(hash[i] == 0) {
            leading += 8;
            continue;
        }
        for(int j = 0; j < 8; j++) {
            if(hash[i] >> j == 0) {
                leading += 8 - j;
                goto afterloop;
            }
        }
        break;
    }
afterloop:
    return leading;
}

char *sha256(const char *str, int len) {
    char *hash = malloc(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256ctx;
    SHA256_Init(&sha256ctx);
    SHA256_Update(&sha256ctx, str, len);
    SHA256_Final(hash, &sha256ctx);
    return hash;
}

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("ERROR: invalid number of arguemnts\n");
        printf("Usage: pow-check file header\n");
        return 0;
    }
    FILE *input_file;
    FILE *header_file;
    
    input_file = fopen(argv[1], "r");
    header_file = fopen(argv[2], "r");

    if(input_file == NULL || header_file == NULL) {
        printf("ERROR: cannot open file\n");
        return 0;
    }

    fseek(input_file, 0, SEEK_END);
    int file_size = ftell(input_file);
    rewind(input_file);
    char *message = malloc(file_size);
    fread(message, 1, file_size, input_file);
    char *message_hash = sha256(message, file_size);
    char message_hash_string[2 * SHA256_DIGEST_LENGTH + 1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(message_hash_string + 2*i, "%02hhx", message_hash[i] & 0xff);
    }
    char line[4096];
    int leading_zero_bits;
    char valid_hash[1024];
    char pow_message[1024];
    int initial_hash = 0, pow = 0, zero_bit = 0, hash = 0;
    while(fgets(line, 4096, header_file)) {
        char tag[1024] = {0};
        char val[1024] = {0};
        sscanf(line, "%s %s", tag, val);
        if(!strcmp(tag, "Initial-hash:")){
            initial_hash = 1;
            if(strcmp(message_hash_string, val)) {
                printf("ERROR: initial hashes don't match\n");
                printf("\thash in header: %s\n", val);
                printf("\tfile hash: %s\n", message_hash_string);
                printf("fail\n");
                return 0;
            }
        }
        else if(!strcmp(tag, "Leading-zero-bits:")) {
            zero_bit = 1;
            leading_zero_bits = atoi(val);
        }

        else if(!strcmp(tag, "Hash:")) {
            hash = 1;
            strcpy(valid_hash, val);
        }

        else if(!strcmp(tag, "Proof-of-work:")) {
            pow = 1;
            strcpy(pow_message, val);
        }
    }
    if(pow == 0 || zero_bit == 0 || hash == 0 || initial_hash == 0) {
        if(!initial_hash)
            printf("ERROR: missing Initial-hash in header\n");
        if(!zero_bit)
            printf("ERROR: missing Leading-zero-bits in header\n");
        if(!pow)
            printf("ERROR: missing Proof-of-work in header\n");
        if(!hash)
            printf("ERROR: missing Hash in header\n");
        printf("fail\n");
        return 0;
    }
    char combined_message[4096];
    sprintf(combined_message, "%s%s", message_hash_string, pow_message);
    char *final_hash = sha256(combined_message, strlen(combined_message));
    int final_leading = leading_bits(final_hash, SHA256_DIGEST_LENGTH);
    if(final_leading != leading_zero_bits){
        printf("ERROR: incorrect Leading-bits value: %d, expected %d\n", leading_zero_bits, final_leading);
        printf("fail\n");
        return 0;
    }
    char final_hash_string[2 * SHA256_DIGEST_LENGTH + 1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(final_hash_string + 2*i, "%02hhx", final_hash[i] &0xff);
    }
    if(strcmp(final_hash_string, valid_hash)) {
        printf("ERROR: pow hash does not match Hash header\n");
        printf("\texpected: %s\n", final_hash_string);
        printf("\theader has: %s\n", valid_hash);
        printf("fail\n");
        return 0;
    }
    printf("pass\n");
}
