#include "callbackactioncomponent.h"
#include <unordered_map>
#include <functional>
#include <iostream>
#include <any>
const std::string CallbackActionComponent::INIT_PARAM_PARENT_ANIMATION = "parentAnimation";
const std::string CallbackActionComponent::INIT_PARAM_CALLBACK_IDENTIFIER = "identifier";

void CallbackActionComponent::notifyCallback(CallbackActionComponent::CallbackState state, Component::CID cid)
{

    this->funcManager.call(this->identifier,CallbackEventArgs(state), cid);
}
CallbackActionComponent::CallbackActionComponent(const FunctionManager &funcManager)
    :ActionComponent ("CallbackAction"), funcManager(funcManager), identifier("UNDEFINED_ID"){
}

Component *CallbackActionComponent::clone()
{
    return new CallbackActionComponent(*this);
}

void CallbackActionComponent::onActionStart()
{
    notifyCallback(START, this->parentAnimation);
}

void CallbackActionComponent::onActionUpdate(float playheadPosition, float relativePlayheadPosition)
{
    notifyCallback(UPDATE, this->parentAnimation);
}

void CallbackActionComponent::onActionEnd()
{
    notifyCallback(STOP, this->parentAnimation);
}

void CallbackActionComponent::_init(nlohmann::json json)
{
    ActionComponent::_init(json);
    this->identifier = json[INIT_PARAM_CALLBACK_IDENTIFIER].get<std::string>();
    this->parentAnimation = json[INIT_PARAM_PARENT_ANIMATION].get<Component::CID>();
}

void CallbackActionComponent::_deinit()
{
    this->identifier = "undefined";
    this->parentAnimation = -1;
}


