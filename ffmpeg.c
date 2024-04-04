#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int checkForAc3(char *args[], int argc) {
    for (int i = 1; i < argc; i++) {
        if (strncmp(args[i], "-c:a:", 5) == 0) {
            if (strcmp(args[i+1], "ac3") == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void modifyAudioBitrate(char *args[], int argc, char *bitrate) {
    for (int i = 1; i < argc; i++) {
        if (strncmp(args[i], "-ab:a:", 6) == 0) {
            args[i+1] = bitrate;
            return;
        }
    }
}

char *getEnv(char *key, char *fallback) {
    char *value = getenv(key);
    if (value != NULL) {
        return value;
    } else {
        return fallback;
    }
}

int main(int argc, char *argv[]) {
    char *args[argc];
    for (int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }

    if (checkForAc3(args, argc)) {
        char *customBitrate = getEnv("EMBY_CUSTOM_AC3_BITRATE", "640000");
        modifyAudioBitrate(args, argc, customBitrate);
    }

    char *ffmpegPath = getEnv("EMBY_CUSTOM_FFMPEG_PATH", "/opt/emby-server/bin/_ffmpeg");

    execv(ffmpegPath, args);

    // execv will only return if there is an error
    perror("Error executing ffmpeg");
    return 1;
}
