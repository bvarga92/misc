#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/errno.h>

int main(int argc, char* argv[]){
	pid_t child;
	int status, verbose;
	long icnt=0, instruction;
	struct user_regs_struct regs;
	if(argc==3 && argv[1][0]=='-' && argv[1][1]=='v' && argv[1][2]==0){
		verbose=1;
	}
	else if(argc==2){
		verbose=0;
	}
	else{
		printf("Usage: %s [-v] executable_name\n\n",argv[0]);
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
		execl(argv[argc-1],argv[argc-1],NULL); //inditjuk a programot
	}
	/* mi vagyunk a szulo */
	else{
		while(1){
			waitpid(child,&status,0); //varunk, hogy a gyerek csinaljon valamit
			if(WIFEXITED(status) || WIFSIGNALED(status)) break; //gyerek futasanak vege --> kesz vagyunk
			icnt++;
			if(verbose){
				ptrace(PTRACE_GETREGS,child,0,&regs); //kiolvassuk a regisztereket
				instruction=ptrace(PTRACE_PEEKTEXT,child,regs.rip,0); //kiolvassuk, mire mutat az instruction pointer
				printf("address: %llx    instruction: %016lx\n",regs.rip,instruction);
			}
			ptrace(PTRACE_SINGLESTEP,child,0,0); //kovetkezo utasitasig futhat a gyerek
		}
		printf("%lu instructions executed.\n",icnt);
	}
	return 0;
}
