ENTRY(Reset_Handler)

MEMORY
{
    I-SRAM : ORIGIN = 0x08010400, LENGTH = 0xEFC00   /* to 0x08100000 */
    D-SRAM : ORIGIN = 0x20032000, LENGTH = 0x16000   /* to 0x20048000 */
    V-SRAM : ORIGIN = 0x20000000, LENGTH = 0x100
}

PROVIDE(__ram_end  = 0x20048000);
PROVIDE(__heap_end = __ram_end);

PAYLOAD_BASE = 0x08010400;

SECTIONS
{
    .vectors PAYLOAD_BASE : {
        *(.vectors)
        *(.vectors.*)
    } > I-SRAM

    .blob_text __text_base_arg : {
        *zw_app.o(.text)
        *zw_app.o(.text.*)
    } > I-SRAM

    .blob_rodata __rodata_base_arg : {
        *zw_rodata.o(.rodata)
        *zw_rodata.o(.rodata.*)
    } > I-SRAM

    .sdk_text __sdk_text_base_arg : {
        *(EXCLUDE_FILE(*zw_app.o *zw_rodata.o *zw_symbols.o) .text)
        *(EXCLUDE_FILE(*zw_app.o *zw_rodata.o *zw_symbols.o) .text.*)
        *(.gnu.linkonce.t.*)
        KEEP(*(.init))
        KEEP(*(.fini))
        __ctor_start__ = .;
        KEEP(*(.ctors)) KEEP(*(.ctors.*))
        __ctor_end__ = .;
        __dtor_start__ = .;
        KEEP(*(.dtors)) KEEP(*(.dtors.*))
        __dtor_end__ = .;
        KEEP(*(.init_array)) KEEP(*(.init_array.*))
        KEEP(*(.fini_array)) KEEP(*(.fini_array.*))
        . = ALIGN(4);
    } > I-SRAM

    .sdk_rodata : {
        . = ALIGN(4);
        *(.rodata) *(.rodata.*) *(.rdata) *(.rdata.*)
        *(.got) *(.got.plt) *(.sdata2.*) *(.data2.*)
        *(.gcc_except_table) *(.gcc_except_table.*)
        . = ALIGN(4);
        __erodata = .;
    } > I-SRAM

    .data 0x20032000 : AT(ADDR(.sdk_rodata) + SIZEOF(.sdk_rodata)) {
        __data_start__ = .;
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d.*)
        *(.sdata) *(.sdata.*) *(.gnu.linkonce.s.*)
        . = ALIGN(4);
        __data_end__ = .;
    } > D-SRAM

    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start__ = .;
        *(.dynsbss)
        *(.sbss) *(.sbss.*) *(.scommon)
        *(.dynbss)
        *(.bss) *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
        __end = .; end = .;
    } > D-SRAM

    .vdata ORIGIN(V-SRAM) (NOLOAD) : ALIGN(0x400) {
        __vdata_start__ = .;
        *(.vdata)
        *(.vdata.*)
        . = ALIGN(4);
        __vdata_end__ = .;
    } > V-SRAM

    /DISCARD/ : {
        *(.comment) *(.note*) *(.eh_frame*) *(.csky_stack_size)
        *(.csky.attributes) *(.interp) *(.dynamic) *(.dynsym)
        *(.dynstr) *(.hash) *(.gnu.*)
    }
}

PROVIDE(flash_data_region_start = ADDR(.sdk_text));

ASSERT(ADDR(.vectors) == 0x08010400, "vectors must start at 0x08010400")
ASSERT(SIZEOF(.vectors) == 0x100, "vector table must be exactly 0x100 bytes")
ASSERT(ADDR(.vdata) == 0x20000000, ".vdata/irq_vectors must sit at 0x20000000 to match VBR")
ASSERT(SIZEOF(.vdata) == 0x100, "vector shadow must be exactly 0x100 bytes")
ASSERT(SIZEOF(.blob_text) == 0x1E260, "blob .text size differs from stock 0x1E260")
ASSERT(SIZEOF(.blob_rodata) == 0x4FC78, "blob .rodata size differs from stock 0x4FC78")
ASSERT((ADDR(.blob_text) & 3) == 0, "blob .text base must be 4-aligned")
ASSERT((ADDR(.blob_rodata) & 3) == 0, "blob .rodata base must be 4-aligned")
ASSERT((ADDR(.sdk_text) & 3) == 0, "SDK .text base must be 4-aligned")
ASSERT(ADDR(.blob_text) >= ADDR(.vectors) + SIZEOF(.vectors), "blob .text overlaps the vector table")
ASSERT(ADDR(.blob_text) + SIZEOF(.blob_text) <= ADDR(.blob_rodata), "blob .text reaches into the blob rodata region")
ASSERT(ADDR(.blob_rodata) + SIZEOF(.blob_rodata) <= ADDR(.sdk_text), "blob rodata reaches into the SDK text region")
ASSERT(__erodata + SIZEOF(.data) <= 0x08096000, "SDK data image crosses into the persistent/calibration region")
ASSERT(ADDR(.data) == 0x20032000, "SDK .data base moved out of the reclaimed window")
ASSERT(__data_start__ >= 0x20030C78 + 0x1388, "SDK .data intrudes on the vendor BSS guard band")
ASSERT(__bss_start__ >= __data_end__, "SDK .data and .bss overlap")
ASSERT(__bss_end__ <= 0x20048000, "SDK .bss crosses the D-SRAM reservation")
ASSERT(__app_data_init - ADDR(.blob_rodata) == 0x4F9EC, "vendor .data image is not where .blob_rodata puts it")
ASSERT(__app_data_start == 0x20000100, "vendor .data VMA changed")
ASSERT(__app_bss_start == 0x2000038C, "vendor .data size changed")
ASSERT(__app_bss_end == 0x20030C78, "vendor .bss extent changed")
