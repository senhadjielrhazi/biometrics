@echo off
echo Make CD for Secure Workstation Product Suite.....
rmdir /S /Q "W:\PC\Bin\Exe\CD Rom"
mkdir "W:\PC\Bin\Exe\CD Rom"
echo Copying files for installer.....
copy "Quick Installer\Media\New CD-ROM Media\Disk Images\Disk1\*.*" "W:\PC\Bin\Exe\CD Rom\*.*"
echo Copying files for autorun.....
copy "Autorun\*.*" "W:\PC\Bin\Exe\CD Rom\*.*"
echo Copying files for repair and help.....
mkdir "W:\PC\Bin\Exe\CD Rom\Procedure de depannage"
copy "Procedure de depannage\*.*" "W:\PC\Bin\Exe\CD Rom\Procedure de depannage\*.*"
mkdir "W:\PC\Bin\Exe\CD Rom\Aide"
copy "SW Access\SWAccess_EXE\hlp\Secure Workstation.cnt" "W:\PC\Bin\Exe\CD Rom\Aide\Secure Workstation.cnt"
copy "SW Access\SWAccess_EXE\hlp\Secure Workstation.hlp" "W:\PC\Bin\Exe\CD Rom\Aide\Secure Workstation.hlp"
echo Making CD for Secure Workstation Product Suite OK!
pause