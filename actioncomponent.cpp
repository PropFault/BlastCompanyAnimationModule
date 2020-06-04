#include "actioncomponent.h"
#include <string>
const std::string ActionComponent::INIT_PARAM_START_POINT = "start";
const std::string ActionComponent::INIT_PARAM_STOP_POINT = "end";

float ActionComponent::getEndPoint() const
{
    return endPoint;
}

void ActionComponent::setEndPoint(float value)
{
    endPoint = value;
}

void ActionComponent::_init(nlohmann::json json)
{
    this->startPoint = json[INIT_PARAM_START_POINT].get<int>();
    this->endPoint = json[INIT_PARAM_STOP_POINT].get<int>();
}

void ActionComponent::_deinit()
{
    this->startPoint = 0;
    this->endPoint = 0;
}


float ActionComponent::getStartPoint() const
{
    return startPoint;
}

void ActionComponent::setStartPoint(float value)
{
    startPoint = value;
}

bool ActionComponent::getHasBeenStarted() const
{
    return hasBeenStarted;
}

void ActionComponent::setHasBeenStarted(bool value)
{
    hasBeenStarted = value;
}

bool ActionComponent::getHasBeenEnded() const
{
    return hasBeenEnded;
}

void ActionComponent::setHasBeenEnded(bool value)
{
    hasBeenEnded = value;
}

ActionComponent::ActionComponent(const std::string &componentName)
    :Component (componentName), startPoint(-1.0), endPoint(-1.0), hasBeenStarted(false), hasBeenEnded(false)
{}

