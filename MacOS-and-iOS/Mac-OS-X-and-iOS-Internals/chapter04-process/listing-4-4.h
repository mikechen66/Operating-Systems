// Listing 4-4: DYLD_INTERPOSE macro definition in dyld's include/mach-o/dyld-interposing.h

#if !defined(_DYLD_INTERPOSING_H_) 
#define _DYLD_INTERPOSING_H_
/*  Example:
 *  static
 *  int
 *  my_open(const char* path, int flags, mode_t mode)
 *  {
 *    int value;
 *    // do stuff before open (including changing the arguments)
 *    value = open(path, flags, mode);
 *    // do stuff after open (including changing the return value(s))
 *    return value;
 *  }
 *  DYLD_INTERPOSE(my_open, open)
 */
#define DYLD_INTERPOSE(_replacment,_replacee) \
   __attribute__((used)) static struct{ const void* replacment; const void* replacee; } 
_interpose_##_replacee \
            __attribute__ ((section (”__DATA,__interpose”))) = { (const void*)(unsigned 
long)&_replacment, (const void*)(unsigned long)&_replacee };
#endif



/*
Output 4-9: Dumping the interpose section of libgmalloc
morpheus@Ergo (/)% otool -lV /usr/lib/libgmalloc.dylib
/usr/lib/libgmalloc:
..
Load command 1
      cmd LC_SEGMENT_64
  cmdsize 632
  segname __DATA
..
Section
  sectname __interpose
   segname __DATA
      addr 0x0000000000005200
      size 0x0000000000000240
    offset 20992
     align 2ˆ4 (16)
    reloff 0
    nreloc 0
      type S_INTERPOSING
attributes (none)
 reserved1 0
 reserved2 0
 */

/*
Output 4-10: Running pagestuff(1) to show interpose symbols in libgmalloc.
morpheus@Ergo(/)% pagestuff/usr/lib/libgmalloc.dylib 6 
File Page 6 contains contents of section (__DATA,__nl_symbol_ptr) (x86_64)
File Page 6 contains contents of section (__DATA,__la_symbol_ptr) (x86_64)
File Page 6 contains contents of section (__DATA,__const) (x86_64)
File Page 6 contains contents of section (__DATA,__data) (x86_64)
File Page 6 contains contents of section (__DATA,__interpose) (x86_64)
File Page 6 contains contents of section (__DATA,__bss) (x86_64)
File Page 6 contains contents of section (__DATA,__common) (x86_64)
Symbols on file page 6 virtual address 0x5000 to 0x6000
  . . .
  0x0000000000005200 __interpose_malloc_set_zone_name
  0x0000000000005210 __interpose_malloc_zone_batch_free
  0x0000000000005220 __interpose_malloc_zone_batch_malloc
  0x0000000000005230 __interpose_malloc_zone_unregister
  0x0000000000005240 __interpose_malloc_zone_register
  0x0000000000005250 __interpose_malloc_zone_realloc
   . . .
  0x00000000000053b0 __interpose_free
  0x00000000000053c0 __interpose_malloc
 */