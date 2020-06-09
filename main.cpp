#include <iostream>
#include "../BlastCompany/componentplugin.h"
#include "animationcomponent.h"
#include "animationsystem.h"
#include <boost/config.hpp>
#include <iostream>
#include "spriteactioncomponent.h"
#include "callbackactioncomponent.h"
#include "../BlastCompany/functionmanager.h"
#include "../BlastCompany/context.h"
using namespace std;

namespace plugins {
class AnimationComponentPlugin : public ComponentPlugin{
public:


    // ComponentPlugin interface
public:
    void onRegisterComponents(const Context &context) override{
        std::cout<<"onRegisterComponent"<<std::endl;
        EntityComponentManager &ecm = context.getEcm();
        ecm.registerBlueprint(new SpriteActionComponent(context.getResourceLoader()));
        ecm.registerBlueprint(new AnimationComponent(context.getEcm()));
        ecm.registerBlueprint(new CallbackActionComponent(context.getFuncMan()));
    }
    void onRegisterSystems(SystemPipeline &pipeline, const Context &context) override{
        pipeline.add(new AnimationSystem());
    }

};
extern "C" BOOST_SYMBOL_EXPORT AnimationComponentPlugin plugin;
AnimationComponentPlugin plugin;
}
