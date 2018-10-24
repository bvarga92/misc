import sys
import os
import datetime
import subprocess
import time

if len(sys.argv)!=3:
	print("Error: invalid arguments.")
	print("Usage: python %s \"file1 file2 ...\" \"command\""%sys.argv[0])
	print("Example: python %s \"program.c\" \"gcc program.c -o program && ./program\""%sys.argv[0])
	exit(1)

files=sys.argv[1].split()
command=sys.argv[2]

anyMissing=False
for file in files:
	if not os.path.exists(file):
		print("Error: File %s does not exist."%file)
		anyMissing=True
if anyMissing:
	exit(1)

print("Watch started. (Stop with Ctrl+C.)")

last=[datetime.datetime.fromtimestamp(os.path.getmtime(file)) for file in files]

while True:
	try:
		anyChanged=False
		for i,file in enumerate(files):
			currentDate=datetime.datetime.fromtimestamp(os.path.getmtime(file))
			if currentDate!=last[i]:
				last[i]=currentDate
				print("File %s modified."%file)
				anyChanged=True
		if anyChanged:
			print("Executing command...")
			subprocess.call(command,shell=True)
		time.sleep(1)
	except KeyboardInterrupt:
		print("Watch stopped. Bye.")
		exit(0)
