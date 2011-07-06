#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libsha1.h>
#include <time.h>
#include <string.h>

typedef struct {
    char userName[20];
    char userKey[SHA1_DIGEST_SIZE];
} taskitConfigData;

char userConfig[512];

char VERSION[] = "0.1";

char HOME_PATH[512];