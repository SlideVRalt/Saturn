# Saturn: Moon Edition

- *Saturn: Moon Edition* is a cross-platform all-in-one machinima studio for *Super Mario 64*, based on [Undervolt/Moon64](https://github.com/Undervolt/Moon64).
- In order to download, use or compile the editor, a prior copy of the game is required. This is to avoid including any copyrighted assets or material.
- *Detailed, extensive guides can be found on our [wiki](https://github.com/Llennpie/Saturn/wiki).*

#### Features

```
- Completely revamped UI with dockable panels
- Machinima camera
  - A "free camera", can be frozen in place or moved with the joystick.
- Custom eye textures
  - Loaded externally as PNG files
  - Can be selected through a dropdown
- Color code editor
  - Uses the common *GameShark* format
  - Complete visual CC editor
  - Color presets save as a .gs file for later use
- Chroma Key Stage
  - Background is color-changeable to any RGB/Hex code
- Animation Player
  - Can play all 209 of Mario's in-game animations
  - Supports looping/first-person to move head
- Toggles for HUD, Mario's cap emblem, overall buttons, voices, head rotations, shadows, dust particles and more
- Switch between cap states (on/off/wing) and hand poses (victory/open/holding hat/etc.)
- Warp to any level from the menu
- Custom textures (& texture packs) support
  - All textures are 100% customizable
- Settings manager
  - All options from sm64ex and Moon64 (minus configuring controls, currently) carry over to the new UI
  - Option to disable music and Mario's voice for machinima purposes
  - Addons Menu, to switch priority/order of texture packs & more
- "Anti-aliasing" (not really, just clever internal resolution scaling, works better with cross-platform)
- "Jabo Mode", a toggle to recreate the infamous weird widescreen stretching, as seen in many Project64 graphics plugins.
- "Wireframe Mode", it just looks really cool...
```

*... And more to come!*

## Installation

### Download (recommended)
WARNING: THE SATURN ADDON ON THE [USED TO BE] MOON64 PLUGIN SITE IS NOWHERE TO BE FOUND! PLS USE MINGW64 (WHICH COMES WITH MSYS2!)
1: Install GIT and MSYS2
2: Open Git
3: In Git: type "git clone https://github.com/SlideVRalt/Saturn-Moon-Edition-CC100-edition"
4: Get a Mario 64 ROM and extract it to your Saturn: Moon Edition CC100 edition folder. RENAME THE ROM TO "baserom.[YOUR REGION HERE].z64"
5: Open MINGW64 in the folder you installed this in, then type "make"
6: Wait for it to finish compiling.
7: WALLAH! The classic Saturn experience is now in your hands.


