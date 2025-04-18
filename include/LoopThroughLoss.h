/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoopThroughLoss.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:08:40 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/16 18:12:27 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOOPTHROUGHLOSS_H
# define LOOPTHROUGHLOSS_H

# include "libft.h"
# include "raylib.h"
# include "raymath.h"
# include "assets_path.h"

# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <stdint.h>
# include <string.h>

# define FLOOR_COLOR_DL			0x7BC9C0FF
# define CEILING_COLOR_DL		0xFFFFFFFF

# define FLOOR_COLOR_AL			0x851414FF
# define CEILING_COLOR_AL		0x615454FF

# define FLOOR_COLOR_BL			0x758C69FF
# define CEILING_COLOR_BL		0x939990FF

# define FLOOR_COLOR_DEPL		0x6E7F80FF
# define CEILING_COLOR_DEPL		0xFFFFFFFF

# define FLOOR_COLOR_ACCL		0xA3D1CBFF
# define CEILING_COLOR_ACCL		0xFFFFFFFF

# define SUCCESS	0
# define FAILURE	1

# define FOV				0.66
// fov_threshold = cos(FOV / 2.0);
# define FOV_THRESHOLD		0.943956
# define INFINITY_DIST		1e6

# define WIN_NAME	"LoopThroughLoss"
# define WIN_W		1200
# define WIN_H		900

# define TEX_W		1024
# define TEX_H		1024

# define DEAD_ZONE	1.0

typedef enum e_char_value
{
	FREE_SPACE,
	WALL,
	DOOR,
	CONF_DIR,
	FURNITURE,
	EMPTY
}	t_char_value;

typedef struct s_map
{
	int			fd;
	char		*filename;
	char		**file_content;
	char		**map_layout;
	t_point		size;
	int			player_count;
	int			**matrix;
	int			floor_color;
	int			ceiling_color;
}	t_map;

typedef struct s_ray
{
	t_dpoint	dir;			// Ray direction
	t_point		map;			// Map square coordinates
	t_dpoint	delta_dist;		// Distance to next side in x and y
	t_dpoint	side_dist;		// Initial distance to next x or y side
	t_point		step_dir;		// Step direction in x and y (+1 or -1)
	int			hit;			// 1 if a wall was hit
	int			side;			// 0 for vertical side, 1 for horizontal side
	double		perp_w_dist;	// Perpendicular distance from player to wall
	int			line_height;	// Height of wall line to draw
	int			draw_start;		// Starting pixel for wall line
	int			draw_end;		// Ending pixel for wall line
	double		wall_x;			// Exact wall hit position
	t_point		tex;			// Texture coordinates 
	double		step;			// How much to increase texture coordinate
	double		tex_pos;		// Initial texture coordinate position
}	t_ray;

typedef struct s_texture
{
	Texture2D	texture;
	Vector2		size;
}	t_texture;

typedef struct s_sprite_draw
{
	t_dpoint	relative_position;		// Sprite position relative to player
	double		inverse_determinant;	// Inverse of the det of the camera mat
	t_dpoint	transform;				// Sprite position in camera space
	int			screen_x;				// X coordinate of sprite center screen
	int			height;					// Calculated sprite height on screen
	int			width;					// Calculated sprite width on screen
	t_point		draw_start;				// (top-left) of sprite bounding box
	t_point		draw_end;				// (bott-right) of sprite bounding box
	int			current_frame;			// Chosen animation frame
	t_texture	*texture;				// Pointer to the sprite texture
	int			stripe_x;				// Current vert stripe in screen space
	t_point		tex_pixel;				// Current pixel in texture
	int			color;					// Final color from texture
}	t_sprite_draw;

typedef struct s_sprite
{
	t_dpoint	pos;
	t_point		size;
	char		**idle_paths;
	t_texture	*idle_frames;
	int			idle_frames_count;
	t_texture	texture;
	int			anim_start;
	int			anim_index;
	double		anim_timer;
}	t_sprite;

typedef enum e_dial_phase
{
	PHASE_0,
	PHASE_1,
	PHASE_2,
	PHASE_3,
	PHASE_4
}	t_dial_phase;

# define DENIAL_LOOP		0
# define ANGER_LOOP			1
# define BARGAINING_LOOP	2
# define DEPRESSION_LOOP	3
# define ACCEPTANCE_LOOP	4

# define FIRST_LOOP		0
# define SECOND_LOOP	1
# define THIRD_LOOP		2
# define FOURTH_LOOP	3

typedef enum e_pending_transition
{
	TRANSITION_NONE,
	TRANSITION_FIRST_TO_SECOND_LOOP,
	TRANSITION_SECOND_TO_THIRD_LOOP,
	TRANSITION_RESET_SECOND_LOOP,
	TRANSITION_THIRD_TO_ANGER_LOOP,
	TRANSITION_SECOND_TO_BARGAINING_LOOP,
	TRANSITION_SECOND_LOOP_TO_DEPRESSION,
	TRANSITION_RESET_FIRST_LOOP,
	TRANSITION_FIRST_TO_ACCEPTANCE_LOOP
}	t_pending_transition;

typedef struct s_story
{
	int						state;
	int						loop_number;
	bool					has_spoken_to_mother;
	bool					has_interacted_with_door;
	bool					has_repaired_frame;
	double					reset_timer;
	double					interaction_timer;
	bool					to_anger_loop;
	t_dpoint				last_player_pos;
	bool					is_player_idle;
	t_pending_transition	pending_transition;
	float					cover_progress;
} t_story;

typedef struct s_dial
{
	char			***dialogues;
	int				*count;
	int				current_line;
	int 			phase_count;
	t_dial_phase	phase;
	float			alpha;
	bool			fading_in;
	bool			fading_out;
	float			fade_speed;
}	t_dial;

typedef enum e_npc_state
{
	IDLE,
	SPEAK,
	NOT_PRESENT
}	e_npc_state;

typedef struct s_npc
{
	char		*type;
	t_dpoint	pos;
	e_npc_state	state;
	t_sprite	sprite;
	t_texture	texture_idle;
	t_texture	texture_blurry;
	t_dial		dialogue;
	bool		is_blurry;
}	t_npc;

typedef enum e_door_state
{
	CLOSED,
	OPENING,
	OPEN,
	CLOSING
}	t_door_state;

typedef enum e_door_type
{
	DOOR_T,
	FRAME_T
}	t_door_type;

typedef struct s_door
{
	t_door_type		type;
	char			*name;
	t_dpoint		pos;
	t_door_state	state;
	double			offset;
}	t_door;

typedef enum e_item_state
{
	IDLE_ITEM,
	ON,
	BROKEN
}	t_item_state;

typedef struct s_item
{
	char			*type;
	char			*name;
	t_dpoint		pos;
	t_texture		texture;
	t_texture		texture_broken;
	t_texture		texture_message;
	t_sprite		sprite;
	t_item_state	state;
	bool			is_interactable;
	bool			is_broken;
	bool			has_message;
}	t_item;

typedef enum e_entity_type
{
	NPC,
	ITEM
}	t_entity_type;

typedef struct s_entity
{
	t_entity_type	type;
	t_dpoint		pos;
	void			*ptr;
}	t_entity;

typedef struct s_tex
{
	t_texture walls_denial;
	t_texture door_denial;
	t_texture frame_denial;

	t_texture walls_angry;
	t_texture door_angry;
	t_texture frame_angry;

	t_texture walls_acceptance;
	t_texture door_acceptance;
	t_texture frame_acceptance;

	t_texture walls_bargaining;
	t_texture door_bargaining;
	t_texture frame_bargaining;
	t_texture frame_bargaining_repaired;
	
	t_texture walls_sad;
	t_texture door_sad;
	t_texture frame_sad;
}	t_tex;

typedef enum e_game_state
{
	RUNNING,
	PAUSED,
	GAME_OVER,
	WIN
}	t_game_state;

typedef struct s_player
{
	char		conf_dir;
	t_dpoint	pos;
	t_dpoint	start_pos;
	t_dpoint	last_pos;
	t_dpoint	facing_dir;		// Direction vector
	t_dpoint	view_plane;		// Camera plane vector: perp to facing_dir
	double		rot_speed;		// (in radians)
	double		move_speed;
	double		facing_angle; 	// (in radians)
	double		start_facing_angle;
}	t_player;

typedef enum e_fade_state
{
	FADE_IDLE,
	FADE_IN,
	FADE_OUT
}	t_fade_state;

typedef struct s_transition
{
	bool					on;
	double					timer;
	double					duration;
	double					fade_alpha; // 0.0 (transparent) to 1.0 (fully black)
	t_fade_state			state;
	bool					midpoint_triggered;
}	t_transition;

typedef struct s_font
{
	Font	dialogue;
	Font	interaction;
} t_font;

typedef struct s_track
{
	Music	music;
	float	volume;
	bool	is_playing;
}	t_track;

typedef struct s_music
{
	t_track	voice_message_one;
	t_track	voice_message_two;
	double	voice_timer;
	bool	voice_active;
	t_track	denial;
	t_track	acceptance;
	t_track	bargaining;
	t_track	anger;
	t_track	depression;
} t_music;

typedef struct s_game
{
	t_game_state	state;
	t_story			story;
	t_map			*map;
	t_player		player;
	t_tex			tex;
	t_npc			**npcs;
	int				npc_count;
	t_door			**doors;
	int				door_count;
	t_item			**items;
	int				item_count;
	t_entity		*entities;
    int				entity_count;
	bool			keys[66000];
	bool			interactions_blocked;
	double			interaction_block_timer;
	t_transition	transition;
	bool			temp_msg_visible;
	char			temp_msg[80];
	double			temp_msg_timer;
	double			temp_msg_timer_max;
	t_font			font;
	bool 			instruction;
	t_music			music;
}	t_game;

void	spawn_armchair(t_game *game, double x, double y);
void	spawn_armchair2(t_game *game, double x, double y);
void	spawn_answering_machine(t_game *game, double x, double y);
void	spawn_coffee_table(t_game *game, double x, double y);
void	spawn_chair(t_game *game, double x, double y);
void	spawn_mother(t_game *game, double x, double y);
void	spawn_plant(t_game *game, double x, double y);

void	spawn_frame(t_game *game, double x, double y);

void	reset_player(t_game *game, t_player *player);

void	update_interaction_block_timer(t_game *game, double delta_time);
void	block_interactions_for_seconds(t_game *game, double seconds);

void	start_fade_out(t_transition *transition);

void	init_transition(t_game *game, t_transition *transition, double duration);
void	update_transition(t_game *game, t_transition *transition, double delta_time);
void	render_transition(t_game *game, t_transition *transition);

void	draw_background(t_game *game);

void	update_voice_timer(t_game *game, double delta_time);

void	update_music(t_game *game, double delta_time);


// UTILS
void	error(t_game *game, char *err_msg);
void	free_game(t_game *game);
void	load_single_texture(t_game *game, t_texture *tex, const char *path);
void	load_game_textures(t_game *game);
bool	is_facing_target(t_player *player, t_dpoint target_pos);
void	update_entities_sort(t_game *game);

// PARSING
void	extract_file_content(t_game *game, t_map *map);
void	normalize_map_layout(t_game *game, t_map *map);
void	calculate_map_dimension(t_game *game, t_map *map);
void	process_map_cell(t_game *game, t_map *map, int row, int col);
void	check_map_boundaries(t_game *game, t_map *map, int row, int col);
void	check_map_chars(t_game *game, char c, int row, int col);
int		convert_map_char_to_value(t_game *game, t_map *map, int i, int j);
void	parse_map(t_game *game, t_map *map);

// INITIALIZATION
t_game	*init_game(char *filename);
void	init_player(t_game *game, t_player *player);

// TEMP_MESSAGE
void	update_temp_message(t_game *game, double delta_time);
void	show_temp_message(t_game *game, double duration, const char *message);
void	draw_temp_message(t_game *game);


// ITEM


// DOOR
void	update_door_list(t_game *game, t_door *door);
void	spawn_door(t_game *game, double x, double y);
t_door	*find_door_at(t_game *game, t_point pos);

// RENDERING
void	calculate_texture_mapping(t_game *game, t_ray *ray);
void	calculate_ray_properties(t_game *game, t_ray *ray);
void	init_ray(t_game *game, t_ray *ray, int x);
void	init_dda_ray(t_game *game, t_ray *ray);
void	raycast(t_game *game, t_ray *ray, int x, double *z_buffer);
void	perform_dda(t_game *game, t_ray *ray);
void	render_scene(t_game *game, double delta_time);

void	draw_npc_dialogue(t_game *game);
void	draw_entities(t_game *game, double *z_buffer);

double	compute_determinant(t_player player);
double	compute_inverse_determinant(double det);
double	compute_transform_x(t_player player, t_dpoint rel, double inv_det);
double	compute_transform_y(t_player player, t_dpoint rel, double inv_det);
bool	is_sprite_in_front(double transform_y);
bool	calc_sprite_screen_coords(t_sprite_draw *data);
bool	init_sprite_draw_data(t_sprite_draw *data, t_player player, t_sprite *sprite);
void	draw_sprite_column(t_game *game, t_sprite_draw *data, double *z_buffer);
bool	init_sprite_draw_data(t_sprite_draw *data, t_player player, t_sprite *sprite);
void	draw_sprite(t_game *game, t_player player, t_sprite *sprite, double *z_buffer);
void	draw_texture(t_game *game, t_texture *texture, t_dpoint texture_pos, double *z_buffer);

// HOOKS
bool	interact_with_door(t_game *game);
bool	interact_with_item(t_game *game);
bool	interact_with_npc(t_game *game);
bool	continue_npc_dialogue(t_game *game);
void	update_story(t_game *game, double delta_time);
void	handle_interaction(t_game *game);
void	handle_events(t_game *game);

// GAME LOOP
int		game_loop(t_game *game);
bool	is_map_position_valid_player(t_game *game, t_dpoint pos);
bool	is_player_move_valid(t_game *game, t_dpoint pos);
void	handle_player_moves(t_game *game, double delta_time);
void	rotate_player_left(t_player *player, double delta_time);
void	rotate_player_right(t_player *player, double delta_time);
void	move_player_forward(t_game *game, t_player *player, double delta_time);
void	move_player_backward(t_game *game, t_player *player, double delta_time);
void	strafe_player_left(t_game *game, t_player *player, double delta_time);
void	strafe_player_right(t_game *game, t_player *player, double delta_time);

// MEMORY UTILS
void	*x_malloc(t_game *game, size_t size);
void	*x_calloc(t_game *game, size_t count, size_t size);
void	*x_realloc(t_game *game, void *ptr, size_t old_size, size_t new_size);
char	*x_strjoin_free(t_game *game, char *s1, char *s2);
char	*x_strdup(t_game *game, const char *s);
char	**x_copy_strarray(t_game *game, char **array);
int		**x_create_matrix(t_game *game, int row_count, int col_count);
char	*x_itoa(t_game *game, int n);

// MUSIC


#endif