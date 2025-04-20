#include <stdio.h>
#include "pico/stdlib.h"
#include <inc/config_btn.h>
#include <inc/display_ssd1306.h>
#include <inc/joystick.h>
#include <inc/controle_animacoes.h>

int main() {
    stdio_init_all();
    adc_init();        // Inicializa o ADC (conversor analógico-digital)
    display_init();   // Inicializa as configurações do display OLED SSD1306
    npInit(LED_PIN); // Inicializa matriz de LEDs NeoPixel.
    joystick_init();// Inicializa os pinos do joystick
    buzzer_init(); // Inicializa o buzzer
    leds_init();  // Inicializa os leds rgb

    setup_gpio_BTN();// Configuração inicial dos botões A e B
    gpio_set_irq_interrupt_btn();// Configuração da interrupção com callback para botões A e B

    while (true) {

        //se o botão A for apertado, mostrará as funcionalides do box_8x8 
        if (acao_botao_A) {
            //inicia a ação do botão A com o display limpo, animações e leds desligados (assim que voltar de uma ação do botão B)
            limpa_display();
            off_animation();
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_BLUE, 0);

            //Função para leitura do joystick e alternância das bordas com o botão do joystick
            controle_joystick_box();
        
            //Função responsável pela exibição da caixinha 8x8 no display
            print_display();

        } else if (acao_botao_B) {
            limpa_display();

            //função de controle de animações
            animacoes(num_animacao, 200);
        }
        sleep_ms(100);
    }
    return 0;
}
