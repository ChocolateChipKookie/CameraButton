#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


>^>+k::		;Hotkey combination(in this case right control, right shift and K)
RunWait, ".\\CameraButton.exe" 		;Path to CameraButton.exe, if you put it to startup, you need to put another path, so camera button doesn't get called every time you start your computer

if ErrorLevel = 1
{
	Run, explore "C:\\Users"	;Secret repository you want to open, you can put anything you want in here you want to happen when camera button is activated
}
else
{
	clp = %Clipboard%
	RunWait, ".\\TakePicture.exe"		;Take the picture of the bad guy who wants to access your data
	Run, %Clipboard%
	Clipboard = %clp%
	MsgBox, "Hey sweaty!"				;Sexy message
}

return