bits 32                         
section .multiboot
    align 4
    dd 0x1BADB002              
    dd 0x00                    
    dd -0x1BADB002              

section .text
global _start
extern kernel_main              

_start:
    cli                        
    mov esp, stack_space        
    call kernel_main            
    hlt

global inb
inb: 
    mov dx, [esp + 4]
    in al, dx
    ret

section .bss
resb 8192                       
stack_space: