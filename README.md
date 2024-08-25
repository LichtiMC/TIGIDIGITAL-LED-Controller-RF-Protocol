# TIGIDIGITAL-LED-Controller-RF-Protocol
Some results of my reverse engineering of the TIGIDIGITAL LED Controller RF-Protocol and the Arduino Project "opentigi" to control the Lights with an nRF24L01

Flash the opentigi to an arduino with an nRF24 connected and you should be able to control your LED-Lights.
Unfortunately range is not very good, but this is true for the original remote controls too.

The excel file has emerged while reverse engineering the protocol with a Logic Analyzer and with a HackRF used to sniff the PL1167 radio comm.

All of this wouldn't have been possible (for me) without the excellent work of Henryk Plötz (https://github.com/henryk/openmili).
