//
// Created by olliekrk on 21.10.2019.
//

#ifndef EMBEDDED_PLAYER_CONTROLS_H
#define EMBEDDED_PLAYER_CONTROLS_H

static int SELECTED_BUTTON = -1;

enum MainControls {
    CON_BUTTON_0 = 0,
    CON_BUTTON_1 = 1,
    CON_BUTTON_2 = 2,
    CON_BUTTON_3 = 3,
    CON_BUTTON_4 = 4,
    CON_BUTTON_5 = 5,
    CON_BUTTON_6 = 6,
    CON_BUTTON_7 = 7,
};

enum OptionControl {
    NEXT_TRACK = 8,
    BACK_TRACK = 9,
    SELECTED_TRACK = 10,
    EFFECT_1 = 11,
    EFFECT_2 = 12
};

void CON_HandleButtonTouched(int);

void CON_HandleOptionsTouch(int, int);

void CON_PlayLoadedSound(int);

#endif //EMBEDDED_PLAYER_CONTROLS_H
