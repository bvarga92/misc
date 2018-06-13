gcc -o hello -static hello.c
gcc -o hello_asm -nostdlib hello_asm.s
gcc -o test1_strace test1_strace.c
gcc -o test2_memmod test2_memmod.c
gcc -o test3_step test3_step.c
gcc -o test4_brkpt test4_brkpt.c

printf "Running demo 1 (syscall tracing):\n"
printf "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
./test1_strace hello
printf "\n"

printf "Running demo 2 (memory modification):\n"
printf "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
./test2_memmod hello
printf "\n"
./test2_memmod /usr/bin/lsusb
printf "\n"

printf "Running demo 3 (single stepping):\n"
printf "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
./test3_step hello
printf "\n"
./test3_step -v hello_asm
#erdemes osszehasonlitani: objdump -d hello_asm
printf "\n"

printf "Running demo 4 (breakpoint insertion):\n"
printf "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
./test4_brkpt 0x40013F hello_asm
printf "\n"

find . ! \( -name '*.c' -o -name '*.s' -o -name '*.sh' \) -type f -exec rm -f {} +
