Set shell=WScript.CreateObject("WScript.Shell")
Do While True
	shell.sendkeys("{CAPSLOCK}{CAPSLOCK}")
	WScript.Sleep(10000)
Loop