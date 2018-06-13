#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/syscall.h>

int main(int argc, char* argv[]){
	pid_t child;
	int status, i, j;
	long orig_rax, rax, rdi, rsi, rdx, data, c;
	if(argc!=2){
		printf("Usage: %s executable_name\n\n",argv[0]);
		return 1;
	}
	child=fork();
	/* nem sikerult forkolni */
	if(child==-1){
		printf("Error: fork.\n\n");
	}
	/* mi vagyunk a gyerek */
	else if(child==0){
		ptrace(PTRACE_TRACEME,0,0,0); //megengedjuk a trace-elest
		execl(argv[1],argv[1],NULL); //inditjuk a programot
	}
	/* mi vagyunk a szulo */
	else{
		while(1){
			waitpid(child,&status,0); //varunk, hogy a gyerek csinaljon valamit
			if(WIFEXITED(status) || WIFSIGNALED(status)) break; //gyerek futasanak vege --> kesz vagyunk
			if(WSTOPSIG(status)==SIGTRAP){ //syscall belepes/kilepes tortent
				orig_rax=ptrace(PTRACE_PEEKUSER,child,8*ORIG_RAX); //itt a syscall szama
				rax=ptrace(PTRACE_PEEKUSER,child,8*RAX); //itt s visszateresi erteke
				if(orig_rax==SYS_write && rax==-ENOSYS){ //write() rendszerhivas tortent
					rdi=ptrace(PTRACE_PEEKUSER,child,8*RDI); //1. argumentum (stdout: 1)
					rsi=ptrace(PTRACE_PEEKUSER,child,8*RSI); //2. argumentum (string cime)
					rdx=ptrace(PTRACE_PEEKUSER,child,8*RDX); //3. argumentum (string hossza)
					if(rdi==1){ //a standard kimenetre ir a gyerek, belenyulunk
						for(i=0;i<rdx;i+=8){
							data=ptrace(PTRACE_PEEKDATA,child,rsi+i,0); //kiolvasunk 8 karaktert
							for(j=0;j<8;j++){
								c=((data>>(8*j))&0xFF);
								if((c>=0x30 && c<=0x39) || (c>=0x41 && c<=0x5A) || (c>=0x61 && c<=0x7A)){
									c=c+1; //minden betut es szamot megnovelunk eggyel
									data&=~(0x00000000000000FFUL<<(8*j));
									data|=c<<(8*j);
								}
							}
							ptrace(PTRACE_POKEDATA,child,rsi+i,data); //visszairjuk a modositott reszletet
						}
					}
				}
			}
			ptrace(PTRACE_SYSCALL,child,0,0); //a gyerek folytathatja a futast, a kovetkezo rendszerhivasrol ertesulunk
		}
	}
	return 0;
}
