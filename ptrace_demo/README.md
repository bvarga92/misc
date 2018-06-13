# `ptrace` demó x86-64 arcitektúrára

A futtatás eredménye:

```
Running demo 1 (syscall tracing):
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Syscall  59 invoked.
Syscall  59 returned 0.
Syscall  59 returned 0.
Syscall  63 invoked.
Syscall  63 returned 0.
Syscall  12 invoked.
Syscall  12 returned 15257600.
Syscall  12 invoked.
Syscall  12 returned 15262144.
Syscall 158 invoked.
Syscall 158 returned 0.
Syscall  89 invoked.
Syscall  89 returned 29.
Syscall  12 invoked.
Syscall  12 returned 15397312.
Syscall  12 invoked.
Syscall  12 returned 15400960.
Syscall  21 invoked.
Syscall  21 returned -2.
Syscall   5 invoked.
Syscall   5 returned 0.
Syscall   1 invoked.
Hello world!
Syscall   1 returned 13.
Syscall 231 invoked.

Running demo 2 (memory modification):
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Ifmmp xpsme!

Cvt 113 Efwjdf 113: JE 9198:1135 Joufm Dpsq. Joufhsbufe Sbuf Nbudijoh Ivc
Cvt 113 Efwjdf 112: JE 2e7c:1113 Mjovy Gpvoebujpo 3.1 sppu ivc
Cvt 112 Efwjdf 114: JE 157c:gg21 Bnfsjdbo Nfhbusfoet, Jod. Wjsuvbm Lfzcpbse boe Npvtf
Cvt 112 Efwjdf 113: JE 9198:1135 Joufm Dpsq. Joufhsbufe Sbuf Nbudijoh Ivc
Cvt 112 Efwjdf 112: JE 2e7c:1113 Mjovy Gpvoebujpo 3.1 sppu ivc

Running demo 3 (single stepping):
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Hello world!
9800 instructions executed.

address: 40010c    instruction: 4800000001c0c748
address: 400113    instruction: 4800000001c7c748
address: 40011a    instruction: 4800600151c6c748
address: 400121    instruction: 0f0000000dc2c748
address: 400128    instruction: 000001c0c748050f
Hello world!
address: 40012a    instruction: 4800000001c0c748
address: 400131    instruction: 480060015fc6c748
address: 400138    instruction: 0f00000008c2c748
address: 40013f    instruction: 00003cc0c748050f
Hehe...
address: 400141    instruction: 480000003cc0c748
address: 400148    instruction: 0f00000000c7c748
address: 40014f    instruction: 206f6c6c6548050f
12 instructions executed.

Running demo 4 (breakpoint insertion):
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Hello world!
Breakpoint at 0x40013f. Press any key to continue.

Hehe...
```