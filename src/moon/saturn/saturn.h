#ifndef MoonSaturnEngine
#define MoonSaturnEngine

#include <string>
#include <vector>

#include <mario_animation_ids.h>

extern enum MarioAnimID selected_animation;

namespace MoonInternal {
    void setupSaturnModule(std::string status);
    void freeze_camera();
    void saturn_play_animation(MarioAnimID);
}

extern bool show_menu_bar;

extern bool camera_frozen;
extern float camera_speed;
#include "saturn_types.h"

extern bool mario_exists;

extern bool enable_night_skybox;
extern bool enable_yoshi;

extern bool has_changed_chroma_sky;

#endif