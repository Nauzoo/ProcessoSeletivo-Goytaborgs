<div>
  
  # ProcessoSeletivo-Goytaborgs <img align="left" alt="Java" width="80px" style="padding-right:10px;" src="assets/logo.png" />
  
</div>

<br>

`Este projeto faz parte do processo seletivo da equipe Goytaborgs do IFF Campos centro.`

## Especificações do robo:
- Microcontrolador: `ESP32 DevKit`


## Dependencias:
- ESP32 core para arduino: [EspCore](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json)
- Lib Dabble [DabbleLib](https://github.com/STEMpedia/DabbleESP32)

<br>

## Instalação das dependências:
- Ambas as dependeências podem ser baixadas pelo arduino IDE no gerenciador de nucleos e no gerenciador de bibliotecas respectivamente
- Para arduino CLI:
  - Inincialize um arquivo de configuraçao: `$ arduino-cli config init`
  - Atualize o cache de plataformas: `$ arduino-cli core update-index`
  - Instale o nucleo: `$ arduino-cli board install esp32`
  - Para nucleos de terceiros, adicione o URL da "ESP32 core para arduino" em seu `arduino-cli.yaml`
  ![exemplo](assets/config.png) 
