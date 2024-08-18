# Clevo-W650SJ_FanControl
Better fan management for the Clevo W650SJ (and maybe other Clevo models)

>**!!! In any case I am not responsible for any damage that may occur to your computer, you use this program at your own risk. You have been warned !!!**


If you have this computer, you know that default fan management comes from hell. The fan turns slowly first, then turn fast for nothing, and there is occasional bursts when doing nothing. A nightmare for your ears.
Hopefully, with this software, it's over. The fans is quieter. The laptop will be a little warmer, but it doesn't matter, as the temperature barely reaches 65°C on my computer when the CPUs are 100%.


# INSTALLATION
Installation is very simple, just type the following commands in your favorite terminal :

`make`

 `sudo make install`

# UNINSTALL
If you want to remove this sofware, you can use this command :

`sudo make uninstall`

>!!! AND VERY IMPORTANT ! Press Fn+1 to restore the original settings, otherwise YOU CAN FRY YOUR CPU !!!

# ANOTHER TIPS
In addition, you can change thermal paste on the CPU and the GPU, as the original thermal pads are crap. Don't forget to remove residue with a cotton swab soaked in acetone.

Also, you can disable Turbo mode, but performance will be slightly impacted. You can use the following command as root in Linux if you don't have the PremaMod BIOS : 

`echo "1" | sudo tee /sys/devices/system/cpu/intel_pstate/no_turbo`

You can create a service if you want to keep this setting after a reboot.

# FOR THE CURIOUS
The software reads the CPU temperature directly in the EC, and set fan speed depending on current temperature. This function also uses EC. It's a slightly complicated solution, but unfortunately it's the only way since Clevo doesn't use a standard method for selecting the fan speed (non-standard ? Looks like Apple company ;-) )

Here are the different steps used in my software (temperature => fan speed in %) :

* < 55°C = 50%
* 55-60°C = 55%
* 60-65°C = 70%
* 65-70°C = 75%
* 70-75°C = 80%
* 75-80°C = 85%
* 80-90°C = 90%
* 90°C-105°C = 100%

# FOR WINDOWS USERS
You can use the following software and use the values above :

https://github.com/djsubtronic/ClevoFanControl

# CREDITS
Many thanks :

* LiZhenhuan1019 for the linux Clevo_Fan_Control, a great tool who inspired me. You can manually set the fan speed with it : https://github.com/LiZhenhuan1019/clevo_fan_control
* djsubtronic for the Windows Clevo Fan Control : https://github.com/djsubtronic/ClevoFanControl
* PCW, the french shop where I bought my Clevo W650SJ laptop in 2014 with my first salary : https://www.pcw.fr/
* Clevo manufacturer for their robust modular laptops, I still use mine after all these years :-)
