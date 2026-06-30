int position_byte = 480; // pula pra terceira linha onde vc quer digitar eh basicamente o byte onde quer escrever

extern unsigned char inb(unsigned short port);

const char keyboard_map[50] = {
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
    [0x27] = 'M',
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
    [0x2C] = 'Z'};

void kernel_print(const char *text, int color);
void kernel_clear();
void kernel_digit_mode();
void kernel_input_keyboard();
void kernel_credits();
void kernel_show_menu();

const int VGA_ADDR = 0xB8000;
static unsigned char last_key = 0;
static int LINE = 1;

void kernel_main()
{
    kernel_clear();
    // variavel sem uso
    // volatile char *vga_color = (char *)VGA_ADDR;
    kernel_show_menu();
    while (1)
    {
        unsigned char scancode = inb(0x60);
        // impede repetição de escrita e mantém o loop
        if (scancode != last_key && scancode != 0)
        {
            if (scancode == 0x1E) // A
            {
                kernel_digit_mode();
                continue;
            }
            else if (scancode == 0x30) // B
            {
                kernel_credits();
                kernel_show_menu();
            }

            last_key = scancode;
            if (scancode == 0)
                last_key = 0;
        }
    }
}

void kernel_print(const char *text, int color)
{
    volatile char *vga_color = (char *)VGA_ADDR;
    int position = LINE++ * 160;
    for (int i = 0; text[i] != '\0'; i++)
    {
        vga_color[position] = text[i];
        vga_color[position + 1] = color;
        position += 2;
    }
}

void kernel_clear()
{
    LINE = 0;
    volatile char *vga_color = (char *)VGA_ADDR;
    for (int i = 0; i < 4000; i++)
    {
        if (i % 2 == 0)
            vga_color[i] = ' ';
        else
            vga_color[i] = 0x07; // cor verde
    }
}

void kernel_digit_mode()
{
    kernel_clear();
    while (1)
    {
        volatile char *vga_color = (char *)VGA_ADDR;
        unsigned char scancode = inb(0x60);

        if (scancode != 0 && scancode != last_key)
        {
            if (scancode == 0x39) // espaço em branco?
            {
                position_byte += 2;
            }
            else if (scancode == 0x0E)
            {
                if (position_byte > 480)
                {
                    position_byte -= 2;
                    vga_color[position_byte] = ' ';
                    vga_color[position_byte + 1] = 0x07;
                }
            }

            if (scancode < 60 && keyboard_map[scancode])
            {
                vga_color[position_byte] = keyboard_map[scancode];
                vga_color[position_byte + 1] = 0x0A;
                position_byte += 2; // So pra letra mudar de lugar e nao ficar mudando
            }

            last_key = scancode;
        }

        if (scancode == 0) // SO PRA NAO FICAR MUDANDO A LETRA PRA NUMERO
        {
            last_key = 0;
        }
    }
}

void kernel_credits()
{
    kernel_clear();
    kernel_print("Coding: Hoberte, Assembly: Hoberte", 0x01);
    kernel_print("PRESS A TO BACK TO MENU", 0x01);

    while (1)
    {
        unsigned char scancode = inb(0x60);
        if (scancode != last_key && scancode != 0)
        {
            if (scancode == 0x1E)
                return;
            last_key = scancode;
        }
        if (scancode == 0)
            last_key = 0;
    }
}

void kernel_show_menu()
{
    kernel_clear();
    kernel_print("WELCOME TO HOBERT OS", 0x01);
    kernel_print("MADED BY Hoberte", 0X0A);
    kernel_print("PRESS A TO DIGIT MODE", 0X0A);
    kernel_print("PRESS B TO SEE CREDITS", 0x0A);
}
