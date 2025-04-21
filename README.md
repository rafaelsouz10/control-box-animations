# BitBox Animado: Controle Interativo e Animações

---

## Descrição do Projeto

Projeto tem como objetivo desenvolver um sistema na placa BitDogLab para a segunda fase do **EmbarcaTech**, permitindo ao usuário controlar a movimentação de um quadrado 8x8 no display OLED por meio de um joystick, com feedback sonoro e visual, além de alternar entre diferentes animações exibidas em uma matriz de LEDs.

![image](https://github.com/user-attachments/assets/92f493d1-2457-4427-b0d5-d5cf52335343)

---

## Requisitos

- **Microcontrolador**: Raspberry Pi Pico ou Raspberry Pi Pico W (opcional)
- **Placa de Desenvolvimento:** BitDogLab (opcional).
- **Conta Criada no Wokwi Simulator**: [Wokwi](https://wokwi.com/).
- **Editor de Código**: Visual Studio Code (VS Code).
- **SDK do Raspberry Pi Pico** configurado no sistema.
- Ferramentas de build: **CMake** e **Ninja**.

---

## Instruções de Uso

### 1. Clone o Repositório

Clone o repositório para o seu computador:
```bash
git clone https://github.com/rafaelsouz10/control-box-animations.git
cd control-box-animations
code .
```
---

### 2. Instale as Dependências

Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no VS Code. As extensões recomendadas são:

- **C/C++** (Microsoft).
- **CMake Tools**.
- **Wokwi Simulator**.
- **Raspberry Pi Pico**.

---

### 3. Configure o VS Code

Abra o projeto no Visual Studio Code e siga as etapas abaixo:

1. Certifique-se de que as extensões mencionadas anteriormente estão instaladas.
2. No terminal do VS Code, compile o código clicando em "Compile Project" na interface da extensão do Raspberry Pi Pico.
3. O processo gerará o arquivo `.uf2` necessário para a execução no hardware real.

---

### 4. Teste no Simulador Wokwi Integrado ao VS Code

Após ter configurado o VS Code conforme descrito no item 3, siga os passos abaixo para simular o projeto:

1. Abra o arquivo `diagram.json` no Visual Studio Code.
2. Clique no botão "Play" disponível na interface.
3. Divirta-se interagindo com os componentes disponíveis no simulador integrado!

---

### 5. Teste no Hardware Real

#### Utilizando a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W:

1. Conecte a placa ao computador no modo BOTSEEL:
   - Pressione o botão **BOOTSEL** (localizado na parte de trás da placa de desenvolvimento) e, em seguida, o botão **RESET** (localizado na frente da placa).
   - Após alguns segundos, solte o botão **RESET** e, logo depois, solte o botão **BOOTSEL**.
   - A placa entrará no modo de programação.

2. Compile o projeto no VS Code utilizando a extensão do [Raspberry Pi Pico W](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):
   - Clique em **Compile Project**.

3. Execute o projeto clicando em **Run Project USB**, localizado abaixo do botão **Compile Project**.

---

### 🔌 6. Conexões e Esquemático
Abaixo está o mapeamento de conexões entre os componentes e a Raspberry Pi Pico W:

| **Componentes**        | **Pino Conectado (GPIO)** |
|------------------------|---------------------------|
| Display SSD1306 (SDA)  | GPIO 14                   |
| Display SSD1306 (SCL)  | GPIO 15                   |
| Joystick VRX           | GPIO 27                   |
| Joystick VRY           | GPIO 26                   |
| Joystick SW            | GPIO 22                   |
| Botão A                | GPIO 5                    |
| Botão B                | GPIO 6                    |
| LED RGB Vermelho       | GPIO 13                   |
| LED RGB Azul           | GPIO 12                   |
| LED RGB Verde          | GPIO 11                   |
| Buzzer                 | GPIO 21                   |

#### 🛠️ Hardware Utilizado
- **Microcontrolador:** Raspberry Pi Pico W
- **Display:** OLED SSD1306 (I2C)
- **Joystick Analógico** (VRX e VRY)
- **Botões A e B**
- **Led RGB**
- **Buzzer**

---

### 7. Funcionamento do Sistema

#### 📌 Funcionalidades

**O sistema possui dois modos principais:**

**1. Modo de Controle do Quadrado 8x8 (ativado ao pressionar o botão A)** 
Neste modo, o quadrado é movimentado pelo joystick no display OLED. O botão do joystick alterna entre quatro estágios de borda que delimitam a área de movimentação: sem borda, borda total, borda média e borda pequena. Sempre que o quadrado colide com uma borda, o buzzer é ativado com som contínuo e o Led RGB vermelho é acionado a cada colisão.

**2. Modo de Animações na Matriz de LEDs (ativado com o botão B)** 
Ao pressionar o botão B, o sistema entra em modo de animações. Cada clique alterna entre os seguintes estados: 

**Animação Cobrinha** – o display mostra “ANIMACAO COBRINHA” e liga o Led RGB Azul;
**Suspensão da animação** - display mostra “ANIMACAO SUSPENSA” e liga o Led RGB Verde;
**Animação Relógio** – display mostra “ANIMACAO RELOGIO” e liga o Led RGB Azul;
**Suspensão novamente**;
**Animação Cerveja** – display mostra “ANIMACAO CERVEJA” e liga o Led RGB Azul;
**Suspensão novamente**.

---

### 8. Vídeo Demonstrativo

Click [AQUI](https://drive.google.com/file/d/1NZdzw5Du4WLmz_Zdit2E3Bd0f86hzapV/view?usp=sharing) para acessar o link do Vídeo Ensaio
