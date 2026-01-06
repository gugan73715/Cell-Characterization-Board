# Cell Characterization Board
This project is a 10-channel sequential lithium-ion cell (18650) characterization instrument designed to measure cell voltage, discharge current, internal resistance, and capacity under a controlled constant-current load of up to 5 A. The Cell data would be displayed to a LCD and stored to a SD card which can be used to plot discharge curves using Excel/Matlab/Python. Protection features include Reverse Polarity Protection for each channel, Low voltage cut-off and hardware controlled sequential switching circuit with hardware interlock to create mutually exclusive channels.

## Key design goals
- Programable constant-current discharge
- Accurate, ratiometric voltage and current measurement
- Fault-tolerant handling of reverse polarity and missing cells
- Sequential testing to minimize BOM cost and thermal complexity
- Hardware based protection features for relaibility and 
- Reduce manufacturing and assembly cost as much as possbile due to budget constraint
- Clear documentation of design intent and constraints
  
# PCB Design:
## Latest 3D Render:
![Cell Characterization Board V1 2 3D Render - Top](https://github.com/user-attachments/assets/29e0ffa8-d2e8-4c36-aab5-d34a47237cab)
<img width="4265" height="4019" alt="Cell Characterization Board V1 2 3D Render - Bottom" src="https://github.com/user-attachments/assets/4b63f3ed-e3a5-4549-a06e-88446abbb75f" />
## Overview:
The system is implemented on a custom 4-layer mixed-signal PCB (SIG / GND / PWR / SIG) optimized for high-current power handling, precision analog measurement and noise handling.

GND and PWR plane are continous and unbroken providing low-impedance return paths and a stable reference plane.
### High-Current Routing
- All >2 A paths use wide copper pours with stitching vias if possible to minimise voltage drop
- All high current paths are kept as away as possible from sensitive analog traces
- Relay coil and Flyback traces are kept as short as possible and fanned out to prevent noise from adjacent traces

### Analog Integrity
- All analog traces are on top layer with a GND plane below and no via jumping
- Analog traces are kept as short as possible, achieved by proper Analog/Digital/Power zones of component placement
- Important analog signals are buffered and have a decoulping capacitor close to it
- kelving sense is used for current and voltage measurement 
  
### Noise and Protection
- Relay drive and switching currents are physically separated from the analog front-end
- External flyback diodes placed adjacent to each relay
- Decoupling capacitors placed close to each IC supply pin
- Reverse polarity protection for each channel using P-channel mosfets
- V_Cell traces are connected straight to cell holder for kelvin sense and current limiting resistor on each trace to protect the MUX in case of reverse polarity.
- NTC on Load Mosfet's heatsink for over temprature protection as redundancy
- 30 ms Soft start for BUCK IC to prevent overshoot and inrush current
  
# Hardware
![Cell characterization board V1 2 - Top Level_page-0001](https://github.com/user-attachments/assets/958f1ddc-cff1-46bc-9eeb-34644356cadd)
## System Architecture Summary (Click for on subsection header for schematic sheet)
<details>
<summary><h3>Buck and LDO</h3></summary>
[![Buck and LDO Schematic](https://github.com/user-attachments/assets/433c3e82-389d-4984-9a22-51cbf6804a1b)](https://github.com/user-attachments/assets/433c3e82-389d-4984-9a22-51cbf6804a1b)
</details>

- input DC Jack / XT60: 8–40 V
- input USB-C: 5V 3A (Non-PD)
- 5 V logic rail via AP64502QSP-13 based synchronous buck converter
- 3.3 V low-noise LDO for MicroSD and SPI

<details>
<summary><h3>Constant Current Sink</h3></summary>
[![Constant Current Sink](https://github.com/user-attachments/assets/570f1b11-27f7-42b6-8a97-f1864ae25d66)](https://github.com/user-attachments/assets/570f1b11-27f7-42b6-8a97-f1864ae25d66)
</details>

- IRLZ44N Logic level mosfet and TLV9162 control op-amp
- Low side 50mohm 3W shunt
- DAC60501ZDGSR 12-bit DAC for precise control of dishcharge current and controlled via I2C
- Internal 2.5 V precision reference of DAC is shared by ADC as well
- Amplified I_sense signal (0 - 2.5V) using MCP6001 for better resolution
- Theoritical mosfet temprature with heat sink(θ_normal = 2.6 C/W) at max case is 115.86 C
- Load MOSFET temprature monitoring via NTC
- Maximum discharge current: 5 A

<details>

<summary><h3>MCU</h3></summary>
[![MCU](https://github.com/user-attachments/assets/d0f35247-9f11-4299-ac2f-d843d51ea3c3)](https://github.com/user-attachments/assets/d0f35247-9f11-4299-ac2f-d843d51ea3c3)

</details>

- Compatable with 3.3v STM32 Nucleo boards with nano connectivity and Arduiuno nano
- External I2C header for debugging and future expansion modules
- External UART header for telemetry

### Cell Holders
- DIY 3D printed SMD 18650 cell holders (similar to Keystone 1043) with 0.2mm nickel strips as cell contacts to save BOM cost
- Reverse polarity protection for each channel using P-channel mosfets
- Cell voltage sense traces are connected straight to cell holder pads for kelvin sense

### Sequential Cell Switching
- Control Logic: MCU -> I2C Expander -> Line Decoder (For mutually exclusive channels) -> Relay Driver -> Relay -> Cell Holder
- Relay-based physical isolation of cells driven by darlington transistor array on low side
- PCF8575PWR I2C expander for I/O expansion
- CD4514BM96 Line decoder to prevent connecting more than one channel at the same time and a active high inhibit pin controlled by I2C expander
- External pull ups on all I2C lines and external flyback diodes on all relays

### Cell Monitoring
- CD74HC4067SM96 16:1 analog MUX for cell volatage sampling
- MUX out is converted to a signal of 0 to 2.5V using a voltage divider and then buffered
- Current limiting resistor(limits to 2.1mA) on each channel to protect the MUX in case of reverse polarity (internal ESD diode forward biases)



Darlington relay driver arrays

External flyback diodes on all relay coils

Cell Voltage Measurement

Direct cell-pad Kelvin sensing

16:1 analog multiplexer

Series input resistors for current-limited fault handling

Current Measurement

Low-side shunt resistor

Kelvin-style sense routing

Op-amp gain stage scaled to ADC range

Measured Parameters

Cell voltage

Discharge current

Internal resistance

Capacity (mAh / Wh)

Communication Interfaces

I²C: DAC, I/O expander

SPI: MicroSD card, debug header

UART: PC telemetry / debug

User Interface

1602 character LCD (direct MCU connection)

Real-time status and measurement display



