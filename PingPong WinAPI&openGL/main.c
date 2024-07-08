#include <stdio.h> 
#include "window.h"
#include "drawing.h"
#include "utils.h"

#include "game.h"
#include "font.h" 

int main()
{

	Game *game = malloc(sizeof(Game));
	if (game == null)return -1;
	game_init(game);

	

	while (isWindowOpened(game->window))
	{ 
		updateWindow();
		game_udpate(game);
		game_draw(game); 
	}

	game_destruct(game);

	return 0;
}