#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H
#include "../BlastCompany/system.h"
#include <ctime>

class AnimationSystem : public System
{
private:
    clock_t lastExec;
public:
    AnimationSystem();

    // System interface
public:
    void think(EntityComponentManager &ecs, const std::unordered_set<Component::CID> &typedComponents, DataPack &dataPack);
};

#endif // ANIMATIONSYSTEM_H
