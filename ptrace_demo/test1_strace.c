#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/errno.h>

int main(int argc, char* argv[]){
	pid_t child;
	int status;
	long orig_rax, rax;
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
		kill(getpid(),SIGSTOP); //megallunk, hogy az exec-rol is ertesuljon a szulo
		execl(argv[1],argv[1],NULL); //inditjuk a programot
	}
	/* mi vagyunk a szulo */
	else{
		while(1){
			waitpid(child,&status,0); //varunk, hogy a gyerek csinaljon valamit
			if(WIFEXITED(status) || WIFSIGNALED(status)) break; //gyerek futasanak vege --> kesz vagyunk
			if(WSTOPSIG(status)==SIGTRAP){ //syscall belepes/kilepes tortent
				orig_rax=ptrace(PTRACE_PEEKUSER,child,8*ORIG_RAX); //itt a syscall szama
				rax=ptrace(PTRACE_PEEKUSER,child,8*RAX); //itt a visszateresi erteke
				if(rax==-ENOSYS) //belepes volt --> a visszateresi ertek ervenytelen
					printf("Syscall %3ld invoked.\n",orig_rax);
				else //visszateres volt
					printf("Syscall %3ld returned %ld.\n",orig_rax,rax);
			}
			ptrace(PTRACE_SYSCALL,child,0,0); //a gyerek folytathatja a futast, a kovetkezo rendszerhivasrol ertesulunk
		}
	}
	return 0;
}
