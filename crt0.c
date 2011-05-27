#include "stm32f10x.h"

extern volatile unsigned long _ebss, _edata, _sbss, _sdata, _sidata;
extern void _estack();
extern int main(void);

void __attribute__((__interrupt__)) Reset_Handler() {

   volatile unsigned long* pulSrc;
   volatile unsigned long* pulDest;

   // Copy the data segment initializers from flash to SRAM.
   pulSrc = &_sidata;

   for( pulDest = &_sdata; pulDest < &_edata; ) {
      *(pulDest++) = *(pulSrc++);
   }

   // Zero fill the bss segment.
   for( pulDest = &_sbss; pulDest < &_ebss; ) {
      *(pulDest++) = 0;
   }

   // Call the application's entry point.
   SystemInit();
   main();
}

#define BootRAM (void (*)(void))0xF1E0F85F

#if defined (STM32F10X_LD)
	#include "it_vector_ld.h"
#elif defined (STM32F10X_LD_VL)
	#include "it_vector_ld_vl.h"
#elif defined (STM32F10X_MD)
	#include "it_vector_md.h"
#elif defined (STM32F10X_MD_VL)
	#include "it_vector_md_vl.h"
#elif defined (STM32F10X_HD)
	#warning "Using HD startup"
	#include "it_vector_hd.h"
#elif defined (STM32F10X_HD_VL)
	#include "it_vector_hd_vl.h"
#elif defined (STM32F10X_XL)
	#include "it_vector_xl.h"
#elif defined (STM32F10X_CL)
	#warning "Using CL startup"
	#include "it_vector_cl.h"
#else
	#error "Please select first the target STM32F10x device used in your application"
#endif

