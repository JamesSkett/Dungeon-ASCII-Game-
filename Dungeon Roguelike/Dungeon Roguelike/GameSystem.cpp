#include "GameSystem.h"
#include "Renderer.h"
#include "Tile.h"

#include <conio.h>

//Constructor sets up the game
GameSystem::GameSystem(std::string levelFileName)
{
	renderer = new Renderer();

	m_timer = al_create_timer(1.0 / 30.0);
	m_queue = al_create_event_queue();

	tile = new Tile(0, 0, true, "turtle.jpg");

	//_mainMenu.displayMenu();

	//_player.init(3, 0, 0);

	//_level->load(levelFileName, _player);
}

GameSystem::~GameSystem()
{
	al_destroy_timer(m_timer);
	al_destroy_event_queue(m_queue);

	if (_level != nullptr) 	
	{
		delete _level;		
		_level = nullptr;	
	}

}

//---------------------------------------------------------------------------
//main game loop
void GameSystem::playGame()
{
    al_register_event_source(m_queue, al_get_keyboard_event_source());
    al_register_event_source(m_queue, al_get_display_event_source(Renderer::disp));
    al_register_event_source(m_queue, al_get_timer_event_source(m_timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(m_timer);
    while (1)
    {
        al_wait_for_event(m_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if (redraw && al_is_event_queue_empty(m_queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

			tile->Draw();

            al_flip_display();

            redraw = false;
        }
    }
	//tells the player they are dead after all lives lost.
	//deathScreen();
	//returns to main function and game ends
}

//---------------------------------------------------------------------------
//gets user input
void GameSystem::playerMove()
{
	char input;
	printf("\n\nEnter a move command (W/A/S/D), press 'E' to dig hole or Press 'Q' to quit: ");
	input = _getch();

	_level->movePlayer(input, _player);
}

//-----------------------------------------------------------------------------
//tells the player they died and prints out the player properties
void GameSystem::deathScreen()
{
	system("CLS");
	printf("           YOU DIED!\n\n");

	_player.printProperties();
	_getch();
}


