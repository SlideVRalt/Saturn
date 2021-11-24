#ifndef MoonSaturnEngine
#define MoonSaturnEngine

#include <string>
#include <vector>

namespace MoonInternal {
    void setupSaturnModule(std::string status);
    void freeze_camera();
}

extern bool camera_frozen;
#include "saturn_types.h"

extern bool show_menu_bar;

extern float camera_speed;
extern bool enable_cap_logo;
extern bool enable_overall_buttons;
extern bool enable_night_skybox;
extern bool enable_yoshi;

#endif