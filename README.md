# LPC2378 USB Mass Storage Audio Device
This project uses a LPC2378 to mount an SD Card as a USB Mass Storage to a host system.  It also behaves as a USB Audio Device allowing playback via the speakers connected to the ADC on the Keil MCB2300 LPC2378 Development Board. Developed as part of Embedded Systems Design (EEE G512) course in BITS Pilani Goa Campus. 

The project was developed using Keil uvision IDE. The project heavily relies on the RL-ARM libraries. In addition, it employs the RTX-RTOS in order to handle both the Audio Streaming and Mass Storage actions. 

Developed by
- Devam Ajit Awasare (2016A3PS0657G)
- Moosa Mahsoom (2016A8PS0310G)
- Pragnesh Patel Rasiklal (2016A3PS0183G)
- Priyal Chittrapathi (2016A8PS0378G)

The method described below is for ULINK USB-JTAG Adapter. 

## Flashing the Code
1. Download the repository and extract it to a location of your choice. 
2. Open Keil uvision5 IDE. Ensure you have the Profesional version of the IDE in order to have access to the RL-ARM libraries. 
3. Open the project via the menu **Project - Open Project** and select the file **Memory.UVPROJ** from the folder. 
    -The project has been pre-configured for the MCB2300 LPC2378 Board and ULINK JTAG Adapter. 
4. Compile and link the application via the toolbar button or using the menu **Project - Build Target.** µVision starts compiling and linking the source files, and displays progress messages in the window **Build Output.**
5. Use the **Download to Flash** toolbar button (*LOAD is written on the icon*). This will download the program onto the board. 
6. Reset the board. 
7. **Connect** the board to a PC via the **Micro-USB port**.
8. The SD Card should mount to the system and the device should also be recognised as an audio device. 
    - We recommend formatting the SD card to partitions less than 1 GB as higher partition negatively impact the performance. 
9. For debugging purposes, utilise **Debug - Start/Stop Debug Session**. 
