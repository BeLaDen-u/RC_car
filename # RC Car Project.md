# RC Car Project

Este proyecto implementa un coche RC (Radio Control) utilizando ESP32. Consiste en dos componentes principales:

- **RC_Transmitter**: Unidad transmisora con joysticks para control
- **RC_Receiver**: Unidad receptora que controla los motores y servos

## Estructura del Proyecto

```
.
├── RC_Receiver/          # Código del receptor
├── RC_Transmitter/       # Código del transmisor  
├── MAC_address/         # Utilidad para direcciones MAC
└── Joystick_Calibration/ # Utilidad de calibración
```

## Requisitos

- ESP32 DevKit v4 o compatible
- PlatformIO
- Visual Studio Code
- Librerías:
  - ESP32Servo
  - WiFi