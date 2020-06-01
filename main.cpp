#include <iostream>
#include "../BlastCompany/componentplugin.h"
#include "animationcomponent.h"
#include "animationsystem.h"
#include <boost/config.hpp>
#include <iostream>
#include "spriteactioncomponent.h"
using namespace std;

namespace plugins {
class AnimationComponentPlugin : public ComponentPlugin{
public:


    // ComponentPlugin interface
public:
    void onRegisterComponents(const Window &window, const SDLRenderer &renderer, EntityComponentManager &ecm){
        std::cout<<"onRegisterComponent"<<std::endl;
        ecm.registerBlueprint(new SpriteActionComponent(renderer.getSdlRenderer()));
        ecm.registerBlueprint(new AnimationComponent(ecm));
    }
    void onRegisterSystems(SystemPipeline &pipeline){
        pipeline.add(new AnimationSystem());
    }
};
extern "C" BOOST_SYMBOL_EXPORT AnimationComponentPlugin plugin;
extern "C" BOOST_SYMBOL_EXPORT AnimationComponent baggage;
AnimationComponentPlugin plugin;
}
