#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "../BlastCompany/component.h"
#include <string>
#include "../BlastCompany/texture.h"
#include <vector>
#include "../BlastCompany/entitycomponentmanager.h"
#include "actioncomponent.h"

class AnimationComponent : public Component, public Texture
{
private:
    bool isPlaying;
    float duration;
    float playhead;
    Component::CID displayedAction;
    std::vector<Component::CID> actions;
    const EntityComponentManager& ecm;
public:
    static const std::string INIT_PARAM_ACTIONS;
    static const std::string INIT_PARAM_DISPLAYED_ACTION;
    static const std::string INIT_PARAM_DURATION;
    AnimationComponent(const EntityComponentManager& ecm);
    bool getIsPlaying() const;
    void setIsPlaying(bool value);
    float getDuration() const;
    void setDuration(float value);
    float getPlayhead() const;
    void setPlayhead(float value);

    // Texture interface
public:
    SDL_Texture *getSDLTexture() const;

    // Component interface
protected:
    void _init(nlohmann::json json);
    void _deinit();

public:
    Component *clone();
    std::vector<Component::CID> getActions() const;
};

#endif // ANIMATIONCOMPONENT_H
