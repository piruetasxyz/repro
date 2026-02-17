#include "ui.h"
#include "pico/stdlib.h"

#define BTN_PLAY 10
#define BTN_STOP 11

void ui_init()
{
    gpio_init(BTN_PLAY);
    gpio_set_dir(BTN_PLAY, GPIO_IN);
    gpio_pull_up(BTN_PLAY);

    gpio_init(BTN_STOP);
    gpio_set_dir(BTN_STOP, GPIO_IN);
    gpio_pull_up(BTN_STOP);
}

bool ui_play_pressed()
{
    return !gpio_get(BTN_PLAY);
}

bool ui_stop_pressed()
{
    return !gpio_get(BTN_STOP);
}

void ui_update()
{
    sleep_ms(10); // simple debounce
}