🌊 HydroGuard sua barreira inteligente contra enchentes 🌊

# 💧 Sistema de Monitoramento Preventivo contra Enchentes com ESP32 e IoT

## 📌 Problema Identificado

Enchentes causam grandes prejuízos em áreas urbanas, afetando a mobilidade, a segurança e a saúde pública. A falta de monitoramento em tempo real dificulta a resposta rápida das autoridades e da população.

## 🎯 Objetivo da Solução

Criar uma solução IoT com Edge Computing para detectar precocemente situações de risco de enchente, utilizando sensores de **Nível de água**, **Temperatura** e **Umidade**, com atuação automatizada (alertas e abertura de comportas simulada com servomotores).

## 🧠 Tecnologias Utilizadas

- **ESP32 (Simulador Wokwi)**
- **Sensor Ultrassônico** (nível da água)
- **Sensor DHT22** (temperatura e umidade)
- **Servomotores** (simulação de abertura de comportas)
- **LEDs** (alertas visuais)
- **Broker MQTT (test.mosquitto.org)**
- **Node-RED** (dashboard e automações)

## 🛠 Arquitetura da Solução

### 🔌 Camada IoT (Edge)
- ESP32 coleta dados dos sensores localmente e publica via MQTT nos tópicos:
  - `iot/agua/distancia`
  - `iot/agua/temperatura`
  - `iot/agua/umidade`
  - `iot/agua/alerta`

### 🌐 Camada Back-End
- Broker MQTT: `test.mosquitto.org` (Mosquitto)

### 📊 Camada de Aplicação
- Node-RED com dashboard `/ui` para visualização em tempo real:
  - Gauge de nível da água
  - Temperatura ambiente
  - Umidade relativa
  - Alerta automático e simulação de controle de comporta

## 🚀 Funcionamento

1. Sensores coletam dados em tempo real.
2. ESP32 publica dados no broker MQTT.
3. Node-RED consome os dados e atualiza o dashboard.
4. Se o nível da água for crítico, o sistema:
   - Gira os servos (abrindo comportas)
   - Acende o LED vermelho
   - Publica alerta via MQTT

## 🔗 Link do Projeto no Wokwi

[🔗 Acesse no Wokwi](https://wokwi.com/projects/SEU_LINK_AQUI](https://wokwi.com/projects/432161784302052353))

## ▶️ Como Executar

1. Acesse o projeto no Wokwi.
2. Execute o Node-RED localmente com `npx node-red`.
3. Importe o fluxo JSON no editor (via Menu > Import > Clipboard).
4. Acesse `http://localhost:1880/ui` para visualizar o dashboard.
5. Verifique dados ao vivo e a atuação automática do sistema.
