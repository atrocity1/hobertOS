


extern unsigned char inb(unsigned short port);

const char keyboard_map[50] = {
    [0x1E] = 'A',
    [0x30] = 'B',
    [0x2E] = 'C',
    [0x20] = 'D',
    [0X12] = 'E',

};

unsigned char last_key = 0;

void kernel_print(const char*text, int line, int color);

void kernel_clear();

void kernel_digit_mode();

void kernel_input_keyboard();


void kernel_main(){
    kernel_clear();
    char * vga_color = (char*)0xB8000;
    kernel_print("WELCOME TO HOBERT OS", 1, 0x01);
    kernel_print("PRESS A TO DIGIT MODE" , 2, 0X0A);
    int position_byte = 480; //pula pra terceira linha onde vc quer digitar eh basicamente o byte onde quer escrever
    while (1)
    {
        unsigned char scancode = inb(0x60);

        if (scancode = 0x1E && scancode != 0)
        {
            kernel_digit_mode();
        }
        
    }
    
}

void kernel_print(const char*text, int line, int color){
    char * vga_color = (char*)0xB8000;

    int position = line * 160;

    int i = 0;
    while (text[i] != '\0') //tem q fazer um for aq mas to com preguiça
    {
        vga_color[position] = text[i];
        vga_color[position + 1] = color;

        i++;
        position += 2;

    }
    
}

void kernel_clear(){
    char *vga_color = (char*)0xB8000;
    for (int i = 0; i < 4000; i++)
    {
        if (i % 2 == 0)
        {
            vga_color[i] = ' ';
        }
        else{
            vga_color[i] = 0x07;
        }
        
    }
    
}

void kernel_digit_mode(){
    kernel_clear();
    while (1)
    {
        char *vga_color = (char*)0xB8000;
        unsigned char scancode = inb(0x60);


        if (scancode != 0)
        {
            if (keyboard_map[scancode] && scancode != 0)
            {
                vga_color[0] = keyboard_map[scancode];
            }
            
        }
        
    }
    

}