#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libsha1.h>

typedef struct {
    char userName[20];
    char userKey[SHA1_DIGEST_SIZE];
} taskitConfigData;