#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "midi_engine.h"
#include "storage.h"
#include "ui.h"

int main()
{

    stdio_init_all();

    midi_engine_init();
    storage_init();
    ui_init();

    multicore_launch_core1(midi_engine_core1_entry);

    while (true)
    {

        ui_update();

        if (ui_play_pressed())
        {
            midi_engine_start();
        }

        if (ui_stop_pressed())
        {
            midi_engine_stop();
        }
    }
}