// Wrapper for the ncurses TUI

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG TRUE

// ******************************************* STATIC GLOBALS ******************************************* \\ 
//static WINDOW* menuwin;
static WINDOW* chatwin;
static WINDOW* inputwin;
static WINDOW* statuswin;

static int term_height, term_width;
static int half_height, half_width;

struct Connection_Info
{
    char _ipv4addr[64];
    char _password[64];
};

void draw_main_menu(WINDOW* currentwin, int selected_option);
char* get_user_input(WINDOW* current_win, char* dest_buf, int max_buf_size, int start_y, int start_x, int margin);
void draw_game_info(WINDOW* currentwin, int height, int width);

// **************************************** Function Definitions **************************************** \\ 

// Initialize ncurses with optional settings
bool init_ui()
{
    // Basic init sequence
    initscr();
    clear();
    noecho();
    cbreak();

    // Get terminal size
    getmaxyx(stdscr, term_height, term_width);
    half_height = (term_height / 2);
    half_width = (term_width / 2);

    if (DEBUG)
    {
        mvprintw(1, 0, "Max width: %d", term_width);
        mvprintw(2, 0, "Max height: %d", term_height);
        mvprintw(3, 0, "Half width: %d", half_width);
        mvprintw(4, 0, "Half height: %d", half_height);
        mvprintw(5, 0, "COLS: %d", COLS);
        mvprintw(6, 0, "LINES: %d", LINES);
    }
    // Determine if terminal supports color

}

// Start main menu
int main_menu()
{
    WINDOW* menuwin;
    menuwin = newwin(half_height, half_width, half_height / 2, half_width / 2);
    keypad(menuwin, TRUE);
    int option = 1;
    uint16_t ch;

    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
    draw_main_menu(menuwin, option);
    while (true)
    {
        ch = wgetch(menuwin);
        switch(ch)
        {
            case 1:
                option = 1;
                break;
            case 2:
                option = 2;
                break;
            case 3:
                option = 3;
                break;
            case KEY_UP:
				if(option == 1)
					option = 3;
				else
					--option;
				break;
			case KEY_DOWN:
				if(option == 3)
					option = 1;
				else 
					++option;
				break;
            case KEY_ENTER:
                return option;
                break;
            case 10:
                return option;
                break;
        }
        draw_main_menu(menuwin, option);
    }

    delwin(menuwin);
}

// Draw menu options
void draw_main_menu(WINDOW* currentwin, int selected_option)
{
    char*  menu_options [] =
    {
    "1. Play Game",
    "2. Settings",
    "3. Exit"
    };

    int n_options = sizeof(menu_options) / sizeof(char*);
    int starty = half_height - n_options;
    int startx = half_width;

    box(currentwin, 0, 0);

    int i;
    for(i = 0; i < n_options; i++)
    {
        if (i + 1 == selected_option)
        {
            wattron(currentwin, A_REVERSE);
            mvwprintw(currentwin, 2 + i, 2, "%s", menu_options[i]);
            wattroff(currentwin, A_REVERSE);
        }
        else
        {
            mvwprintw(currentwin, 2 + i, 2, "%s", menu_options[i]);
        }
    }
    wrefresh(currentwin);

}



struct Connection_Info game_info()
{
    // Display screen to get connection info etc. before starting game
    struct Connection_Info connection_info;
    WINDOW* childwin;
    char buf[512] = {0}; 

    childwin = newwin(half_height, half_width, half_height / 2, half_width / 2);
    draw_game_info(childwin, half_width, half_height);

    get_user_input(childwin, buf, 255, half_height / 4, half_width / 4, -1);

    mvprintw(0, 0, "You typed: %s", buf);

    getch();

    delwin(childwin);
    return connection_info;
}

void draw_game_info(WINDOW* currentwin, int height, int width)
{
    int max_x, max_y;
    getmaxyx(currentwin, max_y, max_x);
    box(currentwin, 0, 0);
    mvwprintw(currentwin, 0, 0, "%d", max_x);
    mvwprintw(currentwin, 1, 0, "%d", max_y);
    mvwprintw(currentwin, max_y * .10f, (max_x / 2) - 5, "Hallo");



}

// Start waiting_screen
void waiting_screen()
{

}

// Start game screen
void game_screen()
{
    //
}

// Insert text into the chat window
int draw_to_chatwin()
{

}

// Insert text into the input window
int draw_to_inputwin()
{

}

// Update the status window
int update_statuswin()
{

}


void cleanup()
{
    // delwin(menuwin);
    // delwin(chatwin);
    // delwin(inputwin);
    // delwin(statuswin);

    endwin();
}

// if char is an allowed character print and advance cursor
char* get_user_input(WINDOW* current_win, char* dest_buf, int max_buf_size, int start_y, int start_x, int margin)
{
    int max_x = 0;
    int xpos, ypos;
    char input_buf[max_buf_size + 1];

    xpos = start_x;
    ypos = start_y;

    if (margin > 0)
    {
        max_x = start_x + margin;
    }

    // Set cursor to defined position
    wmove(current_win, start_y, start_x);

    int counter = 0;
    while(true)
    {
        uint16_t ch = wgetch(current_win);
        if (counter < max_buf_size)
        {
            // get char, print to screen, and add to buffer
            switch (ch)
            {
                case 10:
                    input_buf[counter + 1] = '\0';
                    return strcpy(dest_buf, input_buf);
                case KEY_BACKSPACE:
                    if (counter > 0)
                    {
                        --counter;
                        mvwaddch(current_win, ypos, xpos + counter, ' ');
                        wmove(current_win, ypos, xpos + counter);
                    }
                    break;
                case 127:
                    if (counter > 0)
                    {
                        --counter;
                        mvwaddch(current_win, ypos, xpos + counter, ' ');
                        wmove(current_win, ypos, xpos + counter);
                    }
                    break;
                default:
                    waddch(current_win, ch);
                    input_buf[counter] = ch;
                    ++counter;
                    break;
            }
        }
        else
        {
            // do nothing except for backspace and carriage return
            switch (ch)
            {
                case 10:
                    input_buf[counter + 1] = '\0';
                    return strcpy(dest_buf, input_buf);
                case KEY_BACKSPACE:
                    --counter;
                    mvwaddch(current_win, ypos, xpos + counter, ' ');
                    wmove(current_win, ypos, xpos + counter);
                    break;
                case 127:
                    --counter;
                    mvwaddch(current_win, ypos, xpos + counter, ' ');
                    wmove(current_win, ypos, xpos + counter);
                    break;
                default:
                    continue;
                    break;
            }
        }
    }
    return strcpy(dest_buf, input_buf);
    
}

void highlight_field(WINDOW* current_win, int field_length, int start_x, int start_y)
{
    
}