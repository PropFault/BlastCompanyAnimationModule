#ifndef SPAWNERACTION_H
#define SPAWNERACTION_H
#include "actioncomponent.h"
#include <string>
#include <nlohmann/json.hpp>
#include "../BlastCompany/entitycomponentmanager.h"
class SpawnerActionComponent : public ActionComponent
{
private:
    bool despawnOnAnimationEnd;
    EntityComponentManager &ecm;
public:
    const static std::string INIT_PARAM_DESPAWN_ON_ANIM_END;
    const static std::string INIT_PARAM_ENTITY_FILE;
    SpawnerActionComponent();

    // Component interface
public:
    Component *clone() override;

    // ActionComponent interface
public:
    void onActionStart() override;
    void onActionUpdate(float playheadPosition, float relativePlayheadPosition) override;
    void onActionEnd() override;
};

#endif // SPAWNERACTION_H
