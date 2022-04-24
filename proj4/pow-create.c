#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include <string.h>

#define THREAD_COUNT 8

int iterations = 0;
// 33 - 126

pthread_mutex_t thread_lock;
int winner = -1;
pthread_mutex_t thread_lock_lock;

typedef struct thread_arg {
    int tid;
    int difficulty;
    char hash[2 * SHA256_DIGEST_LENGTH + 1];
}thread_arg;

typedef struct return_arg {
    char *hash;
    char* pow;
    int leading;
}return_arg;

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

void powgen(int seed, char* buffer) {
    int i = 0;
    while(seed != 0) {
        buffer[i] = (seed % 94) + 33;
        seed /= 94;
        i++;
    }
    buffer[i] = 0;
    return;
}

void *worker_thread(void *arg) {
    thread_arg *args = (thread_arg*) arg;
    int tid = args->tid;
    int difficulty = args->difficulty;
    char* hash_string = args->hash;
    int work = tid +1;
    char *combined_string = malloc(4096);
    char *powbuf = malloc(2048);
    while(1) {
        powgen(work, powbuf);
        strcpy(combined_string, hash_string);
        strcat(combined_string, powbuf);
        char* hash = sha256(combined_string, strlen(combined_string));
        int zeros = leading_bits(hash, SHA256_DIGEST_LENGTH);
        if(zeros >= difficulty){
            break;
        }
        free(hash);
        work += THREAD_COUNT;
        iterations++;
    }
    pthread_mutex_lock(&thread_lock_lock);
    winner = tid;
    pthread_mutex_unlock(&thread_lock);
    return_arg *retval = malloc(sizeof(return_arg));
    retval->hash = sha256(combined_string, strlen(combined_string));
    retval->pow = powbuf;
    retval->leading = leading_bits(retval->hash, SHA256_DIGEST_LENGTH);
    pthread_exit(retval);
}

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Error: invalid number of arguments\n");
        printf("Usage: pow-create difficulty file\n");
        return 0;
    }
    
    FILE *input_file = fopen(argv[2], "r");

    if(input_file == NULL) {
        printf("Error: could not open file\n");
        return 0;
    }

    fseek(input_file, 0, SEEK_END);
    long long int size = ftell(input_file);
    rewind(input_file);
    char *message = malloc(size);
    printf("File: %s\n", argv[2]);
    fread(message, 1, size, input_file);
    char *hash = sha256(message, size);
    char *hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_string + 2*i, "%02hhx", hash[i] & 0xff);
    }
    printf("Initial-hash: %s\n", hash_string);
    pthread_mutex_init(&thread_lock, NULL);
    pthread_mutex_init(&thread_lock_lock, NULL);
    pthread_mutex_lock(&thread_lock);
    pthread_t tid[THREAD_COUNT];
    
    struct timeval oldtv;
    long double time = 0;
    gettimeofday(&oldtv, NULL);
    int difficulty = atoi(argv[1]);
    for(int i = 0; i < 8; i++) {
        thread_arg *arg = malloc(sizeof(thread_arg));
        arg->tid = i;
        arg->difficulty = difficulty;
        strcpy(arg->hash, hash_string);
        pthread_create(&tid[i], NULL, worker_thread, arg);
    }
    pthread_mutex_lock(&thread_lock);
    for(int i = 0; i < 8; i++) {
        if(winner != i){
            pthread_cancel(tid[i]);
        }
    }
    return_arg *retval;
    pthread_join(tid[winner], (void**)&retval);
    struct timeval newtv;
    gettimeofday(&newtv, NULL);
    time = (newtv.tv_sec - oldtv.tv_sec) + (newtv.tv_usec - oldtv.tv_usec)*1.0 / 1000000;
    printf("Proof-of-work: %s\n", retval->pow);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_string + 2*i, "%02hhx", retval->hash[i] & 0xff);
    }
    printf("Hash: %s\n", hash_string);
    printf("Leading-zero-bits: %d\n", retval->leading);

    printf("Iterations: %d\n", iterations);
    printf("Compute-time: %Lf\n", time);
}

