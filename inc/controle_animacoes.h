#ifndef CONTROLE_ANIMACAO_H
#define CONTROLE_ANIMACAO_H

#include <inc/matriz_led.h>
#include <inc/animacoes/off.h>
#include <inc/animacoes/cerveja.h>
#include <inc/animacoes/relogio.h>
#include <inc/animacoes/cobrinha.h>

// A cada clique no botão B, alterna entre uma animação nova e suspensão de animação
void animacoes(int num_animacao, int duration){
    
    if (num_animacao == 0) {
        printf("%d - Animação Cobrinha.\n", num_animacao);
        display_animacao_cobrinha();
        gpio_put(LED_PIN_BLUE, 1);
        gpio_put(LED_PIN_RED, 0);
        snake_animation(duration);

    }
    else if (num_animacao == 1) {
        printf("%d - Animacação Desligada.\n", num_animacao);
        display_animacao_suspensa();
        gpio_put(LED_PIN_GREEN, 1);
        gpio_put(LED_PIN_BLUE, 0);
        off_animation();
    }
    else if (num_animacao == 2) {
        printf("%d - Animação Relógio.\n", num_animacao);
        display_animacao_relogio();
        gpio_put(LED_PIN_BLUE, 1);
        gpio_put(LED_PIN_GREEN, 0);
        clock_animation(duration);
    }
    else if (num_animacao == 3) {
        printf("%d - Animacação Desligada.\n", num_animacao);
        gpio_put(LED_PIN_GREEN, 1);
        gpio_put(LED_PIN_BLUE, 0);
        display_animacao_suspensa();
        off_animation();
    }
    else if (num_animacao == 4) {
        printf("%d - Animacação Copo de Cerveja.\n", num_animacao);
        gpio_put(LED_PIN_BLUE, 1);
        gpio_put(LED_PIN_GREEN, 0);
        display_animacao_cerveja();
        beer_animation(duration);
    
    } else if (num_animacao == 5){
        printf("%d - Animacação Desligada.\n", num_animacao);
        gpio_put(LED_PIN_GREEN, 1);
        gpio_put(LED_PIN_BLUE, 0);
        display_animacao_suspensa();
        off_animation();
    }
}

#endif