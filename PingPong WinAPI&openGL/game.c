#include "game.h"
 
#define PADDLE_LEFT		0
#define PADDLE_RIGHT	1
#define BALL			2
#define WALL_TOP		3
#define WALL_BOTTOM		4

#define BOARD_WIDTH		1000
#define BOARD_HEIGHT	600

#define DEBUG 1

#define BALL_SPEED_Y	5

static Color4_t col_white = { 1.0,1.0,1.0,1.0 };
static Color4_t col_red = { 1.0,0.0,0.0,0.0 };

void game_init(Game* game)
{
	if (game == NULL)return;
	
	game->title = "Gierka";
	game->maxFps = 60;
	game->lastFrame = 0;

	int window_width = 1000;
	int window_height = 800;

	long paddle_width = 20;
	long paddle_height = 150;

	long board_height = BOARD_HEIGHT;
	long board_width = BOARD_WIDTH;

	window* wnd = createWindow(window_width, window_height, game->title);
	if (wnd == NULL)
	{
		return -1;
	}
	game->window = wnd;
	game->userPoints = 0;
	game->computerPoints = 0;
	game->gameObjectsCount = 5;
	game->gameObjects = malloc(game->gameObjectsCount * sizeof(gameObjectRect));


	//ball and paddles
	game->gameObjects[0] = createGameObject_rect(10.0f, board_height / 2 - paddle_height / 2, paddle_width, paddle_height, 0.0f, &col_white, NULL);
	game->gameObjects[1] = createGameObject_rect(board_width - paddle_width - 26.0f, board_height / 2 - paddle_height / 2,paddle_width,paddle_height,0.0f, &col_white, NULL);
	game->gameObjects[2] = createGameObject_circle(board_width / 2, board_height / 2, paddle_width / 2, 0, &col_white, NULL);
	
	//Top and bottom walls
	game->gameObjects[3] = createGameObject_rect(0.0f, 0.0f, board_width, 10, 0.0f, &col_white, NULL);
	game->gameObjects[4] = createGameObject_rect(0.0f, board_height - 10, board_width, 10, 0.0f, &col_white, NULL);


	//Set ball speed
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[2];
	ball->speedX = 10;
	ball->speedY = -BALL_SPEED_Y;

}

void game_udpate(Game* game)
{
	if (game == NULL)return;

	gameObjectCircle *ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddle1 = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	gameObjectRect* paddle2 = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];
	gameObjectRect* wallTop = (gameObjectRect*)game->gameObjects[WALL_TOP];
	gameObjectRect* wallBottom = (gameObjectRect*)game->gameObjects[WALL_BOTTOM];
	ball->super->x += ball->speedX;
	ball->super->y += ball->speedY;

	int colBallPaddleL = checkBallCollision(ball, paddle1);
	int colBallPaddleR = checkBallCollision(ball, paddle2);
	if (colBallPaddleL || colBallPaddleR)
	{
		ball->speedX *= -1;
		int yDir = ball->speedY > 0 ? 1 : -1;
		if (colBallPaddleL == 1 || colBallPaddleR == 1)ball->speedY = ball->speedY - 2;
		else if (colBallPaddleL == 2 || colBallPaddleR == 2)ball->speedY /= 1;
		else if (colBallPaddleL == 3 || colBallPaddleR == 3)ball->speedY = ball->speedY + 2;
	}
	if (checkBallCollision(ball, wallTop) || checkBallCollision(ball, wallBottom))ball->speedY *= -1;
	computerMove(game);
	keyboardEvents(game);
	checkPoint(game);
	
}

void game_draw(Game* game)
{
	if (game == NULL)return;

	startDraw(game->window);

	for (int i = 0; i < game->gameObjectsCount; i++)
	{
		gameObjectRect* obj_tmp = (gameObjectRect*)game->gameObjects[i];
		
		//printf("OBJECT TYPE: %d\n", obj_tmp->type);
		switch (obj_tmp->super->type)
		{
		case GO_RECT:
		{
			gameObjectRect* obj = (gameObjectRect*)game->gameObjects[i];
			if(obj->txt==NULL)
				drawRect(&((rect){ obj->super->x, obj->super->y, obj->w, obj->h }), obj->super->color, NULL, NULL, obj->depth, game->window);
			else
				drawRect(&((rect) { obj->super->x, obj->super->y, obj->w, obj->h }), obj->super->color, &((rect) { obj->super->x, obj->super->y, obj->w, obj->h }), obj->txt, obj->depth, game->window);
			break;
		}
		case GO_CIRCLE:
		{
			gameObjectCircle* obj = (gameObjectCircle*)game->gameObjects[i];
			drawCircle(obj->super->x, obj->super->y, obj->r, 360, obj->super->color, obj->depth, game->window);
			break;
		}
		default: 
			break;
		}
	}

	//drawRect(0, game->window->height - 20 - game->window->offsetY, game->window->width, 10, NULL, Color4f(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, game->window);

	endDraw(game->window);
}

void game_destruct(Game* game)
{
	printf("window closed");
	freeGameObjects(game->gameObjects, game->gameObjectsCount);
	free(game->window);
}

int checkBallCollision(gameObjectCircle* obj1, gameObjectRect* obj2)
{
	if (
		obj1->super->x + obj1->r	> obj2->super->x &&
		obj1->super->x - obj1->r	<	obj2->super->x + obj2->w &&
		obj1->super->y + obj1->r	>	obj2->super->y &&
		obj1->super->y - obj1->r	< obj2->super->y + obj2->h
		)
	{
		if (obj2->super->id == PADDLE_LEFT)obj1->super->x = obj2->super->x + obj2->w + 1;
		else if (obj2->super->id == PADDLE_RIGHT)obj1->super->x = obj2->super->x - obj1->r - 1;

		if (obj1->super->y < obj2->super->y + (float)obj2->h * 1.0/3.0) return 1;
		if (obj1->super->y < obj2->super->y + (float)obj2->h * 2.0/3.0)	return 2;
		return 3;
	}
	return 0;
}

void checkPoint(Game* game)
{
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddleLeft = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	gameObjectRect* paddleRight = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];

	if (ball->super->x - ball->r < paddleLeft->super->x)
	{
		ball->super->x = game->window->width / 2;
		ball->super->y = game->window->height / 2;
		ball->speedX = -10;
		ball->speedY = 5;
		game->computerPoints++;
		if (DEBUG)printf("USER %d : %d COMPUTER\n", game->userPoints, game->computerPoints);
	}
	else if (ball->super->x + ball->r > paddleRight->super->x + paddleRight->w)
	{
		ball->super->x = game->window->width / 2;
		ball->super->y = game->window->height / 2;
		game->userPoints++;
		ball->speedX = 10;
		ball->speedY = -5;
		if (DEBUG)printf("USER %d : %d COMPUTER\n", game->userPoints, game->computerPoints);

	}
}


int keyboardEvents(Game* game)
{
	gameObjectRect* paddleLeft = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	if (game->window->keysPressed[VK_UP] && paddleLeft->super->y > 0)paddleLeft->super->y -= 5;
	if (game->window->keysPressed[VK_DOWN] && paddleLeft->super->y + paddleLeft->h < BOARD_HEIGHT)paddleLeft->super->y += 5;
}

void computerMove(Game* game)
{
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddleRight = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];

	if (ball->speedX > 0 && ball->super->x > BOARD_WIDTH / 2)
	{
		if (ball->super->y > paddleRight->super->y + paddleRight->h && paddleRight->super->y + paddleRight->h < BOARD_HEIGHT)paddleRight->super->y+=2;
		else if(paddleRight->super->y > 0) paddleRight->super->y-=2;
	}

	if (ball->speedX > 0 && ball->super->x > BOARD_WIDTH * (2.0/3.0))
	{
		if (ball->super->y > paddleRight->super->y + paddleRight->h && paddleRight->super->y + paddleRight->h < BOARD_HEIGHT)paddleRight->super->y += 5;
		else if (paddleRight->super->y > 0) paddleRight->super->y -= 5;
	}

}