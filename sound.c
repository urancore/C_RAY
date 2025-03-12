#include "ray.h"
#include "sound.h"
#include <time.h>

unsigned short sound_is_playing = 0;
clock_t sound_start_time;
double sound_duration = 4.0; // Длительность звука в секундах

void play_sound(const char *filename)
{
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
    sound_is_playing = 1;
    sound_start_time = clock();
}

void stop_sound()
{
    PlaySound(NULL, NULL, 0);
    sound_is_playing = 0;
}

// void update_game()
// {
//     if (player_walk == 1 && !sound_is_playing) {
//         play_sound("assets/sound/walk/w1.wav");
//     } else if (sound_is_playing == 1 && player_walk == 0) {
//         double elapsed_time = (double)(clock() - sound_start_time) / CLOCKS_PER_SEC;
//         if (elapsed_time >= sound_duration) {
//             stop_sound();
//         }
//     }
// } // прототип, слишком плохо
