#define VGA_COLOR = 0xB8000;
    
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
            for (int i = len - 1; i < len; i++)
            {
                
            }
        }
        void eat(){
            for (int i = 0; i < foods; i++)
            {
                len++;
            }  
        }
};


void clean_kernel_game_screen() {
    for (int y = 0; y < 25; y++) // O y do jogo
    {
        for (int x = 0; x < 80; x++) // o X
        {
            
        }
    }
    
}
void render_game_kernel(){
    clean_kernel_game_screen();
}

void drawn_food(){
    char *food_x = (char*) 0x04;
}