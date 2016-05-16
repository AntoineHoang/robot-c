
#ifndef DEL_H
#define DEL_H
#include <avr/io.h> 
#include <stdlib.h> 

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *); 

extern "C" void __cxa_pure_virtual(void); 

class del 

{
  
public:

  del(uint8_t delN);
  del(volatile uint8_t *portA, volatile uint8_t *portAddr, uint8_t pins);
  void * operator new(size_t size);
  void operator delete(void * ptr); 
  void * operator new[](size_t size);
  void operator delete[](void * ptr); 
  ~del() {;};
  
  void initialiser();
 
  void allumer(uint8_t couleur=0x01);
  void eteindre();
  void clignoter(uint8_t delais, uint8_t nbFois);

  

private:
  
   uint8_t delpins;
   volatile uint8_t *port;
   volatile uint8_t *portddr;

  
};
#endif
