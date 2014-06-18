/*
 * Kernel: beagle.cmd
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * Linker command file for BeagleBone
 * Basic linker options
 */


/* supress warning _c_int00 entry point */
--diag_suppress=10063

-stack           0x00002000
-heap            0x00004000

/* set entry point to boot asm (boot.asm) func */
-e boot

MEMORY
{
   stack_memory:     ORIGIN 0x81000000 LENGTH = 0x00002000
   virtual_memory:       ORIGIN 0x81002000 LENGTH = 0x01000000
   sysmem_memory:      ORIGIN 0x82002000 LENGTH = 0x00004000
}



SECTIONS
{
   ORDER
     .stack      > stack_memory  {
      systemStack = .;
   }

   .text       > virtual_memory

   .bss        > virtual_memory
   .const      > virtual_memory
   .cinit      > virtual_memory
   .pinit      > virtual_memory
   .cio        > virtual_memory
   .switch     > virtual_memory
   .far        > virtual_memory
   .data       > virtual_memory
   .switch     > virtual_memory
   .init_array > virtual_memory




   .sysmem     > sysmem_memory



}
