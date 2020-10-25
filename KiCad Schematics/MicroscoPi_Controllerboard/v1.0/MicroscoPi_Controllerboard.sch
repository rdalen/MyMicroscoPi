EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "MicroscoPi - Controllerboard"
Date "2020-08-09"
Rev "V1.0"
Comp "TechDen"
Comment1 "Designed by Roland"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L tinkerforge:JOYSTICK_BUTTON U1
U 1 1 5F2E0D2D
P 5050 3425
F 0 "U1" V 5600 3925 60  0000 R CNN
F 1 "JOYSTICK_BUTTON" V 5600 3700 60  0000 R CNN
F 2 "tinkerforge:Joystick_w_Button" H 5050 3425 60  0001 C CNN
F 3 "https://www.evernote.com/l/AD6xE7tqk31F_41CDl8qYf35tWgwOpIksp4/" H 5050 3425 60  0001 C CNN
	1    5050 3425
	0    -1   -1   0   
$EndComp
$Comp
L tinkerforge:JOYSTICK_BUTTON U2
U 1 1 5F2E48FA
P 6275 3425
F 0 "U2" V 6825 3925 60  0000 R CNN
F 1 "JOYSTICK_BUTTON" V 6825 3700 60  0000 R CNN
F 2 "tinkerforge:Joystick_w_Button" H 6275 3425 60  0001 C CNN
F 3 "https://www.evernote.com/l/AD6xE7tqk31F_41CDl8qYf35tWgwOpIksp4/" H 6275 3425 60  0001 C CNN
	1    6275 3425
	0    -1   -1   0   
$EndComp
$Comp
L tinkerforge:JOYSTICK_BUTTON U3
U 1 1 5F2E967E
P 7500 3425
F 0 "U3" V 8050 3925 60  0000 R CNN
F 1 "JOYSTICK_BUTTON" V 8050 3700 60  0000 R CNN
F 2 "tinkerforge:Joystick_w_Button" H 7500 3425 60  0001 C CNN
F 3 "https://www.evernote.com/l/AD6xE7tqk31F_41CDl8qYf35tWgwOpIksp4/" H 7500 3425 60  0001 C CNN
	1    7500 3425
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F2EF893
P 4475 4375
F 0 "#PWR0101" H 4475 4125 50  0001 C CNN
F 1 "GND" H 4500 4175 50  0000 C CNN
F 2 "" H 4475 4375 50  0001 C CNN
F 3 "" H 4475 4375 50  0001 C CNN
	1    4475 4375
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5F2F21FE
P 4475 4225
F 0 "#PWR0103" H 4475 4075 50  0001 C CNN
F 1 "+5V" V 4525 4375 50  0000 L CNN
F 2 "" H 4475 4225 50  0001 C CNN
F 3 "" H 4475 4225 50  0001 C CNN
	1    4475 4225
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7450 4075 7450 4225
Wire Wire Line
	7450 4225 7100 4225
Wire Wire Line
	7650 4075 7650 4375
Wire Wire Line
	7650 4375 7300 4375
Wire Wire Line
	4650 4075 4650 4225
Connection ~ 4650 4225
Wire Wire Line
	4650 4225 4475 4225
Wire Wire Line
	5000 4075 5000 4225
Connection ~ 5000 4225
Wire Wire Line
	5000 4225 4650 4225
Wire Wire Line
	4850 4075 4850 4375
Connection ~ 4850 4375
Wire Wire Line
	4850 4375 4475 4375
Wire Wire Line
	5200 4075 5200 4375
Connection ~ 5200 4375
Wire Wire Line
	5200 4375 4850 4375
Wire Wire Line
	5450 4075 5450 4375
Connection ~ 5450 4375
Wire Wire Line
	5450 4375 5200 4375
Wire Wire Line
	5875 4075 5875 4225
Connection ~ 5875 4225
Wire Wire Line
	5875 4225 5000 4225
Wire Wire Line
	6075 4075 6075 4375
Connection ~ 6075 4375
Wire Wire Line
	6075 4375 5450 4375
Wire Wire Line
	6225 4075 6225 4225
Connection ~ 6225 4225
Wire Wire Line
	6225 4225 5875 4225
Wire Wire Line
	6425 4075 6425 4375
Connection ~ 6425 4375
Wire Wire Line
	6425 4375 6075 4375
Wire Wire Line
	6675 4075 6675 4375
Connection ~ 6675 4375
Wire Wire Line
	6675 4375 6425 4375
Wire Wire Line
	7100 4075 7100 4225
Connection ~ 7100 4225
Wire Wire Line
	7100 4225 6225 4225
Wire Wire Line
	7300 4075 7300 4375
Connection ~ 7300 4375
Wire Wire Line
	7300 4375 6675 4375
Wire Wire Line
	7900 4075 7900 4375
Wire Wire Line
	7900 4375 7650 4375
Connection ~ 7650 4375
Text Label 4750 4525 0    50   ~ 0
X
Text Label 5100 4525 0    50   ~ 0
Y
Text Label 5975 4525 0    50   ~ 0
Z
Text Label 6325 4525 0    50   ~ 0
C
Text Label 7200 4525 0    50   ~ 0
T
Text Label 7550 4525 0    50   ~ 0
R
Text Label 4750 4700 1    50   ~ 0
GPIOA0
Text Label 5100 4700 1    50   ~ 0
GPIOA1
Text Label 5975 4700 1    50   ~ 0
GPIOA2
Text Label 6325 4700 1    50   ~ 0
GPIOA3
Text Label 7200 4700 1    50   ~ 0
GPIOA6
Text Label 7550 4700 1    50   ~ 0
GPIOA7
Wire Wire Line
	7550 4075 7550 4700
Wire Wire Line
	7200 4075 7200 4700
Wire Wire Line
	6325 4075 6325 4700
Wire Wire Line
	5975 4075 5975 4700
Wire Wire Line
	5100 4075 5100 4700
Wire Wire Line
	4750 4075 4750 4700
Text Label 5350 4700 1    50   ~ 0
GPIO02
Text Label 6575 4700 1    50   ~ 0
GPIO03
Text Label 7800 4700 1    50   ~ 0
GPIO04
Wire Wire Line
	7800 4075 7800 4700
Wire Wire Line
	6575 4075 6575 4700
Wire Wire Line
	5350 4075 5350 4700
Text Label 5350 4525 0    50   ~ 0
BUTTON1
Text Label 6575 4525 0    50   ~ 0
BUTTON2
Text Label 7800 4525 0    50   ~ 0
BUTTON3
Text Label 2900 4100 0    50   ~ 0
GPIOA0
Text Label 2900 4000 0    50   ~ 0
GPIOA1
Text Label 2900 3800 0    50   ~ 0
GPIOA3
Text Label 2900 3900 0    50   ~ 0
GPIOA2
Text Label 2900 3500 0    50   ~ 0
GPIOA7
Text Label 2900 3400 0    50   ~ 0
GPIOA6
Text Label 1600 3950 2    50   ~ 0
GPIO02
Text Label 1600 4050 2    50   ~ 0
GPIO03
Text Label 1600 4150 2    50   ~ 0
GPIO04
NoConn ~ 1600 3800
$Comp
L power:GND #PWR0104
U 1 1 5F309A08
P 2150 5050
F 0 "#PWR0104" H 2150 4800 50  0001 C CNN
F 1 "GND" H 2150 4900 50  0000 C CNN
F 2 "" H 2150 5050 50  0001 C CNN
F 3 "" H 2150 5050 50  0001 C CNN
	1    2150 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0105
U 1 1 5F309C52
P 2350 2500
F 0 "#PWR0105" H 2350 2350 50  0001 C CNN
F 1 "VCC" H 2350 2650 50  0000 C CNN
F 2 "" H 2350 2500 50  0001 C CNN
F 3 "Vin" V 2350 2775 50  0000 C CNN
	1    2350 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder_Switch SW1
U 1 1 5F30CA77
P 8425 3500
F 0 "SW1" V 8850 3775 50  0000 R CNN
F 1 "Rotary_Encoder_Switch" V 8775 3775 50  0000 R CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 8275 3660 50  0001 C CNN
F 3 "https://www.evernote.com/l/AD6MthjFr_VGQb9QrLRkJV6A4uxv8JMFLmg/" H 8425 3760 50  0001 C CNN
	1    8425 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7900 4375 8125 4375
Wire Wire Line
	8425 4375 8425 3800
Connection ~ 7900 4375
Wire Wire Line
	8325 3200 8125 3200
Wire Wire Line
	8125 3200 8125 4375
Connection ~ 8125 4375
Wire Wire Line
	8125 4375 8425 4375
Wire Wire Line
	8325 3800 8325 4700
Wire Wire Line
	8525 3800 8525 4700
Wire Wire Line
	8525 3200 8725 3200
Wire Wire Line
	8725 3200 8725 4700
Text Label 8325 4700 1    50   ~ 0
GPIO09
Text Label 8525 4700 1    50   ~ 0
GPIO08
Text Label 8725 4700 1    50   ~ 0
GPIO07
Text Label 8325 4225 1    50   ~ 0
CLK
Text Label 8525 4225 1    50   ~ 0
DT
Text Label 8725 4525 0    50   ~ 0
BUTTON4
Text Label 1600 4450 2    50   ~ 0
GPIO07
Text Label 1600 4550 2    50   ~ 0
GPIO08
Text Label 1600 4650 2    50   ~ 0
GPIO09
$Comp
L Display_Character:Display_I2C_OLED U4
U 1 1 5F2F3DA1
P 10075 3450
F 0 "U4" H 9525 3700 50  0000 C CNN
F 1 "Display_I2C_OLED" H 10125 3475 50  0000 C CNN
F 2 "Lib-Footprint:SSD1306_OLED-0.91-128x32" H 10025 3150 50  0001 C CNN
F 3 "https://www.evernote.com/l/AD62jUmcMJBGZpAa-3Ric2js8dKCUVTVpok/" H 10075 3375 50  0001 C CNN
F 4 "128x32" H 10075 3375 50  0000 C CNN "Field4"
	1    10075 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F2FF1DF
P 9375 3600
F 0 "#PWR02" H 9375 3350 50  0001 C CNN
F 1 "GND" H 9375 3425 50  0000 C CNN
F 2 "" H 9375 3600 50  0001 C CNN
F 3 "" H 9375 3600 50  0001 C CNN
	1    9375 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5F2FF84D
P 9375 3500
F 0 "#PWR01" H 9375 3350 50  0001 C CNN
F 1 "+5V" V 9400 3650 50  0000 L CNN
F 2 "" H 9375 3500 50  0001 C CNN
F 3 "" H 9375 3500 50  0001 C CNN
	1    9375 3500
	0    -1   -1   0   
$EndComp
Text Label 2900 3050 0    50   ~ 0
SDA
Text Label 2900 3150 0    50   ~ 0
SCL
Text Label 9075 3300 0    50   ~ 0
SDA
Text Label 9075 3400 0    50   ~ 0
SCL
Wire Wire Line
	9375 3300 9075 3300
Wire Wire Line
	9375 3400 9075 3400
NoConn ~ 1600 4250
NoConn ~ 1600 4350
NoConn ~ 2900 4200
NoConn ~ 2900 4300
NoConn ~ 2900 4400
NoConn ~ 2900 4500
$Comp
L Connector:USB_B_Micro J3
U 1 1 5F33247E
P 1125 950
F 0 "J3" H 1000 1325 50  0000 C CNN
F 1 "Power in" H 725 950 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 1275 900 50  0001 C CNN
F 3 "https://www.evernote.com/shard/s62/sh/747e80cf-da2d-4e95-b6d8-e3c64d316c75/671090d3e83537ea649cd51a3a3a36f9" H 1275 900 50  0001 C CNN
	1    1125 950 
	1    0    0    -1  
$EndComp
Text Label 1425 1050 0    50   ~ 0
RxD_USB
Text Label 1425 950  0    50   ~ 0
TxD_USB
$Comp
L power:GND #PWR03
U 1 1 5F336649
P 1125 1650
F 0 "#PWR03" H 1125 1400 50  0001 C CNN
F 1 "GND" H 1125 1500 50  0000 C CNN
F 2 "" H 1125 1650 50  0001 C CNN
F 3 "" H 1125 1650 50  0001 C CNN
	1    1125 1650
	1    0    0    -1  
$EndComp
NoConn ~ 1425 1150
Text Label 1600 3600 2    50   ~ 0
TxD
Text Label 1600 3700 2    50   ~ 0
RxD
$Comp
L Device:C C2
U 1 1 5F36478D
P 1925 900
F 0 "C2" H 1775 975 50  0000 L CNN
F 1 "100nF" H 2025 900 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P2.50mm_P5.00mm" H 1963 750 50  0001 C CNN
F 3 "~" H 1925 900 50  0001 C CNN
	1    1925 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F366E7A
P 1925 1050
F 0 "#PWR06" H 1925 800 50  0001 C CNN
F 1 "GND" H 1925 900 50  0000 C CNN
F 2 "" H 1925 1050 50  0001 C CNN
F 3 "" H 1925 1050 50  0001 C CNN
	1    1925 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5F2FE2FD
P 2350 5050
F 0 "#PWR0106" H 2350 4800 50  0001 C CNN
F 1 "GND" H 2350 4900 50  0000 C CNN
F 2 "" H 2350 5050 50  0001 C CNN
F 3 "" H 2350 5050 50  0001 C CNN
	1    2350 5050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5F2F13C2
P 2150 2500
F 0 "#PWR0102" H 2150 2350 50  0001 C CNN
F 1 "+5V" H 2150 2675 50  0000 C CNN
F 2 "" H 2150 2500 50  0001 C CNN
F 3 "Vout (to JoySticks)" V 2175 3100 50  0000 C CNN
	1    2150 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5F367975
P 1750 2500
F 0 "#PWR05" H 1750 2250 50  0001 C CNN
F 1 "GND" H 1750 2350 50  0000 C CNN
F 2 "" H 1750 2500 50  0001 C CNN
F 3 "" H 1750 2500 50  0001 C CNN
	1    1750 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5F364EBC
P 1900 2500
F 0 "C1" V 1825 2350 50  0000 L CNN
F 1 "100nF" V 2025 2425 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P2.50mm_P5.00mm" H 1938 2350 50  0001 C CNN
F 3 "~" H 1900 2500 50  0001 C CNN
	1    1900 2500
	0    1    1    0   
$EndComp
NoConn ~ 2900 3650
Wire Wire Line
	2050 2500 2150 2500
$Comp
L power:VCC #PWR04
U 1 1 5F335827
P 1925 750
F 0 "#PWR04" H 1925 600 50  0001 C CNN
F 1 "VCC" V 1925 875 50  0000 L CNN
F 2 "" H 1925 750 50  0001 C CNN
F 3 "Vin" V 1875 625 50  0000 C CNN
	1    1925 750 
	0    1    1    0   
$EndComp
$Comp
L Logo:Logo-TechDen L1
U 1 1 5F33F572
P 800 7725
F 0 "L1" H 525 7825 50  0000 C CNN
F 1 "Logo-TechDen" H 800 7725 50  0000 C CNN
F 2 "Logo:TechDen Logo - inverted" H 800 7725 50  0001 C CNN
F 3 "" H 800 7725 50  0001 C CNN
	1    800  7725
	1    0    0    -1  
$EndComp
$Comp
L Logo:Logo-RvD L2
U 1 1 5F340929
P 1125 7625
F 0 "L2" H 1150 7625 50  0000 C CNN
F 1 "Logo-RvD" H 1325 7525 50  0000 C CNN
F 2 "Logo:RvD Logo inverted small" H 1325 7525 50  0001 C CNN
F 3 "" H 1325 7525 50  0001 C CNN
	1    1125 7625
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5F34F301
P 3350 3300
F 0 "#PWR07" H 3350 3050 50  0001 C CNN
F 1 "GND" H 3425 3150 50  0000 R CNN
F 2 "" H 3350 3300 50  0001 C CNN
F 3 "" H 3350 3300 50  0001 C CNN
	1    3350 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3300 3350 3300
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 5F3593B8
P 9400 4000
F 0 "J1" H 9450 4000 50  0000 L CNN
F 1 "I2C (for testing purpose)" H 9450 3900 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 9400 4000 50  0001 C CNN
F 3 "~" H 9400 4000 50  0001 C CNN
	1    9400 4000
	1    0    0    -1  
$EndComp
Text Label 9200 3900 2    50   ~ 0
SDA
Text Label 9200 4000 2    50   ~ 0
SCL
$Comp
L power:+5V #PWR08
U 1 1 5F35AB57
P 9200 4100
F 0 "#PWR08" H 9200 3950 50  0001 C CNN
F 1 "+5V" V 9225 4250 50  0000 L CNN
F 2 "" H 9200 4100 50  0001 C CNN
F 3 "" H 9200 4100 50  0001 C CNN
	1    9200 4100
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F35BEEF
P 9200 4200
F 0 "#PWR09" H 9200 3950 50  0001 C CNN
F 1 "GND" H 9200 4025 50  0000 C CNN
F 2 "" H 9200 4200 50  0001 C CNN
F 3 "" H 9200 4200 50  0001 C CNN
	1    9200 4200
	1    0    0    -1  
$EndComp
NoConn ~ 1025 1350
$Comp
L Jumper:SolderJumper_2_Bridged JP2
U 1 1 5F3574A5
P 1575 750
F 0 "JP2" H 1600 900 50  0000 C CNN
F 1 "SolderJumper_2_Bridged" H 1600 875 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged2Bar_Pad1.0x1.5mm" H 1575 750 50  0001 C CNN
F 3 "~" H 1575 750 50  0001 C CNN
	1    1575 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1725 750  1925 750 
Connection ~ 1925 750 
$Comp
L Jumper:SolderJumper_2_Bridged JP1
U 1 1 5F3593D4
P 1125 1500
F 0 "JP1" V 1150 1650 50  0000 C CNN
F 1 "SolderJumper_2_Bridged" H 1150 1625 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged2Bar_Pad1.0x1.5mm" H 1125 1500 50  0001 C CNN
F 3 "~" H 1125 1500 50  0001 C CNN
	1    1125 1500
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP3
U 1 1 5F35B7DE
P 2800 1100
F 0 "JP3" H 2825 1250 50  0000 C CNN
F 1 "SolderJumper_2_Bridged" H 2825 1225 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged2Bar_Pad1.0x1.5mm" H 2800 1100 50  0001 C CNN
F 3 "~" H 2800 1100 50  0001 C CNN
	1    2800 1100
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP4
U 1 1 5F35C6FD
P 2800 1250
F 0 "JP4" H 2800 1125 50  0000 C CNN
F 1 "SolderJumper_2_Bridged" H 2825 1375 50  0001 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged2Bar_Pad1.0x1.5mm" H 2800 1250 50  0001 C CNN
F 3 "~" H 2800 1250 50  0001 C CNN
	1    2800 1250
	1    0    0    -1  
$EndComp
Text Label 2650 1100 2    50   ~ 0
TxD_USB
Text Label 2950 1250 0    50   ~ 0
RxD_USB
Text Label 2650 1250 2    50   ~ 0
RxD
Text Label 2950 1100 0    50   ~ 0
TxD
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F35E412
P 1925 750
F 0 "#FLG0101" H 1925 825 50  0001 C CNN
F 1 "PWR_FLAG" H 1925 975 50  0001 C CNN
F 2 "" H 1925 750 50  0001 C CNN
F 3 "~" H 1925 750 50  0001 C CNN
	1    1925 750 
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5F35FA85
P 1125 1650
F 0 "#FLG0102" H 1125 1725 50  0001 C CNN
F 1 "PWR_FLAG" H 1125 1875 50  0001 C CNN
F 2 "" H 1125 1650 50  0001 C CNN
F 3 "~" H 1125 1650 50  0001 C CNN
	1    1125 1650
	0    1    1    0   
$EndComp
Connection ~ 1125 1650
Connection ~ 2150 2500
$Comp
L MCU_Module:Arduino_Pro_mini A1
U 1 1 5F2E9B46
P 1900 4750
F 0 "A1" H 1900 6750 60  0000 C CNN
F 1 "Arduino_Pro_mini" H 2875 6775 60  0000 C CNN
F 2 "Lib-Footprint:Arduino_pro_mini_v2" H 3400 4550 60  0001 C CNN
F 3 "https://www.evernote.com/l/AD4DRM0B5n5O7J_GKryOX0b1Ho4iJdDhcCU/" H 2950 7100 60  0001 C CNN
	1    1900 4750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
