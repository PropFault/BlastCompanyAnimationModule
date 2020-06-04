#ifndef CALLBACKACTION_H
#define CALLBACKACTION_H
#include <functional>
#include <unordered_map>
#include <string>
#include "actioncomponent.h"
#include "../BlastCompany/functionmanager.h"
class CallbackActionComponent : public ActionComponent
{
public:
    enum CallbackState{START, UPDATE, STOP};
    class CallbackEventArgs{
    public:
        CallbackState state;
        CallbackEventArgs(){

        }
        CallbackEventArgs(CallbackState state){
            this->state = state;
        }

    };

private:
    Component::CID parentAnimation;
    std::string identifier;
    const FunctionManager& funcManager;
    void notifyCallback(CallbackState state, Component::CID cid);
public:
    static const std::string INIT_PARAM_CALLBACK_IDENTIFIER;
    static const std::string INIT_PARAM_PARENT_ANIMATION;
    CallbackActionComponent(const FunctionManager &funcManager);


    // Component interface
public:
    Component *clone() override;

    // ActionComponent interface
public:
    void onActionStart() override;
    void onActionUpdate(float playheadPosition, float relativePlayheadPosition) override;
    void onActionEnd() override;

    // Component interface
protected:
    void _init(nlohmann::json json) override;
    void _deinit() override;
};

#endif // CALLBACKACTION_H
