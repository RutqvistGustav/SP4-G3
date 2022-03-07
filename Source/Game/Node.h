#pragma once
#include <string>
#include "NodePin.hpp"

class NodeGraph;

enum class eNodeType
{
    //General
    None,
    Start,
    Timer, 
    Input,
    End,
    //Variables
    Float,
    String,
    Int,
    Bool,
    //Console
    ConsolePrint,
    ConsolePrintFloat,
    //Math
    AddInt,
    AdditionFloat,
    CompareInt,
    CompareBool,
    CompareStr,
    IsGreaterOrEqualInt,
    IsGreaterFloat,
    //Statements
    Branch,
    //Entity
    EntityId,
    //Gameplay
    KillCount,
    Door,
    ActivateButton,
    Light,
    Lights,
    LightStatus,
    CompareLights,
    CurrentButton,
    ButtonClicked,
    //Events
    OnTriggerEnter,
    OnTriggerExit,
    OnButtonPressed,
    OnCollision
};

class Node
{
public:
    virtual ~Node();

    virtual int Run();

    inline const int& GetId() const { return mId; }

    void SetStartNode();
    void SetId(const int& aId);
    void SetName(const std::string& aName);
    void SetCategory(const std::string& aCategory);
    void SetType(eNodeType aType);
    void SetPins(const std::vector<Pin*>& aPins);
    void SetGraph(NodeGraph* aGraph);

    inline const bool IsStartNode() { return mIsStartNode; }
    inline const std::string& GetNodeName() const { return mName; }
    inline const std::string& GetNodeCategory() const { return mCategory; }
    inline const eNodeType GetNodeType() const { return mType; }
    inline const std::vector<Pin*>& GetPins() const { return mPins; }

protected:
    void CreatePin(std::string aLabel, PinType aType, PinDirection aDirection = PinDirection::None);
    std::any GetPinData(const int aPinIndex);

    std::vector<Pin*> mPins;

    std::string mName = "N/A";
    std::string mCategory = "N/A";
    eNodeType mType = eNodeType::None;
    int mId = 0;;

    bool mIsStartNode = false;

    NodeGraph* mGraph = nullptr;
};

static unsigned int mNextId = 9999;