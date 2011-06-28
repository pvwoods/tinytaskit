#include "main.h"

static void printInstructions(){
    printf("Usage: tinytaskit <command> [<args>]\n");
    printf("\nAvailable Commands:\n");
    printf("\tinit:\t\tcreate a tinytaskit instance\n");
    printf("\tadd:\t\tadd a task\n");
    printf("\tclose:\t\tclose a task as complete\n");
    printf("\tactive:\t\tlist all active tasks\n");
    printf("\tcomplete:\tlist all complete tasks\n");
}

static void convertToHex(const char* data, size_t size, unsigned char* hex) {
    int i;
    for(i = 0; i < size; ++i){
        sprintf(hex, "%s%x%x", hex, ((unsigned char)data[i])/16, ((unsigned char)data[i])%16); 
    }
}

static void generateSHA1Hash(const char* data, size_t size, char* dgst){
    sha1_ctx ctx;
    int i;
    
    sha1_begin(&ctx);
    for(i = 0; i < size; ++i)
        sha1_hash(data+i, 1, &ctx);
    sha1_end(dgst, &ctx);
    
}

static void generateKey(char *input, unsigned char *key){
   char output[SHA1_DIGEST_SIZE];
   generateSHA1Hash(input, sizeof(input) - 1, output);
   convertToHex(output, SHA1_DIGEST_SIZE, key);
}

int directoryExists(char *directory){
    struct stat st;
    if(stat(directory,&st) == 0){
        return 1;
    }
    return 0;
}

int tinyTaskitInstanceExists(){
    return directoryExists("./.tinytaskit");
}

int isFirstRun(){
    char confPath[512];
    char *home = getenv ("HOME");    
    if (home != NULL){
        snprintf(confPath, sizeof(confPath), "%s/.tinytaskit/", home);
        return directoryExists(confPath) == 1 ? 0:1;
    }
    return 1;
}

void runFirstUseFlow(){

    char username[21];
    unsigned char userKey[SHA1_DIGEST_SIZE] = "";
    char confPath[512];
    char confFile[512];
    char *home = getenv ("HOME");
    
    if (home != NULL){
        snprintf(confPath, sizeof(confPath), "%s/.tinytaskit/", home);
        snprintf(confFile, sizeof(confFile), "%s/tinytaskit.conf", confPath);
    }else{
        printf("could not set home variable!");
        return;
    }

    printf("It looks like this is your first time running TinyTaskit.\nPlease enter a user name  up to 20 characters to associate with your tasks.\nUserName: ");

    if(scanf("%20s", username) == 1){
        printf("Setting username as: %s\n", username);
        mkdir(confPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        FILE *setupFile;
        setupFile = fopen(confFile, "w");
        if(setupFile == NULL){
            printf("Error attempting to setup TinyTaskit\n");
        }else{
            generateKey(username, userKey);
            printf("%s:%s\n",username, userKey);
            fclose(setupFile);
            printf("TinyTaskit has been set up.\n");
        }
    }
}

int loadConfig(){
    return 1;
}
    

int command_init(){
    if(tinyTaskitInstanceExists() != 1){
        mkdir("./.tinytaskit", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        FILE *initFile;
        initFile = fopen("./.tinytaskit/manifest", "w");
        if(initFile == NULL){
            printf("Error attempting to init TinyTaskit\n");
            return 0;
        }else{
            fclose(initFile);
            printf("TinyTaskit instance created\n");
            return 1;
        }

    }
    printf("TinyTaskit instance already exists!\n");
    return 0;
}

int command_add(char *task){
    return 1;
}

int command_close(){
    return 1;
}

int command_active(){
    return 1;
}

int command_complete(){
    return 1;
}

void registerCommands(){
    //
}

int main(int argc, char *argv[]){
    if(isFirstRun() == 0){
        if(argc > 1){
            command_init();
        }else{
            printInstructions();
        }
    }else{
        runFirstUseFlow();
    }
    return 1;
    
}