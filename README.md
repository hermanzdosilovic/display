display
=======

ASCII display. All-nighter, one night stand, goodbye 2014 "project".

![preview.gif](https://github.com/hermanzdosilovic/display/blob/master/preview.gif)

How to use it?
--------------

1. In the first line of _settings.txt_ file enter your message (max. 100 characters). There is "__hello, world\n__" by default.
2. In the second line of _settings.txt_ enter name of font you want to use (see [fonts](https://github.com/hermanzdosilovic/display/tree/master/fonts)). There is "__colossal__" by default.

2. Compile:

		$ gcc -std=c99 display.c -o display -lm
		
3. Run on Unix:

		$ ./display
	
	Run on Windows:
	
		>display
		

Use `CTRL + C` to stop the program.

Settings
--------
Once you compiled _display_ for your machine just use _settings.txt_ file to set settings that you want. And then just run _display_ again.

Tested on
---------
* OS X
* Linux
* Windows
