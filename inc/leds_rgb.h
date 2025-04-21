#ifndef LEDS_RGB_H
#define LEDS_RGB_H

// Definição dos pinos dos LEDs
#define LED_PIN_RED 13  
#define LED_PIN_BLUE 12
#define LED_PIN_GREEN 11

void leds_init(){
    //Configura os led como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
}

void off_leds(){
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_BLUE, 0);
    gpio_put(LED_PIN_GREEN, 0);
}

#endif
