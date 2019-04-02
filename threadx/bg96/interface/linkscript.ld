/****************************************************************************
 * The linker command script
 *  Created on: 04.06.2018
 *      Author: Georgi Angelov
 ****************************************************************************/

_RO_BASE_ = ROM_ADDRESS; /* -Xlinker --defsym=ROM_ADDRESS=${ROM_BASE} */
heap_size = 64k;

MEMORY
{
   ROM (rx) : ORIGIN = _RO_BASE_ , LENGTH = 3*1024k
}

SECTIONS
{
/*--------------------------------------------------------------------*/	
    . = _RO_BASE_;
	.preamble :
    {
        KEEP( *( .preamble ) );
    } > ROM
	. = ALIGN(4);
    .text :
    {
     	PROVIDE( SHELL_ENTRY = . );
        KEEP( *( .shell_entry ) );
     	PROVIDE( THREAD_ENTRY = . );
        KEEP( *( .thread_entry ) );
     	PROVIDE( THREAD_CALLBACK = . );
        KEEP( *( .thread_callback ) );

		__dso_handle = .; 
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP( *(SORT(.init_array.*)) )
        KEEP( *(.init_array*) )
        PROVIDE_HIDDEN (__init_array_end = .);
		. = ALIGN(4);
        *( .text .text.* i.* )
        *( .glue_7t )
        *( .glue_7 )
        *( .ctors )
        *( .dtors )
        *( .gnu.linkonce.t.* )
        *( .gnu.linkonce.r.* )
        *( .gcc_except_table )
        *( .rodata* .constdata* .conststring*  )
        *(.note.gnu.build-id)		         
    } > ROM
	. = ALIGN(4);
	.ARM.exidx : 
	{ 
	    __exidx_start = .;
	    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
	    __exidx_end = .;
	} >ROM
	. = ALIGN(4);
	_RO_BASE_END_ = .; 
	
/*--------------------------------------------------------------------*/	
	
	_DATA_BEGIN_ = .;
	. = ALIGN(4);
    .data ALIGN(4):
    {
        *( .data .data.* .gnu.linkonce.d.* )
    } > ROM
	. = ALIGN(4);
	_DATA_END_ = .;

/*--------------------------------------------------------------------*/

	_BSS_BEGIN_ = .;
	. = ALIGN(4);
    .bss ALIGN(4):
    {
        *( .bss .bss.* .gnu.linkonce.b.* )
        *( COMMON )
    } > ROM
	. = ALIGN(4);
	.heap ALIGN(4):
	{
		_heap_start = .;
	    . = . + heap_size;
	    _heap_end = .;
	} > ROM
	. = ALIGN(4);
	_BSS_END_ = .;

/*--------------------------------------------------------------------*/

	PROVIDE(IMAGE_ER_RO_LENGTH 		= _RO_BASE_END_ - _RO_BASE_ );
	PROVIDE(IMAGE_ER_RW_LENGTH 		= _DATA_END_ - _DATA_BEGIN_ );
	PROVIDE(IMAGE_ER_ZI_ZI_LENGTH 	= _BSS_END_ - _BSS_BEGIN_ );	

}

