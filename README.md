# canGateway_firmware

#### It is firmware for LPC1768.
MC works as CAN gateway, receive some data to the CAN1 and transmit the same date without any changing.


MCU: LPC17xx

Core: ARM CORTEX-M3

Debug communicate via: 
- UART3: select P0.25 as TXD3 (7), P0.26 as RXD3 (6) - 115200 bps

Use two CAN peripherals: 
- CAN1: select P0.0 as RD1 (46), P0.1 as TD1 (47) is used as receiver - 125000 bps
- CAN2: select P0.4 as RD2 (81), P0.5 as TD2 (80) is used as transmitter - 125000 bps

__Note:__

Acceptance filter configured as Bypass mode.
	
__TODO:__ 

To configure Acceptance filter as FullCAN to implement real GATEWAY.
