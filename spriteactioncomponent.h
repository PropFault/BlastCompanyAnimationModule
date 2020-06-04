#ifndef SPRITEACTIONCOMPONENT_H
#define SPRITEACTIONCOMPONENT_H
#include "actioncomponent.h"
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "../BlastCompany/texture.h"
#include "../BlastCompany/resourceloader.h"

class SpriteActionComponent : public ActionComponent,public Texture
{
private:
    ResourceLoader &resourceLoader;
    std::vector<SDL_Texture*> textures;
    int index;
public:
    SpriteActionComponent(ResourceLoader &resourceLoader);
    // Component interface
private:
    void _init(nlohmann::json json);
    void _deinit();

public:
    Component *clone();

    // ActionComponent interface
public:
    void onActionStart();
    void onActionUpdate(float playheadPosition, float relativePlayheadPosition);
    void onActionEnd();
public:
    static const std::string INIT_PARAM_SPRITE_FOLDER;
    static const std::string INIT_PARAM_SPRITE_NAME;
    static const std::string INIT_PARAM_SPRITE_FRAMECOUNT;

    virtual ~SpriteActionComponent();

    // Texture interface
public:
    SDL_Texture *getSDLTexture() const;
};

#endif // SPRITEACTIONCOMPONENT_H
