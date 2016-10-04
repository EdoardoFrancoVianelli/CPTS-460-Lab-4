/*************************************************************************
  usp  1   2   3   4   5   6   7   8   9  10   11   12    13  14  15  16
----------------------------------------------------------------------------
 |uds|ues|udi|usi|ubp|udx|ucx|ubx|uax|upc|ucs|uflag|retPC| a | b | c | d |
----------------------------------------------------------------------------
***************************************************************************/
#define PA 13
#define PB 14
#define PC 15
#define PD 16
#define AX  8

/****************** syscall handler in C ***************************/
int kcinth()
{
	int    a,b,c,d, r;

	a = get_word(running->uss, running->usp + 2 *     PA);
	b = get_word(running->uss, running->usp + 2 * (PA+1));
	c = get_word(running->uss, running->usp + 2 * (PA+2));
	d = get_word(running->uss, running->usp + 2 * (PA+3));
	
	//==> WRITE CODE TO GET get syscall parameters a,b,c,d from ustack

	switch(a){
		case 0 : r = running->pid;     break;
		case 1 : r = do_ps();          break;
		case 2 : r = chname(b);        break;
		case 3 : r = kkfork();         break;
		case 4 : r = tswitch();        break;
		case 5 : r = do_wait(b);       break;
		case 6 : r = do_exit(b);       break;
		case 7 : r = fork();	       break; 
		case 8 : r = kexec(b);         break; 
		
		case 90: r =  getc();          break;
		case 91: color=running->pid+11;
			r =  putc(b);          break;       
		case 99: do_exit(b);           break;
		default: printf("invalid syscall # : %d\n", a); 
	}
	
	//==> WRITE CODE to let r be the return value to Umode

	put_word(r, running->uss, running->usp + 2 * AX);	
}








