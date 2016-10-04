// ucode.c file

char *cmd[]={"getpid", "ps", "chname", "kmode", "switch", "wait", "exit", 
             "fork", "exec", 0};

void SplitBySpace(char *s, int *argc, char argv[64][64])
{
	int i = 0;
	*argc = 0;

	while (*s)
	{
		if (*s == ' ')
		{
		    argv[*argc][i] = 0;
		    (*argc)++;
		    i = 0;
		}else{
		    argv[*argc][i] = *s;
		    i++;
		}
		s++;
	}
}

int show_menu()
{
	printf("********************* Menu ***************************\n");
	printf("* ps  chname  kmode  switch  wait  exit  fork  exec  *\n");
	/*         1     2      3      4      5     6     7     8      */
	printf("******************************************************\n");
}

int find_cmd(char *name)
{
	int i;   char *p;
	i = 0;   p = cmd[0];
	while (p){
		if (strcmp(p, name)==0)
			return i;
		i++;  p = cmd[i];
	} 
	return(-1);
}


int getpid()
{
	return syscall(0,0,0);
}

int ps()
{
	syscall(1, 0, 0);
}

int chname()
{
	char s[64];
	printf("input new name : ");
	gets(s);
	syscall(2, s, 0);
}

int kmode()
{
	printf("kmode : enter Kmode via INT 80\n");
	printf("proc %d going K mode ....\n", getpid());
	syscall(3, 0, 0);
	printf("proc %d back from Kernel\n", getpid());
}    

int kswitch()
{
	printf("proc %d enter Kernel to switch proc\n", getpid());
	syscall(4,0,0);
	printf("proc %d back from Kernel\n", getpid());
}

int wait()
{
	int child, exitValue;
	printf("proc %d enter Kernel to wait for a child to die\n", getpid());
	child = syscall(5, &exitValue, 0);
	printf("proc %d back from wait, dead child=%d", getpid(), child);
	if (child>=0)
		printf("exitValue=%d", exitValue);
	printf("\n");
	return child; 
} 

int exit()
{
	char exitValue;
	printf("enter an exitValue (0-9) : ");
	exitValue=(getc()&0x7F) - '0';
	printf("enter kernel to die with exitValue=%d\n",exitValue);
	_kexit(exitValue);
}

int _kexit(int exitValue)
{
	syscall(6,exitValue,0);
}

int fork()
{
	return syscall(7,0,0,0);
}

main0(char *s)
{
	int     argc = 0, i = 0, begin = 0;
	char *argv[64];
	char temp[100], *tmp;
	printf("received s in main0 is [%s]\n", s);
	getc();
	
	while (*s)
	{
		if (*s == ' ' || *(s + 1) == 0)
		{
			temp[i] = 0;
			if (*(s + 1) == 0)
			{
				temp[i-3] = 0;
			}
			tmp = &(temp[begin]);
			begin = i + 1;
			argv[argc] = tmp;
			argc++;
		}
		else
		{
			temp[i] = *s;
		}
		s++;
		i++;
	}
	
	main(argc, argv);
}

int exec(char *s)
{
	return syscall(8,s,0,0);
}

int ufork()
{
	int child = fork();
	(child) ? printf("parent ") : printf("child ");
	printf("%d return from fork, child pid=%d\n", getpid(), child);
}

int uexec()
{
	int r; 
	char filename[64];
	printf("enter exec filename : ");
	gets(filename);
	r = exec(filename);
	printf("exec failed\n");
	return -1;
}

int vfork()
{
	return syscall(9,0,0,0);
}

int invalid(char *name)
{
	printf("Invalid command : %s\n", name);
}
