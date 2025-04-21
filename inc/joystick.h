#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "hardware/adc.h"

// Definição dos pinos dos potenciômetros do joystick
#define VRX_PIN 27   // Pino de entrada analógica para eixo X do joystick
#define VRY_PIN 26 // Pino de entrada analógica para eixo Y do joystick
#define SW_PIN 22      // Pino para o botão do joystick

bool sw_value;

uint32_t last_print_time = 0; // Variável para controle de tempo do printf

void joystick_init(){
    // Configura os pinos do joystick como entradas analógicas
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
    //Configura o botão do joystick como entrada
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);
}

void controle_joystick_box(){
    // Lê o valor do eixo X do joystick (pino ADC 1)
    adc_select_input(1);  
    vrx_value = adc_read();
    // Lê o valor do eixo Y do joystick (pino ADC 0)
    adc_select_input(0);  
    vry_value = adc_read();
    // Lê o estado do botão do joystick (true ou false)
    sw_value = gpio_get(SW_PIN) == 0; 

    // A cada clique no botão do joystick, o led verde mudará seu estado e as bordas do display mudaram
    if (sw_value) {

        // Altera o estágio do retângulo
        stage_retangulo = (stage_retangulo + 1) % 4;  //Cicla entre os estágios do retângulo (0, 1, 2, 3)
        sleep_ms(200);  //Debounce do botão para evitar múltiplos cliques
    }

    // Exibe valores no console a cada 1s
    uint32_t current_time = to_ms_since_boot(get_absolute_time());  
    if (current_time - last_print_time >= 1000) {
        printf("x_pos: %d, y_pos: %d\n", x_pos, y_pos);
        last_print_time = current_time;
    }
}

#endif