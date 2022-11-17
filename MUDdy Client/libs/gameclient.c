#include "ui.h"
//#include "network.h"
//#include "game.h"


// Initialize game

// Present main menu

// If multiplayer game then connect to server

    // Present waiting screen

    // Present game once all players have joined

// Game behaviour

    // All client messages go to server for processing

    // Client facilitates transmitting data and presenting received data

    // Server handles actual game behaviour
    
    // Game client should be asynchronus


int main ()
{
    init_ui();

    game_screen();

    cleanup();
}