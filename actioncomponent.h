#ifndef ACTION_H
#define ACTION_H
#include "../BlastCompany/component.h"
#include <string>

class ActionComponent : public Component{
private:
    float startPoint;
    float endPoint;
    bool hasBeenStarted;
    bool hasBeenEnded;
public:
    static const std::string INIT_PARAM_START_POINT;
    static const std::string INIT_PARAM_STOP_POINT;

    ActionComponent(const std::string &componentName);
    float getStartPoint() const;
    void setStartPoint(float value);
    float getEndPoint() const;
    void setEndPoint(float value);

    virtual void onActionStart() = 0;
    virtual void onActionUpdate(float playheadPosition, float relativePlayheadPosition)=0;
    virtual void onActionEnd() = 0;

    // Component interface
protected:
    void _init(nlohmann::json json);
    void _deinit();

public:
    virtual Component *clone() = 0;
    bool getHasBeenStarted() const;
    void setHasBeenStarted(bool value);
    bool getHasBeenEnded() const;
    void setHasBeenEnded(bool value);
};

#endif // ACTION_H
