#include "spriteactioncomponent.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <sstream>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <iomanip>
#include <iostream>
using namespace boost::filesystem;
const std::string SpriteActionComponent::INIT_PARAM_SPRITE_FOLDER = "folder";
const std::string SpriteActionComponent::INIT_PARAM_SPRITE_NAME = "name";
const std::string SpriteActionComponent::INIT_PARAM_SPRITE_FRAMECOUNT = "framecount";

SpriteActionComponent::SpriteActionComponent(ResourceLoader &resourceLoader)
    :ActionComponent ("SpriteAction"), resourceLoader(resourceLoader), index(0){

}

void SpriteActionComponent::_init(nlohmann::json json)
{
    ActionComponent::_init(json);
    const std::string &dir = json[INIT_PARAM_SPRITE_FOLDER];
    const std::string &pattern = json[INIT_PARAM_SPRITE_NAME];
    int frameCount = json[INIT_PARAM_SPRITE_FRAMECOUNT].get<int>();
    if(!is_directory(dir))
        throw new std::runtime_error(INIT_PARAM_SPRITE_FOLDER + " is not a valid directory!");
    for(int i = 0; i < frameCount; i++){
        std::stringstream stringStream;
        stringStream << pattern << std::setfill('0') << std::setw(6) << i<<".png";
        const std::string &fullPath = (dir+"/"+stringStream.str());
        this->textures.push_back(this->resourceLoader.loadSDLTexture(fullPath));
    }
}

void SpriteActionComponent::_deinit()
{
    ActionComponent::_deinit();
    for(SDL_Texture *texture : this->textures)
        SDL_DestroyTexture(texture);
    this->textures.clear();
}

Component *SpriteActionComponent::clone()
{
    return new SpriteActionComponent(*this);
}

void SpriteActionComponent::onActionStart()
{
    this->index = 0;
}

void SpriteActionComponent::onActionUpdate(float playheadPosition, float relativePlayheadPosition)
{
    this->index = (int)round(relativePlayheadPosition*(this->textures.size()-1));
}

void SpriteActionComponent::onActionEnd()
{
    this->index = this->textures.size()-1;
}

SpriteActionComponent::~SpriteActionComponent()
{
    if(this->textures.size() > 0){
        for(SDL_Texture *texture : this->textures)
            SDL_DestroyTexture(texture);
        this->textures.clear();
    }
}

SDL_Texture *SpriteActionComponent::getSDLTexture() const
{
    return this->textures.at(index);
}
