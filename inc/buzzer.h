#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

#define BUZZER_PIN 21

static absolute_time_t buzzer_off_time;
static bool buzzer_ativo = false;

typedef enum {
    BUZZER_NONE,
    BUZZER_CURTO,
    BUZZER_MEDIO,
    BUZZER_GRAVE
} buzzer_tipo_t;

void buzzer_init() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}
#endif
