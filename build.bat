cd C:\saturn\sblproj
make -f makefile
pause
if exist cd\ goto created 
mkdir cd
copy c:\saturn\cdtools\abs.txt cd\abs.txt
copy c:\saturn\cdtools\bib.txt cd\bib.txt
copy c:\saturn\cdtools\cpy.txt cd\cpy.txt
:created
copy out.bin cd\0.bin
c:\saturn\cdtools\mkisofs -sysid "SEGA SATURN" -volid "SaturnApp" -volset "SaturnApp" -publisher "SEGA ENTERPRISES, LTD." -preparer "SEGA ENTERPRISES, LTD." -appid "SaturnApp" -abstract "c:\saturn\cdtools\ABS.TXT" -copyright "c:\saturn\cdtools\CPY.TXT" -biblio "c:\saturn\cdtools\BIB.TXT" -generic-boot "c:\saturn\cdtools\ip_gnu.bin" -full-iso9660-filenames -o out\out.iso cd
cd out
if not exist out.bin goto nodelete
del out.bin
del out.cue
:nodelete
"c:\Program Files\PowerISO\piso.exe" convert out.iso -o out.bin
c:\saturn\mednafen\mednafen out.cue 
REM c:\saturn\yabause\!yabause.exe 