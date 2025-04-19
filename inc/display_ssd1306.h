#ifndef DISPLAY_SSD1306_H
#define DISPLAY_SSD1306_H

#include "hardware/i2c.h"
#include "ssd1306/ssd1306.h"
#include "buzzer.h"
// #include "font.h"

#define QUAD_SIZE 8

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

int stage_retangulo = 0;  //controla a exibicao do retangulo 0: Retângulo grande, 1: Retângulo menor, 2: Retângulo ainda menor
int x_pos, y_pos;  //variáveis para os valores do joystick para as coordenadas do display (128x64 pixels)

bool cor = true;    // Define a cor do display (preto/branco)

uint16_t vrx_value;  
uint16_t vry_value;

ssd1306_t ssd;    // Inicializa a estrutura do display

void display_init(){
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); //Inicializa o display
    ssd1306_config(&ssd); //Configura o display
    ssd1306_send_data(&ssd); //Envia os dados para o display

    //O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

void limpa_display(){
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_send_data(&ssd); // Atualiza o display
}

void print_display(){
    ssd1306_fill(&ssd, !cor); // Limpa o display
    
    //valores iniciais da área mapeada para que o quadrado 8x8 permaneça dentro do espaço 128x64
    int x_min = 0, x_max = 120;
    int y_min = 0, y_max = 56;

    //Define limites do retângulo conforme cada estágio
    if (stage_retangulo == 0) { 
        ssd1306_rect(&ssd, 0, 0, 128, 64, !cor, !cor); //Sem retângulo
    } else if (stage_retangulo == 1) {
        ssd1306_rect(&ssd, 0, 0, 128, 64, cor, !cor); //Retângulo grande
    } else if (stage_retangulo == 2) {
        ssd1306_rect(&ssd, 10, 10, 108, 54, cor, !cor); // Retângulo médio
        x_min = 10, x_max = 110;
        y_min = 10, y_max = 56;
    }else if (stage_retangulo == 3) {
        ssd1306_rect(&ssd, 20, 20, 88, 44, cor, !cor); // Retângulo pequeno
        x_min = 20, x_max = 100;
        y_min = 20, y_max = 56;
    }

    // Mapeia os valores do joystick para as coordenadas do display com a limitação do retângulo
    x_pos = (vrx_value * (x_max - x_min)) / 4095 + x_min;   // Ajusta X para o display
    y_pos = y_max - (vry_value * (y_max - y_min)) / 4095;  // Ajusta Y para o display invertendo para corresponder ao display

    // Correção para valor mínimo de y
    if (y_pos == 1) y_pos = 0;
    else if (y_pos == 11) y_pos = 10;
    else if (y_pos == 21) y_pos = 20;

    // Verifica se o quadrado encostou nas bordas
    bool tocou_borda = (
        x_pos <= x_min || x_pos + QUAD_SIZE >= x_max ||
        y_pos <= y_min || y_pos + QUAD_SIZE >= y_max
    );    

    // Toca buzzer enquanto se tocar na borda (exceto no estágio 0)
    if (stage_retangulo != 0 && tocou_borda) {
        gpio_put(BUZZER_PIN, 1);
    } else gpio_put(BUZZER_PIN, 0);  // Silêncio

    // Desenha o quadrado 8x8 na posição calculada
    ssd1306_rect(&ssd, y_pos, x_pos, QUAD_SIZE, QUAD_SIZE, cor, cor);

    ssd1306_send_data(&ssd); // Atualiza o display
}

void display_animacao_suspensa(){
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_draw_string(&ssd, "ANIMACAO", 0, 0);
    ssd1306_draw_string(&ssd, "SUSPENSA", 0, 20);
    ssd1306_send_data(&ssd); // Atualiza o display
}

void display_animacao_cerveja(){
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_draw_string(&ssd, "ANIMACAO", 0, 0);
    ssd1306_draw_string(&ssd, "CERVEJA", 0, 20);
    ssd1306_send_data(&ssd); // Atualiza o display
}

void display_animacao_relogio(){
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_draw_string(&ssd, "ANIMACAO", 0, 0);
    ssd1306_draw_string(&ssd, "RELOGIO", 0, 20);
    ssd1306_send_data(&ssd); // Atualiza o display
}

void display_animacao_cobrinha(){
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_draw_string(&ssd, "ANIMACAO", 0, 0);
    ssd1306_draw_string(&ssd, "COBRINHA", 0, 20);
    ssd1306_send_data(&ssd); // Atualiza o display
}

#endif