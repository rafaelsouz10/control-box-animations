#ifndef CONFIG_BTN_H
#define CONFIG_BTN_H

#include "hardware/timer.h"

//definição de GPIO botões
#define BTN_A 5
#define BTN_B 6

// Variáveis globais 
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
int num_animacao = -1;

bool acao_botao_A = true;
bool acao_botao_B = false;

// Configuração inicial ds botões
void setup_gpio_BTN() {
  //Botão A
  gpio_init(BTN_A);
  gpio_set_dir(BTN_A, GPIO_IN);
  gpio_pull_up(BTN_A);

  //Botão B
  gpio_init(BTN_B);
  gpio_set_dir(BTN_B, GPIO_IN);
  gpio_pull_up(BTN_B);
}

// Função de interrupção com debouncing do botão
void gpio_irq_handler(uint gpio, uint32_t events){
  // Obtém o tempo atual em microssegundos
  uint32_t current_time = to_us_since_boot(get_absolute_time());

  // Verifica se passou tempo suficiente desde o último evento
  if (current_time - last_time > 300000) { // 300 ms de debouncing
    last_time = current_time; // Atualiza o tempo do último evento

    if (gpio == BTN_A) {
      acao_botao_A = true;
      acao_botao_B = false;

    } else if (gpio == BTN_B) {
      acao_botao_B = true; 
      acao_botao_A = false;

      //controle de animações ao ser apertado o botão B
      if (num_animacao <= 5) num_animacao++;
      else num_animacao = 0;
    }
  }
}

void gpio_set_irq_interrupt_btn(){
  // Configuração da interrupção com callback para botão A
  gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
  // Configuração da interrupção com callback para botão B
  gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

#endif