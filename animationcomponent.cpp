#include "animationcomponent.h"
#include <nlohmann/json.hpp>
#include <iostream>
const std::string AnimationComponent::INIT_PARAM_ACTIONS = "actions";
const std::string AnimationComponent::INIT_PARAM_DISPLAYED_ACTION = "displayedAction";
const std::string AnimationComponent::INIT_PARAM_DURATION = "duration";
const std::string AnimationComponent::INIT_PARAM_LOOPS = "loops";
void AnimationComponent::setPlayhead(float value)
{
    playhead = value;
}

std::vector<Component::CID> AnimationComponent::getActions() const
{
    return actions;
}




bool AnimationComponent::getLoops() const
{
    return loops;
}

void AnimationComponent::setLoops(bool value)
{
    loops = value;
}

AnimationComponent::AnimationComponent(const EntityComponentManager &ecm)
    :Component("animation"), ecm(ecm), isPlaying(true), loops(false){

}

bool AnimationComponent::getIsPlaying() const
{
    return isPlaying;
}

void AnimationComponent::setIsPlaying(bool value)
{
    isPlaying = value;
}

float AnimationComponent::getDuration() const
{
    return duration;
}

void AnimationComponent::setDuration(float value)
{
    duration = value;
}

float AnimationComponent::getPlayhead() const
{
    return playhead;
}

SDL_Texture *AnimationComponent::getSDLTexture() const
{
    if(this->displayedAction == 0)
        throw new std::runtime_error("Requested texture on animation without display component");
    Texture* display = this->ecm.lookupCID<Texture>(this->displayedAction);
    return display->getSDLTexture();
}

void AnimationComponent::_init(nlohmann::json json)
{
    std::cout<<"Called _init with " << json << std::endl;
    for(auto& element : json[INIT_PARAM_ACTIONS]){
        this->actions.push_back(element.get<Component::CID>());
    }
    try {
        std::cout<<"Displayed action raw: " << json.at(INIT_PARAM_DISPLAYED_ACTION) << std::endl;
        this->displayedAction = json.at(INIT_PARAM_DISPLAYED_ACTION).get<Component::CID>();
        std::cout<<"Init displayed action with: " << this->displayedAction << std::endl;
    } catch (const nlohmann::detail::out_of_range &ex) {
        std::cout<<"displayed action caused out_of_range. setting to 0"<<std::endl;
        this->displayedAction = 0;
    }
    std::cout<<"CHECKING IF LOOPS"<<std::endl;
    try {
        this->loops = json[INIT_PARAM_LOOPS].get<bool>();
    } catch (const nlohmann::detail::type_error &ex) {
        this->loops = false;
    }

    std::cout<<"LOOPS: " << this->loops<<std::endl;
    this->duration = json[INIT_PARAM_DURATION].get<float>();
    this->playhead = 0;
}

void AnimationComponent::_deinit()
{
    this->actions.clear();
    this->duration = 0;
    this->playhead = 0;
}

Component *AnimationComponent::clone()
{
    std::cout<<"AnimationComponent::clone"<<std::endl;
    return new AnimationComponent(this->ecm);
}


