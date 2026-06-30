extern unsigned char inb(unsigned short port);

void kernel_print(const char*text, int line, int color);

void kernel_clear();

void kernel_input_keyboard();

void kernel_main(){
    kernel_clear();
    char * vga_color = (char*)0xB8000;
    kernel_print("WELCOME TO HOBERT OS", 1, 0x01);
    kernel_print("PRESS A TO CONTINUE" , 2, 0X0A);
    while (1)
    {
        unsigned char scancode = inb(0x60);

        if (scancode == 0x1E)
        {
            kernel_print("KEY PRESSED", 3, 0X01);
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