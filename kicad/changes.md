# Change log
This file keeps track of changes/updates on schematic and pcb design

__v0.1.42:__
- Fix pullup(MODE) & pulldown(RESET) buttons
- Remove cap for RESET
- Change MODE pin PB4 -> PB2 (INT0), higher level interrupt
- !PCB wiring needs update

__v0.1.41:__
- Add 100nF ceramic capacitors for smoother signal
- !Pullup & pulldown buttons still not fixed
- Add more thermal relief pads on ground holes
- Remove some non-copper 'islands'

__v0.1.32:__
- Added programming pinheaders for attiny85
- Plus silkscreen text for easy reading

__v0.1.31:__
- Added dimensions for 3D printing on User1 layer

__v0.1.3:__
- Fix reset PullUp button

__v0.1.2:__
- Fix bulk capacitor polarity

__v0.1.1:__
- Change mounting hole type to mounting pad and connected it to GND

__v0.1.0:__
- Change footprint of power connector
	(pinHeader 2.54mm -> Molex KK-254 2.54mm)
- Increase size of board 61mm -> 65mm
- Add explicit text for reset & mode buttons 
- Add decoupling electrolytic cap to main power rail
- Add programmable + reset buttons for Attiny85
- Change testpoints footprint

__v0.0.6:__
- Add decoupling capacitors to ICs

__v0.0.5:__
- Add push button to PB4 pin

__v0.0.4:__
- Add image on b.silkscreen
- change routing using plugin

__v0.0.3:__
- Fix text orientation for components-F.silkscreen
- Change testpoint footprints
- Add text-F.silkscreen

__v0.0.2:__
- Fix pin headers footprint 1mm -> 2.54mm

__v0.0.1:__
- initial design

