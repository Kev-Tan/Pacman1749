#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

#include "scene_settings.h"


static Button exitButton;
static Button addMusicVolume;
static Button decreaseMusicVolume;
static Button addEffectVolume;
static Button decreaseEffectVolume;

			
extern ALLEGRO_SAMPLE* themeMusic;
extern ALLEGRO_SAMPLE* PACMAN_MOVESOUND;
extern ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND;
extern ALLEGRO_FONT* menuFont;
extern int fontSize;
extern float music_volume;
extern float effect_volume;
extern bool gameDone;



// The only function that is shared across files.


static void init() {
	exitButton = button_create(730, 20, 50, 50, "Assets/exit-game.png","Assets/exit-game-after.png" );
	addMusicVolume = button_create(650, 180, 50, 50, "Assets/increase-before.png", "Assets/increase-after.png");
	decreaseMusicVolume = button_create(550, 180, 50, 50, "Assets/decrease-before.png", "Assets/decrease-after.png");

	addEffectVolume = button_create(650, 280, 50, 50, "Assets/increase-before.png", "Assets/increase-after.png");
	decreaseEffectVolume = button_create(550, 280, 50, 50, "Assets/decrease-before.png", "Assets/decrease-after.png");
}

static void draw(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(exitButton);
	drawButton(addMusicVolume);
	drawButton(decreaseMusicVolume);
	drawButton(addEffectVolume);
	drawButton(decreaseEffectVolume);

	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2.0,
		SCREEN_H  -750,
		ALLEGRO_ALIGN_CENTER,
		"Settings:"
	);
		
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 5.0,
		SCREEN_H -600,
		ALLEGRO_ALIGN_CENTER,
		"Music Volume:"
	);


	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 5.0,
		SCREEN_H - 500,
		ALLEGRO_ALIGN_CENTER,
		"Effect Volume:"
	);

	al_draw_textf(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		SCREEN_H - 600,
		ALLEGRO_ALIGN_CENTER,
		"%f",
		music_volume
	);

	al_draw_textf(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		SCREEN_H - 500,
		ALLEGRO_ALIGN_CENTER,
		"%f",
		effect_volume
	);
}

static void on_mouse_down() {
	printf("INSIDE MOUSE DOWN\n");

	if (exitButton.hovered == true) {
		game_change_scene(scene_menu_create());
	}			

	//MUSIC VOLUME
	if (addMusicVolume.hovered == true) {
		if (music_volume < 10) {
			music_volume += 0.5;
		}
	}

	if (decreaseMusicVolume.hovered == true) {
		if (music_volume > 0) {
			music_volume-=0.5;
		}
	}

	//EFFECT VOLUME 
	if (addEffectVolume.hovered == true) {
		if (effect_volume < 10) {
			effect_volume += 0.5;
		}
	}

	if (decreaseEffectVolume.hovered == true) {
		if (effect_volume > 0) {
			effect_volume -= 0.5;
		}
	}

}																		 

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) { 
		exitButton.hovered = buttonHover(exitButton, mouse_x, mouse_y);
		addMusicVolume.hovered = buttonHover(addMusicVolume, mouse_x, mouse_y);
		decreaseMusicVolume.hovered = buttonHover(decreaseMusicVolume, mouse_x, mouse_y);
		addEffectVolume.hovered = buttonHover(addEffectVolume, mouse_x, mouse_y);
		decreaseEffectVolume.hovered = buttonHover(decreaseEffectVolume, mouse_x, mouse_y);
}



Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	//scene.destroy = &destroy;			//DESTROY THIS LATER
	scene.on_mouse_move = &on_mouse_move;		//Create this later
	scene.on_mouse_down = &on_mouse_down;	
	scene.draw = &draw;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}