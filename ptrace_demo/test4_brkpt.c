#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/errno.h>

struct breakpoint{
	long long addr;
	long orig_instr;
};

int main(int argc, char* argv[]){
	pid_t child;
	int status;
	struct breakpoint bp;
	struct user_regs_struct regs;
	if(argc!=3){
		printf("Usage: %s bp_address executable_name\n\n",argv[0]);
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
		execl(argv[2],argv[2],NULL); //inditjuk a programot
	}
	/* mi vagyunk a szulo */
	else{
		bp.addr=strtoll(argv[1],NULL,16);
		waitpid(child,&status,0);
		bp.orig_instr=ptrace(PTRACE_PEEKTEXT,child,bp.addr,0); //kimentjuk az eredeti utasitast
		ptrace(PTRACE_POKETEXT,child,bp.addr,(bp.orig_instr&0xFFFFFFFFFFFFFF00)|0xCC); //trap utasitast irunk a helyere
		ptrace(PTRACE_CONT,child,0,0); //folytathatja a futast a gyerek
		waitpid(child,&status,0); //SIGTRAP, mert a gyerek vegrehajtotta a breakpointot
		ptrace(PTRACE_POKETEXT,child,bp.addr,bp.orig_instr); //visszairjuk az eredeti utasitast
		ptrace(PTRACE_GETREGS,child,0,&regs); //kiolvassuk a regisztereket
		regs.rip=bp.addr; //RIP erteke most bp.addr+1 --> visszaleptetjuk, hogy vegre tudja hajtani az eredeti utasitast
		ptrace(PTRACE_SETREGS,child,0,&regs); //kiolvassuk a regisztereket
		printf("Breakpoint at 0x%llx. Press any key to continue.\n",regs.rip);
		getchar();
		ptrace(PTRACE_CONT,child,0,0); //folytathatja a futast a gyerek
	}
	return 0;
}
