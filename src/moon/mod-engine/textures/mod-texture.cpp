#include "mod-texture.h"

#include "moon/fs/moonfs.h"
#include "moon/libs/nlohmann/json.hpp"
#include "moon/mod-engine/engine.h"
#include "moon/mod-engine/hooks/hook.h"
#include "modifiers/tmod.h"
#include "modifiers/animated.h"
#include "assets/missing.h"
#include "assets/logo.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

extern "C" {
#include "text/libs/io_utils.h"
#include "pc/gfx/gfx_rendering_api.h"
#include "pc/platform.h"
#include "pc/fs/fs.h"
}

#include <iostream>
#include <vector>
#include <map>

using namespace std;
using json = nlohmann::json;

std::map<std::string, EntryFileData*> baseGameTextures;
map<string, TextureData*> textureMap;
map<string, BitModule*> textureCache;

map<string, TextureModifier*> textureMods;

namespace Moon {
    void saveAddonTexture(BitModule *addon, std::string texturePath, EntryFileData* data){
        addon->textures.insert(pair<string, EntryFileData*>(texturePath, data));
    }

    void bindTextureModifier(std::string texture, std::string modName, json data){
        if(textureMods.find(modName) != textureMods.end())
            textureMods[modName]->onLoad(texture, data);
    }

    void precacheBaseTexture(char* data, long size, std::string texturePath){
        if(baseGameTextures.find(texturePath) == baseGameTextures.end())
            baseGameTextures.insert(pair<string, EntryFileData*>(
                texturePath,
                new EntryFileData({.path = "", .size = size, .data = data}))
            );
    }

    TextureData *getCachedTexture(string texturePath){
        return textureMap.find(texturePath) != textureMap.end() ? textureMap.find(texturePath)->second : nullptr;
    }
}

namespace MoonInternal {

    EntryFileData *getTextureData(const char *fullpath){
        char texname[SYS_MAX_PATH];
        strncpy(texname, fullpath, sizeof(texname));
        texname[sizeof(texname)-1] = 0;
        char *dot = strrchr(texname, '.');
        if (dot) *dot = 0;

        char *actualname = texname;
        if (!strncmp(FS_TEXTUREDIR "/", actualname, 4)) actualname += 4;
        actualname = sys_strdup(actualname);
        assert(actualname);

        auto cacheEntry = textureCache.find(actualname);
        BitModule *addon = cacheEntry->second;

        EntryFileData * data = NULL;

        if(addon != NULL){
            EntryFileData *fileEntry = addon->textures.find(actualname)->second;

            if(fileEntry != NULL){
                if(fileEntry->data != NULL) data = fileEntry;
                else if(!fileEntry->path.empty()){
                    MoonFS file(addon->path);
                    file.open();
                    EntryFileData *newData = new EntryFileData();
                    file.read(fileEntry->path, newData);
                    data = newData;
                }
            }
        }
        return data;
    }

    void loadTexture(int tile, const char *fullpath, struct GfxRenderingAPI *gfx_rapi){

        int w, h;
        u64 imgsize = 0;

        if(!strcmp(fullpath, "gfx/mod-icons://Moon64.png")){
            gfx_rapi->upload_texture(moon64_logo.pixel_data, moon64_logo.width, moon64_logo.height);
            return;
        }

        EntryFileData * imgdata = getTextureData(fullpath);
        if (imgdata) {
            u8 *data = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(imgdata->data), imgdata->size, &w, &h, NULL, 4);
            if (data) {
                gfx_rapi->upload_texture(data, w, h);
                stbi_image_free(data);
                return;
            } else {
                cout << "Failed to convert texture" << endl;
                std::cout << stbi_failure_reason() << std::endl;
            }
        }

        cout << "Failed to load texture" << endl;
        cout << fullpath << endl;

        gfx_rapi->upload_texture(missing_image.pixel_data, missing_image.width, missing_image.height);
    }

    void saveTexture(TextureData *data, string texturePath){
        textureMap.insert(pair<string, TextureData*>(texturePath, data));
    }

    void buildTextureCache(vector<int> order){
        textureCache.clear();

        for(int i=0; i < order.size(); i++){
            BitModule *addon = Moon::addons[order[i]];

            for (map<string, EntryFileData*>::iterator entry = addon->textures.begin(); entry != addon->textures.end(); ++entry) {
                auto texIt = textureCache.find(entry->first);
                if(texIt != textureCache.end()) textureCache.erase(texIt);

                textureCache.insert(pair<string, BitModule*>(entry->first, addon));
            }
        }
        textureMap.clear();
    }

    void bindTextureModifiers(){
        TextureModifier* modifiers[] = {
            new AnimatedModifier()
        };

        for(auto &mod : modifiers){
            textureMods[mod->getKey()] = mod;
            mod->onInit();
        }
    }

    void setupTextureEngine( string state ){
        if(state == "PreStartup"){
            MoonInternal::bindTextureModifiers();
            return;
        }
        if(state == "PreInit"){
            return;
        }
        if(state == "Exit"){
            textureMods.clear();
            for(auto &addon : Moon::addons){
                addon->textures.clear();
            }
        }
    }

}