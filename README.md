# RC Car Project

Este proyecto implementa un coche RC (Radio Control) utilizando ESP-NOW; es un protocolo de comunicación peer-to-peer desarrollado por Espressif que permite la comunicación directa entre dispositivos ESP32 sin necesidad de router.

- **RC_Transmitter**: Unidad transmisora con joysticks para control
- **RC_Receiver**: Unidad receptora que controla el ESC y servo con PWM con los datos recibidos

## Estructura del Proyecto

```
.
├── RC_Receiver/          # Código del receptor
├── RC_Transmitter/       # Código del transmisor  
├── MAC_address/         # Utilidad para direcciones MAC
└── Joystick_Calibration/ # Utilidad de calibración
```

## Requisitos

- Librerías:
  - ESP32Servo (Receptor)
  - WiFi (Receptor y Transmisor)

## Hardware | Componentes necesarios

- 1x ESP32_DevKitc_V4 (Receptor)
- 1x ESP32 DevKit V1 (Transmisor)
- Servomotor MG90S (Coche)
- ESC (Electronic Speed Controller) Sin freno 40A
- 2x Joystick HW-504 (Control)

## Conexiones
