M1: multi-platform arcade music and sound emulator 
v0.7.8a10 "MegaDrive" released August 4, 2008

NOTE: This is an old readme file because I can't find a newer one.
The current build version of v0.7.9a1.

Core by R. Belmont, Phil Bennett, and UNKNOWNFILE.
Mac version by Richard Bannister.
Windows build of v0.7.9a1 with VGM output by Valley Bell.

Main site: http://rbelmont.mameworld.info/?page_id=223
Forums   : http://www.bannister.org/forums/
Bridge M1 and updated list files: http://www.e2j.net/
VGM mod Forum: http://www.smspower.org/forums/viewtopic.php?t=11965
---------------------------------------------------------

M1 lets you enjoy music from over 1400 arcade games, from the classics 
through the 3D era.  It even supports games for which full emulation isn't
otherwise possible.  For most games, you can also listen to all the sound
effects, but 100% coverage is not guaranteed of all sounds in all games.


System requirements
-------------------

Minimum: 400 MHz CPU, 32 MB RAM, stereo CD-quality soundcard
Win32 (Win98, ME, 2000, or XP) or a modern Linux based system
(Glibc 2.5, like Fedora Core 6, SuSE 10.1, the latest Ubuntu, etc).

NOTE: Some games may have requirements far in excess of the minimum.  
In particular, DCS games like Killer Instinct need 750 MHz or more
to play without breakups.

The Windows version of M1 is developed on and for Windows Vista, and
you'll have best results with Windows 2000, XP, or Vista.

For Linux, 3 executables are included:
m1     - 32-bit x86
m1-x64 - 64-bit x64
m1-ppc - 32-bit PowerPC (including PlayStation 3 Linux)

How to use (commandline)
------------------------

Edit m1.ini to point to your ROMs.  It's format is like this:
; lines starting with a semicolon are comments and are ignored
[ROMPATH]   <- this starts the rompath section.Each line after that is a path
roms	    <- this is the default path, the roms/ folder where the exe is
c:\roms\mame\ <- add additional paths here
f:\server01\archive\roms\ <- add as many as you need

[WAVPATH]   <- this starts the wave path section, where output .WAV files go
waves	    <- only one path will be paid attention to here, unlike the
               rom path!


Run the app from the command line (yes DOS!) like this:
m1 [switches] [romname]
The switches can be any of these:
-a disables "album mode" and the use of .lst files.  Handy if a .lst file
   exists for a song but you want to "explore" for more sounds/tracks.
   (Note: tracks with names will still show those names, but you will
   no longer be restricted to selecting only named tracks).
-b lists all games, sorted by hardware type
-d lists the required ROMs for all games in a format compatible with 
   MAME's -listinfo.  ROM managers such as ClrMamePro can use this to
   automatically support M1.
-i shows the required ROMs for a given game name.  ROM managers can use
   this in conjunction with the -l switch to automatically build a ".DAT"
   for M1.
-l lists all games, sorted in alphabetical order
-mN: sets the headphone mix, in which the game's left channel is mixed
   into the right and vice versa.  This is so-named because it's useful
   for headphones to avoid the stark stereo imaging you otherwise can get.
   N ranges from 0 (full stereo) to 100 (full mono).
-n turns off normalization (see below for a detailed explanation of this)
-o shows the current volume that normalization has calculated, for use
   with the -v switch.
-rN: sets the output sample rate of M1.  N can range from 8000 to 48000.
   Higher values sound better but require a faster CPU.  Some soundcards
   (notably SBLive! and Audigy models) slightly distort the sound if it's
   not at 48000, so on those cards -r48000 is recommended.  Default: 44100.
-t disables forcing maximum track lengths from the .lst files.
-vN: disabled normalization (like -n) but also lets you set a fixed 
   volume level.  N ranges from 0 to 2100, where 0 is silent, 100 is
   no amplification, 200 = 2x amplify, 300 = 3x amplify, etc.
-w records the output to a .WAV file.  The filename is constructed from
   a combination of the game's name and the song number, so you can get
   .WAVs for each song in your favorite game simply by navigating them.
-g records the output to a .VGM file.  The filename is constructed from
   a combination of the game's name and the song number. If you have
   list files, a title is exported to its GD3 tag.

While the commandline M1 is running, you can press the following keys:
Q or ESC quits
+ and - change songs
/ and * change games

If a ROM loading error occurs, M1 commandline will simply exit.


NOTE: Song numbers vary by game and can have a large range on some games.
Not all numbers correspond to useful playable songs - some may just play
garbage.  Most games in fact have very few mapped working numbers
(less than 100 in many cases).


Changes since 0.7.8a9
---------------------
* Improved Sega Genesis/Mega Drive support
* Fixed YM2612/3834 being in mono all the time
* Fixed "out of timers" error in some Genesis/Mega Drive games


Known problems (do not waste time on the boards asking about there)
--------------
* Star Wars Arcade has corruption at the start of some songs.  This is known.
* Namco C352 games do not sound perfect, especially Mr. Driller and a few others.
  This is known.
* The YMF271 OPX chip is not yet perfectly emulated and not all songs in all
  games will sound exactly right.  This is known.


Most wanted ROMs!  If you have these PCBs, please get them dumped!
------------
* Taito's "Double Axle" (US version of "Power Wheels") is misdumped.  The 
  sample ROM C78-12.33 should be 8 megabit rather than 4.  This is why 
  the Japanese set is the one in M1 rather than the usual MAME parent.

Thanks
------
* Special thanks to CAB of AMUSE, for leading the way and making me 
  realize a multi-arcade sound emulator was possible in the first place.
* Big thanks to the Hoot development team for their Taito F3 work.
* ZEK.  Because.
* All e2j.net board users for great feedback and making the project
  worthwhile.
* All CPU and sound cores not specifically credited are from MAME/MESS.
  Thanks to the many contributors who made them possible.
* Viva Nonno HLE sound engine courtesy of Cap.  Thanks!!!
* Musashi 680x0 CPU emulation by Karl Stenerud and MAMEdev.
* FM OPL/OPN/OPM emulation by Tatsuyuki Satoh and Jarek Burczynski.
* OPL4 (YMF278-B) PCM emulation by R. Belmont and O. Galibert.
* YMF271 emulation by Ville Linde and R. Belmont.
* MultiPCM emulation by R. Belmont based on info from CAB of AMUSE, TitoJ of
  SMOG, and DMP Soft (Hoot).
* SCSP (Saturn Custom Sound Processor) emulation by ElSemi and R. Belmont.
* www.System16.com by Toby Broyad.
* Lev, Atila and everyone at ZTNet/Emulation World for the webspace.
* .LST file format by Fujix.
* Richard Bannister at bannister.org for the message boards.
* ivilded for the great site design and coding.
* Additional testing by Toby Broyad and Richard Bannister.
* Additional thanks to Smitdogg, Randy Hoffman, The Guru, Brian Troha, 
  UNKNOWNFILE, and the Belgian Dump Team.


Legal
-----
1) You may freely distribute this emulator as long as it is not on the same
   medium as the necessary ROM files.
2) You must never charge money for this emulator.
3) You must not obtain or use ROMs for machines you do not own.  If you
   decide to anyway, it is entirely at your own risk.
4) You must not distribute altered versions of this emulator or it's
   documentation.
5) This emulator is distributed with NO WARRANTY as to it's functionality
   or fitness for any purpose.  Although the software is believed to be
   free of major problems, the authors cannot be held liable for any damage
   or problems related to the use of this emulator.
6) We will not give you ROMs, and you may not ask for them on our message
   boards.  Violators will be banned.

