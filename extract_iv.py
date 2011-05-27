

import sys, os



f = open(sys.argv[1])

output = False

i = 0
names = {}

for l in f.readlines():

   l = l.strip()
   l = l.replace('\t', ' ')
   l = l.replace('  ', ' ')
   l = l.replace('  ', ' ')

   if ".word" in l and "BootRAM" in l:
      output=False
      break

   if output:
      l = l.split(' ')
      if len(l) > 1:
         names[i] = l[1]
         i+=1

   if "g_pfnVectors:" in l:
      output = True



print "#ifndef __HANDLERS_H__"
print "#define __HANDLERS_H__\n\n"

print "#define WEAK __attribute__ ((weak))\n"

for i, name in names.items():
   if name not in ('0', '_estack', 'BootRAM', 'Reset_Handler'):
      print "extern void %s(void) WEAK;"%name

print
print
print '__attribute__ ((section(".isr_vector")))'
print "void (* g_pfnVectors[])( void ) = {"

for i, name in names.items():
   if name == '_estack':
      print ' &%s,'%name
   else:
      print ' %s,'%name

print ' BootRAM,'
print '};'
print '\n#endif'

#for i in *.s; do python extract_iv.py $i > ${i/stm32f10x_/}.h; done
