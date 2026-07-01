
char command_buffer[100];
int command_len = 0;
char folders[10][15]; // cria um espaço pra guardar as pasta
unsigned int folder_count = 0; // contador so pra saber quantas pastas tem
int position_byte = 480; //pula pra terceira linha onde vc quer digitar eh basicamente o byte onde quer escrever
extern unsigned char inb(unsigned short port);
const char keyboard_map[90] = {
    [0x1E] = 'A',
    [0x30] = 'B',
    [0x2E] = 'C',
    [0x20] = 'D',
    [0X12] = 'E',
    [0x21] = 'F',
    [0x22] = 'G',
    [0x23] = 'H',
    [0x17] = 'I',
    [0x24] = 'J',
    [0x25] = 'K',
    [0x26] = 'L',
    [0x32] = 'M',
    [0x31] = 'N',
    [0x18] = 'O',
    [0x19] = 'P',
    [0x10] = 'Q',
    [0x13] = 'R',
    [0x1F] = 'S',
    [0x14] = 'T',
    [0x16] = 'U',
    [0x2F] = 'V',
    [0x11] = 'W',
    [0x2D] = 'X',
    [0x15] = 'Y',
    [0x2C] = 'Z'
};

unsigned char last_key = 0;
void kernel_print(const char*text, int line, int color);
void kernel_clear();
void kernel_digit_mode();
void kernel_input_keyboard();
void strcpy(char *destiny, const char *origem);
void kernel_credits();
void kernel_show_menu();
int strcmp(const char *str1, const char *str2);

void kernel_main(){
    kernel_clear();
    char * vga_color = (char*)0xB8000;
    kernel_show_menu();
    while (1)
    {
        unsigned char scancode = inb(0x60);
        if (scancode != last_key && scancode != 0)
        {
            if (scancode == 0x1E)
            {
                kernel_digit_mode();
            }
            else if (scancode == 0x30)
            {
                kernel_credits();
                kernel_show_menu();
            }
            last_key = scancode;

            if(scancode == 0){
                last_key = 0;
            }
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


        if (scancode != 0 && scancode != last_key)
        {
            if (scancode == 0x1C)
            {
                command_buffer[command_len] = '\0';
                int clear_screen = 0;
                if (strcmp(command_buffer, "CLEAR") == 1)
                {
                    kernel_clear();
                    position_byte = 0;
                    clear_screen = 1; 
                }
                else if (strcmp(command_buffer, "HELP") == 1)
                {

                    kernel_print("SOON...", 2, vga_color[scancode]);
                }
                else if (strcmp(command_buffer, "MKDIR") == 1){
                    if (folder_count < 10)
                    {
                        strcpy(folders[folder_count], "NOVA PASTAR");
                        
                    }
                    else{
                        int line = (position_byte / 160) + 1;
                        kernel_print("Memory error to create folder", line, 0x02);
                    }
                }
                else if(strcmp(command_buffer, "LS") == 1){
                    int line = (position_byte / 160) + 1;
                    for (int i = 0; i < folder_count; i++)
                    {
                        kernel_print(folders[i], line, 0x07);
                        line++;
                    }
                    
                }
                command_len = 0;
                if (clear_screen)
                {
                    
                    position_byte = ((position_byte / 160) + 1) * 160;    
                } 
            }
            else if (scancode == 0x39)
            {
                if(command_len < 99){
                    command_buffer[command_len] = ' '; // PRA GUARDAR O ESPAÇO TAMBÉM!
                    command_len++;
                    position_byte += 2;
                } 
            }
            else if (scancode == 0x0E)
            {
                if (position_byte > 480)
                {
                    position_byte -= 2;
                    vga_color[position_byte] = ' ';
                    vga_color[position_byte + 1] = 0x07;
                    if (command_len)
                    {
                        command_len--;
                    }
                      
                }
            }
            else if (scancode < 60 && keyboard_map[scancode])
            {
                if (command_len < 99)
                {
                    command_buffer[command_len] = keyboard_map[scancode];
                    command_len++;
                    vga_color[position_byte] = keyboard_map[scancode];
                    vga_color[position_byte + 1] = 0x0A;

                    position_byte += 2; //So pra letra mudar de lugar e nao ficar mudando
                }
            }
            last_key = scancode;    
        }
        if (scancode == 0) //SO PRA NAO FICAR MUDANDO A LETRA PRA NUMERO
        {
            last_key = 0;
        }
    }
}

void kernel_credits(){
    kernel_clear();
    kernel_print("Coding: Hoberte, Assembly: Hoberte", 1, 0x01);
    kernel_print("PRESS A TO BACK TO MENU", 2, 0x01);

    while (1)
    {
        unsigned char scancode = inb(0x60);
        if (scancode != last_key && scancode != 0)
        {
            if (scancode == 0x1E)
            {
                return;
            }   
            last_key = scancode;
        }
        if (scancode == 0)
        {
            last_key = 0;
        }
        
        

    }
    

    
}

void kernel_show_menu(){
    kernel_clear();
    kernel_print("WELCOME TO HOBERT OS", 1, 0x01);
    kernel_print("MADED BY Hoberte", 2, 0X0A);
    kernel_print("PRESS A TO DIGIT MODE" , 3, 0X0A);
    kernel_print("PRESS B TO SEE CREDITS", 4, 0x0A);
}

int strcmp(const char *str1, const char *str2){ //PARA CHECKAR COMANDOS

    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
        i++;
    }

    if (str1[i] == str2[i])
    {
        return 1;
    }
    else{
        return 0;
    }
    
    
}

void strcpy(char *destiny, const char *origem){
    int i = 0;
    while (origem[i != '\0'])
    {
        destiny[i] = origem[i];
        i++;
        destiny[i] = '\0';
    }
    
}

