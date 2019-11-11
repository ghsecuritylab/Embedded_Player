//
// Created by olliekrk on 24.10.2019.
//

#include <ff.h>
#include <term_io.h>
#include "audio_loader.h"
#include "controls.h"

FRESULT AUDIO_L_CreateAudioDirectory(void) {
    FRESULT result = f_mkdir(AUDIO_DIRECTORY_PATH);
    if (result == FR_EXIST) {
        xprintf("Audio directory already exists.\r\n");
    }
    return result;
}

int AUDIO_L_ScanAudioDirectory() {
    DIR audioDirectory;
    FRESULT result;
    FILINFO fileInfo;
    int count = 0;

    result = f_findfirst(&audioDirectory, &fileInfo, AUDIO_DIRECTORY_PATH, "*.wav");
    if (result == FR_OK) {
        while (result == FR_OK && strlen(fileInfo.fname) > 0 && count < AUDIO_FILES_LIMIT) {
            APP_STATE.TRACKS[APP_STATE.TRACKS_COUNT] = malloc((strlen(fileInfo.fname) + 1) * sizeof(char));
            strcpy(APP_STATE.TRACKS[APP_STATE.TRACKS_COUNT], fileInfo.fname);
            APP_STATE.TRACKS_COUNT++;
            result = f_findnext(&audioDirectory, &fileInfo);
        }
        f_closedir(&audioDirectory);

        // Set first track
        APP_STATE.SELECTED_TRACK_INDEX = 0;
        APP_STATE.SELECTED_TRACK_NAME = APP_STATE.TRACKS[0];

    } else if (result == FR_NO_PATH) {
        xprintf("Empty audio directory will be created.\r\n");
        result = AUDIO_L_CreateAudioDirectory();
        if (result != FR_OK) {
            xprintf("Creation of audio directory has failed.\r\n");
            return -1;
        }
    } else if (result == FR_NO_FILE) {
        xprintf("Found zero WAV files.");
    }

    return count;
}

void AUDIO_L_PerformScan(void) {
    FRESULT result = AUDIO_L_CreateAudioDirectory();
    if (result == FR_OK || result == FR_EXIST) {
        AUDIO_L_ResetState();
        AUDIO_L_ScanAudioDirectory();
    }
}

void AUDIO_L_ResetState(void) {
    free(APP_STATE.TRACKS);
    APP_STATE.TRACKS = malloc(AUDIO_FILES_LIMIT * sizeof(char *));
    APP_STATE.TRACKS_COUNT = 0;
    APP_STATE.SELECTED_TRACK_INDEX = 0;
    APP_STATE.SELECTED_TRACK_NAME = "";
}
