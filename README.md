# CaptureThePie
A simple collection of CTF challenges for the raspberry pi.

# Instructions
Clone this repo on a raspberry pi.
Create a very low priv ctf user account.
To try each level create a flag.h file in the respective folder, and compile with the build.sh script.
Run the bash script to start it up as root so that it can su to the ctf user.

# Troubleshooting
Older versions of the raspberry images have -no-pie as a standard compiler flag, whereas newer ones have -pie as the standard.
If level3 doesn't seem to work out for you compile it with -no-pie, similiarly level4 is intended to be compiled with -pie
