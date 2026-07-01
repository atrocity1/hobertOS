
const unsigned long VGA_COLOR = 0xB8000;

class Food{
    public:
        int x;
        int y;
        void init(){
            x = 15;
            y = 12;
        }           
        void drawn(){
            char *vga = (char*) VGA_COLOR;
            int index = (y * 80 + x) * 2;

            vga[index] = '*';
            vga[index + 1] = 0x04;            
        }

        
};

class Snake {
    public:
        int x[100];
        int y[100];
        int len;
        int direction;
        int foods;
        void init(){
            len = 3;
            direction = 3;
            x[0] = 10;
            y[0] = 10;
            x[1] = 9;
            y[1] = 10;
            x[2] = 8;
            y[2] = 10;
        }
        void change_direction(int new_dir){
            if (direction != new_dir)
            {
                direction = new_dir;
            }
        }
        void move(){
            for (int i = len - 1; i > 0; i--)
            {
                x[i] = x[i - 1];
                y[i] = y[i - 1];
            }

                if (direction == 0){
                    y[0]--;
                }
                else if(direction == 1){
                    y[0]++;
                }
                else if (direction == 2){
                    x[0]--;
                }
                else if (direction == 3)
                {
                    x[0]++;
                }         
        }
        void eat(){
            for (int i = 0; i < foods; i++)
            {
                len++;
            }  
        }
        bool check_snake_colision(){
            for (int i = 1; i < len; i++)
            {
                if (x[0] == x[i] && y[0] == y[i]){
                    return true;
                }
                
            }
            return false;
            
        }
};

Snake snake;
Food food;


void clean_kernel_game_screen() {
    char *vga_color = (char*) VGA_COLOR;
    for (int y = 0; y < 25; y++) // O y do jogo
    {
        for (int x = 0; x < 80; x++) // o X
        {
            int index = (y * 80 + x) * 2;
            vga_color[index] = ' ';
            vga_color[index + 1] = 0x07;
            
        }
    }
    
}

extern "C" unsigned char inb(unsigned short port);

void key_check(){
    unsigned char scancode = inb(0x60);
    if (scancode == 0x11)
    {
        if (snake.direction != 1)
        {
            snake.change_direction(0);
        }
    }
    else if (scancode == 0x1F) {
        if (snake.direction != 0) snake.change_direction(1);
    }
    else if (scancode == 0x1E) {
        if (snake.direction != 3) snake.change_direction(2);
    }
    else if (scancode == 0x20) { 
        if (snake.direction != 2) snake.change_direction(3);
    }
    
}
void render_game_kernel(){
    clean_kernel_game_screen();
    food.drawn();

    char *vga_color = (char*) VGA_COLOR;
    for (int i = 0; i < snake.len; i++)
    {
        int index = (snake.y[i] * 80 + snake.x[i]) * 2;
        if (i == 0)
        {
            vga_color[index];
            vga_color[index + 1] = 0x0A;

        } else {
            vga_color[index] = '#';
            vga_color[index + 1] = 0x02;
        }
    }
}

extern "C" void start_snake_game(){
    snake.init();
    food.init();

    while (1)
    {
        for (int i = 0; i < 400; i++) {
            key_check(); // so pra esse monte de bosta nao ficar todo lagado
            for (volatile int d = 0; d < 100000; d++);
        }
        snake.move(); 
        if (snake.x[0] == food.x && snake.y[0] == food.y) {
            snake.len++;
            food.x = (food.x * 7 + 13) % 70 + 5;
            food.y = (food.y * 3 + 7) % 20 + 2;
        }

        if (snake.x[0] == food.x && snake.y[0] == food.y)
        {
            snake.len++;

            food.x = (food.x * 7 + 13) % 70 + 5;
            food.y = (food.y * 3 + 7) % 20 + 2;
        }
        
        

        if (snake.check_snake_colision())
        {
            snake.init();
            food.init();
            continue;
        }

        render_game_kernel();  
        
        
    }
    

}


