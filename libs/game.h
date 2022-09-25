#include "ui.h"
#include "network.h"

// ********************************************** GLOBALS *********************************************** \\ 



// **************************************** Function Definitions **************************************** \\ 

// Start game
void run_game()
{

    // init_ui();
    
    // switch(main_menu())
    // {
    //     case 1:
    //         // Start game
    //         start_game();
    //         // Get connection details for server
    //          // Attempt to connect to server

    //          // If fail then abort 

    //          // If success set state according to server
    //          // Waiting (display waiting screen)
    //          // Or
    //          // Play game (start game)
    //         break;
    //     case 2:
    //         // Open settings menu
    //         display_settings_menu();
    //         break;
    //     case 3:
    //         // Quit
    //         end_game();
    //         return;
    //         break;

    // }
    

    init_ui();
    

   
}

void start_game()
{

}

void display_settings_menu()
{

}

void end_game()
{
    cleanup();
}

int housekeeping()
{
    // Check for game files and folders

    // Create them if they do not exist
}