# CaptureThePie
A simple collection of CTF challenges for the raspberry pi.

# Instructions
Clone this repo on a raspberry pi.
To try each level create a flag.h file in the respective folder, compile with "gcc levelN.c" and run with run.sh
The binary will be running on port 9000 of your raspi

# Troubleshooting
Older versions of the raspberry images have -no-pie as a standard compiler flag, whereas newer ones have -pie as the standard.
If level3 doesn't seem to work out for you compile it with -no-pie, similiarly level4 is intended to be compiled with -pie
