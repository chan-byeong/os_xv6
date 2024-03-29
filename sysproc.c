#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//hello syscall
int sys_hello(void){
  char *ptr;

  if(argstr(0,&ptr) < 0) return -1;
  
  cprintf("hello %s \n",ptr);

  return 0;
}

//get tickets
int
sys_ticketget(void)
{
  return myproc()->tickets;
}

//set tickets
int
sys_ticketset(void)
{
  int ticket_num;
  if(argint(0,&ticket_num) < 0) return -1;
  else {
    myproc()->tickets = ticket_num;
  }
  return 0;
}


int 
sys_clone(void)
{
  void (*fcn)(void*, void*);
  void *arg1 , *arg2 , *stack;

  if(argptr(0, (void *)&fcn, sizeof(void *)) < 0 ||
     argptr(1, (void*)&arg1 , sizeof(void *)) < 0||
     argptr(2, (void*)&arg2 , sizeof(void *)) < 0||
     argptr(3, (void*)&stack , PGSIZE) < 0)
    return -1;

  return clone(fcn,arg1,arg2,stack);

}

int sys_join(void)
{
  void** stack;
  if(argptr(0, (void*)&stack, sizeof(void*)) < 0)
    return -1;

  return join(stack);
}