#include "animationsystem.h"
#include "animationcomponent.h"

AnimationSystem::AnimationSystem()
    :System("animation")
{
    this->lastExec = -1;
}

float getDeltaSec(clock_t lastClock){
    return (clock() - lastClock) / (double) CLOCKS_PER_SEC;
}

void AnimationSystem::think(EntityComponentManager &ecs, const std::unordered_set<Component::CID> &typedComponents, System::DataPack &dataPack)
{
    if(this->lastExec == -1)
        this->lastExec = clock();
    for(Component::CID comp : typedComponents){
        //std::cout<<"Trying to find animation component..."<<std::endl;
        AnimationComponent* animComponent = ecs.lookupCID<AnimationComponent>(comp);
       // std::cout<<"found it"<<std::endl;
        if(animComponent->getIsPlaying()){
        //    std::cout<<"Component is playing" <<std::endl;
       //     std::cout<<"DELTASEC: " << getDeltaSec(this->lastExec)<<std::endl;
            animComponent->setPlayhead(animComponent->getPlayhead() + getDeltaSec(this->lastExec));
            float absPlayhead = animComponent->getPlayhead();
            float playhead = absPlayhead / animComponent->getDuration();

        //    std::cout<<"PLAYHEAD: " << playhead*100 << "%" << " ABS " << absPlayhead << " DUR " << animComponent->getDuration()<<std::endl;
            if(playhead > 1.0)
            {
      //          std::cout<<"STOPPING ANIM BECAUSE " << playhead << " > " << animComponent->getDuration() << std::endl;
                if(animComponent->getLoops() == false)
                    animComponent->setIsPlaying(false);
                animComponent->setPlayhead(0.0f);
            }else{
                for(Component::CID actionComp : animComponent->getActions()){
                    ActionComponent *action = ecs.lookupCID<ActionComponent>(actionComp);
//                    std::cout<<"HAS BEEN STARTED " << action->getHasBeenStarted() << " HAS BEEN ENDED " << action ->getHasBeenEnded() << std::endl;
                    if(action->getHasBeenStarted() == false && action->getStartPoint() <= playhead)
                    {

                        action->onActionStart();
                        action->setHasBeenStarted(true);
                        action->setHasBeenEnded(false);
                    }
                    if(action->getStartPoint() < playhead && action->getEndPoint() > playhead){
                        action->onActionUpdate(playhead, (playhead - action->getStartPoint()) / (action->getEndPoint() - action->getStartPoint()));
                    }
                    if(action->getHasBeenEnded() == false && action->getEndPoint() < playhead){
                        action->onActionEnd();
                        action->setHasBeenEnded(true);
                        action->setHasBeenStarted(false);
                    }
                }
            }
        }
    }

    this->lastExec = clock();
}
