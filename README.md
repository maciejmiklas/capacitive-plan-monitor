It is a Capacitive Moisture Monitor based on Atmega 328. 


[![Youtube EN)](/img/youtube_en.jpg)](https://youtu.be/DBx7lEarteA)
[![Youtube PL)](/img/youtube_pl.jpg)](https://youtu.be/4kX7fkXBnfU)

<img src="/img/cover.jpg" width="600px"/>
<img src="/img/schematic.png" width="600px"/>

It runs on a single Lii 3100mAh battery for about two months, depending on the brightness of the LEDs and moisture level. Wet soli lights up more LEDs, resulting in higher power consumption. 

The Atmega runs at 2Mhz to extend battery life; all unnecessary functions are also disabled. It drops power consumption from 30mA to less than 10mA with just a few LEDs enabled on low brightness. Running at 10mA would give us a battery life of about two weeks. To prolong it, Atmega goes to a deep sleep every 2 seconds for 4 seconds. With that trade-off, we should run on a single charge for about two months.

The PCB was designed using EasyEDA: https://oshwlab.com/mac.miklas/capacitive-plant-monitor. It's possible to order PCBs directly from them. Soldering is straightforward, Atmega and 16MHz crystal can be sourced from cheap Arduino boards. Actually, Cristal is unnecessary, as the whole project runs on 2MHz anyway, but that requires an altered bool loader.

To build such a device, you can order PCD directly from EasyEDA and solder standard components up to Atmega and 16MHz Crystal. You can move from those chap Arduino boards. 

The top of the board has a 6-pin header, providing a serial port and reset. It can be directly connected to a USB->seial adapter to program the Atmega. The project can be directly imported into AdruinoIDE (*CapacitivePlantMonitorPrj/CapacitivePlantMonitorPrj.ino*)

We have multiple classes on the software side, each carrying different responsibilities. For Example: 
- *MoistureDisplay* controls LEDs displaying moisture level,
- *MoistureDriver* drives the moisture sensor,
- *PowerSaver* is responsible for deep sleep,
- *VCCMonitor* monitors battery level,
- *BrightnessManager* regulates the brightness 
- and so on...
Classes do not communicate directly. They are decoupled through an Event Bus - this is the most essential part of the software. Each Class can generate Events, process Events, and react to those adequately. All Events can be found in *BusEvent.h* -> this location provides the information about all possible data exchange between software components. For example:
- *MoistureDriver* monitors the moisture level. In the case of a change, it emits the event *MOISTURE_LEVEL_CHANGE*. *MoistureDisplay* receives it and turns on/off LEDs
- the Class *Buttons* handle the buttons. When the adjust button is being pressed, Buttons emit *BTN_ADJ_SENSOR*. Now, there are multiple components interested in this event:
	- *PowerSaver* will postpone deep sleep for 10 seconds as it recognizes the user's interaction, 
	- *ProbeDriver* will stop measurements for a few seconds because those consume CPU cycles, and we are running only at 2MHz,
	- *LED* Class will blink the action LED a few times to give a user feedback that a button press has been recognized

The Class *ArdLog* can be used to enable Logger. It has to be done for each component separately. Log messages go through serial port, and the speed is set to 38400 (*Config#AL_SERIAL_SPEED*), but as we are running at 2Mhz, the serial rate on the PC has to be set to 38400/8=4800

Many things are configurable through *Config.h*, few might be interesting:

``` cpp
// dealy in ms for first standby after power on
const static uint32_t PS_STANDBY_INIT_MS =  20L * 1000L;

// dealy in ms for standby after a button has been pressed
const static uint32_t PS_STANDBY_BUTTON_MS = 20L * 1000L;

// standby frequency during normal operation
const static uint32_t PS_STANDBY_DELAY_MS = 4000L;

// sleep time in seconds during standby
const static SleepPeriod PS_SLEEP = SleepPeriod::S8;
```

It might be necessary to adjust moisture sensor readings:
``` cpp
/**
    Voltage level read from the moisture sensor over input A0 depend on the VCC level, which changes with a battery charge.
    Different battery level reflects the amplitude of generated square wave for a sensor. It is hard to write a function
    that appropriately adjusts readings based on changes in the VCC level because it is not linear. For this reason,
    we are using mapping table for different VCC(batery) levels.
*/
// For calibration set MI_MIN_VCC_CHANGE_MV = 1 and ArdLog -> LOG_MD, LOG to true
const static uint16_t MI_LEVEL_MAP[MI_LEVEL_MAP_SIZE][3] = {
  // {VCC, DRY, WET} (mV)
  { 5000, 3970, 2212 },
  { 4600, 3610, 2000 },
  { 4500, 3530, 1943 },
  { 4400, 3460, 1900 },
  { 4300, 3370, 1840 },
  { 4200, 3300, 1790 },
  { 4100, 3180, 1730 },
  { 4000, 3100, 1680 },
  { 3900, 3010, 1630 },
  { 3800, 2930, 1580 },
  { 3700, 2840, 1530 },
  { 3600, 2770, 1470 },
  { 3500, 2670, 1424 },
  { 3400, 2590, 1370 },
  { 3300, 2490, 1320 },
  { 3200, 2420, 1260 },
  { 3100, 2330, 1200 },
  { 3000, 2330, 1160 },
  { 2000, 2330, 1160 }
};
```

 
