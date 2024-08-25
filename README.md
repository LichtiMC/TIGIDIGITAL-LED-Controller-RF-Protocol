# TIGIDIGITAL-LED-Controller-RF-Protocol
Some results of my reverse engineering of the TIGIDIGITAL LED Controller RF-Protocol and the Arduino Project "opentigi" to control the Lights with an nRF24L01

Flash the opentigi to an arduino with an nRF24 connected and you should be able to control your LED-Lights.
Unfortunately range is not very good, but this is true for the original remote controls too.

The excel file has emerged while reverse engineering the protocol with a Logic Analyzer and with a HackRF used to sniff the PL1167 radio comm.

All of this wouldn't have been possible (for me) without the excellent work of Henryk Plötz (https://github.com/henryk/openmili).


# The MIT License (MIT)

Copyright (c) 2015 henryk, Copyright (c) 2015 LichtiMC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
