
#include "gfx.h"

// Expected result:
// Bouncing around the screen, leaving behind a trail of pixels
void bounce()
{
	NEW_IMAGE(frogge_img, 5, 5, image_road_middle);

	int8_t speed_x = 1;
	int8_t speed_y = 1;

	while (1)
	{
		draw_image(&frogge_img);

		speed_x *= 1 - 2 * (frogge_img.position.x < 5 || frogge_img.position.x >= 215);
		speed_y *= 1 - 2 * (frogge_img.position.y < 5 || frogge_img.position.y >= 295);
		frogge_img.position.x += speed_x;
		frogge_img.position.y += speed_y;
	}
}

// Expected result:
// A sprite instantly teleporting between two places, without leaving behind debris
void sprite()
{
	NEW_IMAGE(frogge, 100, 120, image_frogge);

	Vector2 one = {100, 120};
	Vector2 two = {40, 80};

	while (1)
	{
		move_image(&frogge, &one);
		_delay_ms(250);
		move_image(&frogge, &two);
		_delay_ms(250);
	}
}
