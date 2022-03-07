#pragma once
#include <vector>
#include <string>

class Node;
class NodeGraph;
struct Pin;

class NodeEditorManager
{
public:
    static NodeEditorManager* Get();

    void Init();
    void Update();
    void SetCurrentGraph(NodeGraph* aGraph);

private:
    void UpdateInput();

    void Load(const std::string& aGraphName);
    void SaveAs();
    void Save();
    void Clear();
    void Delete();

    void Menu();
    void MenuLoad();

    void CopyNodes();
    void PasteNodes();

    void NodeOptions();
    void CreateNode();
    void DeleteNode(const int aId);

    void DrawNodesAndLinks();
    void DrawPin(Pin* aPin);
    void DrawInPin(Pin* aPin);
    void DrawOutPin(Pin* aPin);

    void UpdateLinks();

    NodeGraph* mCurrentGraph;
    NodeGraph* mBaseGraph;
    const std::string mFolderPath = "NodeEditor/";
    bool mShowCategorys;
    int mHoveredNode;

    std::vector<Node*> mCopiedNodes;

    static NodeEditorManager* ourInstance;

    NodeEditorManager();
    ~NodeEditorManager();
};