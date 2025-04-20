#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"             // Biblioteca principal da Pico
#include "hardware/structs/timer.h" // Para usar alarmes via add_alarm_in_us
#include "hardware/gpio.h"         // Para controle de GPIO

#define BUZZER_PIN 21

// Variáveis que vêm do display, indicando se há colisão com a borda
bool tocou_borda;
int stage_retangulo;

static alarm_id_t buzzer_alarm_id = -1; // Armazena o ID do alarm ativo (usado para cancelar depois)
static bool buzzer_estado = false;     // Controla do estado atual do buzzer (ligado ou desligado)

//Callback executado automaticamente após o tempo definido com add_alarm_in_us.
//Serve para alternar o estado do buzzer em intervalos curtos, simulando um sinal sonoro contínuo (ex: 500Hz).
int64_t buzzer_alarm_callback(alarm_id_t id, void *user_data) {
    // Só liga o buzzer se estiver colidindo com as bordas e a borda estiver ativa
    if (stage_retangulo != 0 && tocou_borda) {
        buzzer_estado = !buzzer_estado;          // Alterna o estado do buzzer (toggle)
        gpio_put(BUZZER_PIN, buzzer_estado);    // Atualiza o pino com o novo estado
        return 2000;                           // Reagenda para daqui a 2000 microssegundos (500Hz)
    } else {
        gpio_put(BUZZER_PIN, 0);             // Garante que o buzzer esteja desligado
        buzzer_estado = false;              // Reseta o estado
        buzzer_alarm_id = -1;              // Marca que não há alarme ativo
        return 0;                         // Cancela o alarme (não reexecuta)
    }
}

/*
 * Inicializa o pino do buzzer, definindo como saída e garantindo que inicie desligado.
 */
void buzzer_init() {
    gpio_init(BUZZER_PIN);       // Inicializa o GPIO
    gpio_set_dir(BUZZER_PIN, GPIO_OUT); // Define como saída
    gpio_put(BUZZER_PIN, 0);     // Começa com o pino em nível baixo (desligado)
}

/* Inicia o ciclo de som do buzzer caso ainda não esteja rodando.
 * Agenda a função de callback para começar a tocar (chamada contínua via alarm).*/
void buzzer_start_alarm() {
    if (buzzer_alarm_id < 0) {  // Só agenda se não tiver um alarm ativo
        buzzer_alarm_id = add_alarm_in_us(2000, buzzer_alarm_callback, NULL, true);
    }
}

// Cancela o som do buzzer, caso esteja ativo, e garante que o pino seja desligado.
void buzzer_stop_alarm() {
    if (buzzer_alarm_id >= 0) {             // Só cancela se um alarm estiver ativo
        cancel_alarm(buzzer_alarm_id);     // Cancela o alarme
        buzzer_alarm_id = -1;             // Reseta o ID
        gpio_put(BUZZER_PIN, 0);         // Desliga fisicamente o buzzer
        buzzer_estado = false;          // Reseta o estado de controle
    }
}

#endif
