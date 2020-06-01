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

SpriteActionComponent::SpriteActionComponent(SDL_Renderer *renderer)
    :ActionComponent ("SpriteAction", 0.0f,0.0f), renderer(renderer), index(0){

}

void SpriteActionComponent::_init(nlohmann::json json)
{
    std::cout<<"SPRITE INIT CALLED WITH : " << json << std::endl;
    ActionComponent::_init(json);
    const std::string &dir = json[INIT_PARAM_SPRITE_FOLDER];
    const std::string &pattern = json[INIT_PARAM_SPRITE_NAME];
    std::cout<<"DIR IS " << dir << " AND NAME IS "<<pattern << std::endl;
    int frameCount = json[INIT_PARAM_SPRITE_FRAMECOUNT].get<int>();
    std::cout<<"Framecount: " << frameCount<<std::endl;
    if(!is_directory(dir))
        throw new std::runtime_error(INIT_PARAM_SPRITE_FOLDER + " is not a valid directory!");
    std::cout<<"loading frames..."<<std::endl;
    for(int i = 0; i < frameCount; i++){
        std::stringstream stringStream;
        stringStream << pattern << std::setfill('0') << std::setw(6) << i<<".png";
        const std::string &fullPath = (dir+"/"+stringStream.str());
        std::cout<<"Image is " << fullPath<<std::endl;
        SDL_Surface* surf = IMG_Load(fullPath.c_str());
        if(surf != NULL){
            this->textures.push_back(SDL_CreateTextureFromSurface(this->renderer, surf));
            SDL_FreeSurface(surf);
        }else {
            throw std::runtime_error((std::string("COULD NOT LOAD IMAGE AT PATH")+stringStream.str()).c_str());
        }
    }
    std::cout<<"init done"<<std::endl;
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
