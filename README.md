# raindetector
Firmware for an arduino that monitors and reports the state of a set of rain detector boards.  Communicates with [raind](https://github.com/warwick-one-metre/raind).

The sensor box contains 6 (generic chinese) rain detector boards connected through a logic inverter to ensure that the unit reports bad conditions if the cable fails.  The sensor box is connected to the arduino via a CAT5 cable.  A waterproof connector is used for quick removal of the boxes.

![](https://raw.githubusercontent.com/warwick-one-metre/raindetector/master/images/board1.JPG)
![](https://raw.githubusercontent.com/warwick-one-metre/raindetector/master/images/board2.JPG)

The arduino board and firware supports two sensor boxes, but only one is currently deployed at the telescope on La Palma.

![](https://raw.githubusercontent.com/warwick-one-metre/raindetector/master/images/box2.JPG)
![](https://raw.githubusercontent.com/warwick-one-metre/raindetector/master/images/box1.JPG)

The unit reports the board status once a second through the USB-serial port.  The message format is
```
$AB\r\n
```
The lower 6 bits of A and B indicate the status of the individual boards in each sensor box. A 1 indicates that moisture is detected by the board, or a potential cable / box failure if all 6 bits are 1.
