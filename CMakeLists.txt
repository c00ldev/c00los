cmake_minimum_required(VERSION 3.10)
project(c00los)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_FLAGS "-felf32 -gdwarf -i${CMAKE_SOURCE_DIR}/")

set(CMAKE_CXX_STANDARD 17)

add_executable(c00los boot.asm mode_x86.asm main.cpp console.cpp console.h console_x86.asm segment_desriptor_table.cpp segment_desriptor_table.h segment_descriptor_table_x86.asm memutils.h memutils_x86.asm interrupts.asm interrupts.inc isr.h isr_x86.asm port.cpp port.h port.asm interrupt_descriptor_table.cpp interrupt_descriptor_table.h interrupt_descriptor_table_x86.asm interrupts.h halt.asm interrupt_manager.cpp interrupt_manager.h keyboard.cpp keyboard.h)
set_target_properties(c00los PROPERTIES LINK_DEPENDS "${CMAKE_SOURCE_DIR}/linker.ld")
set_target_properties(c00los PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld")

set(QEMU_ARGS -kernel c00los -m 1024
        -net nic,model=virtio -net user
        -no-reboot -no-shutdown -d int -d cpu_reset -d guest_errors)

add_custom_target(boot
        COMMAND qemu-system-i386 ${QEMU_ARGS}
        DEPENDS c00los
        )

add_custom_target(debug
        COMMAND qemu-system-i386 ${QEMU_ARGS} -s -S
#        COMMAND i686-elf-gdb -x ${CMAKE_SOURCE_DIR}/gdb.ini
        DEPENDS c00los
#        DEPENDS ${CMAKE_SOURCE_DIR}/gdb.ini
        )
