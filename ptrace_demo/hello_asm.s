.globl  _start

.text
_start:
    mov    $1, %rax     # write() rendszerhivas
    mov    $1, %rdi     # 1. argumentum (stdout)
    mov    $str1, %rsi  # 2. argumentum (string cime)
    mov    $13, %rdx    # 3. argumentum (string hossza)
    syscall
    mov    $1, %rax     # kiirjuk a masikat is
    mov    $str2, %rsi  # a masik string
    mov    $8, %rdx     # ez 8 karakter hosszu
    syscall
    mov    $60, %rax    # exit() rendszerhivas
    mov    $0, %rdi     # visszateresi ertek
    syscall

.data
str1:
    .string "Hello world!\n"
str2:
    .string "Hehe...\n"
