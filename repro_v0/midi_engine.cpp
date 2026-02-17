#include "midi_engine.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "pico/multicore.h"

#define MIDI_UART uart0
#define MIDI_TX_PIN 0
#define MIDI_BAUD 31250

static volatile bool playing = false;
static uint64_t start_time = 0;

void send_byte(uint8_t b)
{
    uart_putc_raw(MIDI_UART, b);
}

void send_note_on(uint8_t note)
{
    send_byte(0x90);
    send_byte(note);
    send_byte(100);
}

void send_note_off(uint8_t note)
{
    send_byte(0x80);
    send_byte(note);
    send_byte(0);
}

void midi_engine_init()
{
    uart_init(MIDI_UART, MIDI_BAUD);
    gpio_set_function(MIDI_TX_PIN, GPIO_FUNC_UART);
    uart_set_format(MIDI_UART, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(MIDI_UART, false);
}

void midi_engine_start()
{
    start_time = time_us_64();
    playing = true;
}

void midi_engine_stop()
{
    playing = false;

    // All Notes Off safety
    for (int ch = 0; ch < 16; ch++)
    {
        send_byte(0xB0 | ch);
        send_byte(123);
        send_byte(0);
    }
}

void midi_engine_core1_entry()
{

    while (true)
    {

        if (!playing)
        {
            tight_loop_contents();
            continue;
        }

        uint64_t now = time_us_64() - start_time;

        // Stub demo: play C every second
        if (now % 1000000 < 1000)
        {
            send_note_on(60);
        }

        if (now % 1000000 > 500000 &&
            now % 1000000 < 501000)
        {
            send_note_off(60);
        }
    }
}
