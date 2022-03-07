#include "stdafx.h"
#include "NodeEditorManager.h"

#include <filesystem>
#include <map>
#include <fstream>

#include "imnodes.h"
#include "imnodes_internal.h"

#include "NodeGraphManager.h"
#include "NodeGraph.h"
#include "NodeRegistry.h"
#include "Node.h"
#include "NodePin.hpp"

NodeEditorManager* NodeEditorManager::ourInstance = nullptr;

NodeEditorManager::NodeEditorManager() :
    mShowCategorys(false),
    mCurrentGraph(nullptr),
    mBaseGraph(nullptr),
    mHoveredNode(-1)
{
}

NodeEditorManager::~NodeEditorManager()
{
    Clear();
}

NodeEditorManager* NodeEditorManager::Get()
{
    if (!ourInstance)
    {
        ourInstance = new NodeEditorManager();
        ourInstance->Init();
    }
    return ourInstance;
}

void NodeEditorManager::Init()
{
	ImNodes::CreateContext();
    ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);

    NodeRegistry::RegisterTypes();

    mBaseGraph = new NodeGraph();

    std::string graphName = "mainGraph";

    std::string saveFile = mFolderPath + graphName + ".ini";
    ImNodes::LoadCurrentEditorStateFromIniFile(saveFile.c_str());

    mCurrentGraph = NodeGraphManager::Get()->GetGraph(graphName);

    if (!mCurrentGraph)
    {
        mCurrentGraph = mBaseGraph;
    }
}

void NodeEditorManager::Update()
{
    ImGui::Begin("Node Editor");

    Menu();
    UpdateInput();

    ImNodes::BeginNodeEditor();
  
    if (ImGui::BeginPopupContextWindow(0, 1, false))
    {
        NodeOptions();
        ImGui::EndPopup();
    }
    
    DrawNodesAndLinks();

    ImNodes::EndNodeEditor();

    UpdateLinks();

    ImGui::End();
}

void NodeEditorManager::SetCurrentGraph(NodeGraph* aGraph)
{
    Load(aGraph->GetName());
}

void NodeEditorManager::Save()
{
    std::string saveFile = mFolderPath + mCurrentGraph->GetName() + ".ini";

    ImNodes::SaveCurrentEditorStateToIniFile(saveFile.c_str());

    NodeGraphManager::Get()->SaveGraph(mCurrentGraph);
}

void NodeEditorManager::UpdateInput()
{
    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Delete)))
    {
        auto& nodes = mCurrentGraph->GetNodes();

        for (int i = 0; i < nodes.size(); ++i)
        {
            const int id = nodes[i]->GetId();

            if (ImNodes::IsNodeSelected(id))
            {
                DeleteNode(id);
            }
        }
    }

    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_C)) && &ImGui::GetIO().KeyCtrl)
    {
        CopyNodes();
    }

    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_V)) && &ImGui::GetIO().KeyCtrl)
    {
        PasteNodes();
    }
}

void NodeEditorManager::Load(const std::string& aGraphName)
{
    std::string saveFile = mFolderPath + aGraphName + ".ini";
    ImNodes::LoadCurrentEditorStateFromIniFile(saveFile.c_str());
    mCurrentGraph = NodeGraphManager::Get()->LoadGraph(aGraphName);
}

void NodeEditorManager::SaveAs()
{
    ImGui::SetNextItemWidth(125.f);
    static char buf[128];
    ImGui::InputTextWithHint("", "Graph Name", buf, 128);
    std::string graphName = buf;

    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
         std::string saveFile = mFolderPath + graphName + ".ini";
         ImNodes::SaveCurrentEditorStateToIniFile(saveFile.c_str());
         mCurrentGraph->SetName(graphName);
         NodeGraphManager::Get()->SaveGraph(mCurrentGraph);
    }
    ImGui::EndMenu();
}

void NodeEditorManager::Clear()
{
    if (!mCurrentGraph) return;

    mCurrentGraph->Clear();
}

void NodeEditorManager::Delete()
{
    if (!mCurrentGraph) return;

    mCurrentGraph->Clear();
    NodeGraphManager::Get()->RemoveGraph(mCurrentGraph);

    delete mCurrentGraph;
    mCurrentGraph = nullptr;
}

void NodeEditorManager::Menu()
{
    ImGui::SameLine();
    if (ImGui::Button("Run"))
    {
        if (!mCurrentGraph) return;
        mCurrentGraph->RunStartNodes();
    }
 
    ImGui::SameLine();
    if (ImGui::Button("Clear")) Clear();

    std::string save = ""; 
    if (mCurrentGraph)
    {
        save = "Save \"" + mCurrentGraph->GetName();
    }
    save += "\"";
    ImGui::SameLine();
    if (ImGui::Button(save.c_str())) Save();

    ImGui::SameLine();
    ImGui::BeginChild(42069666, { 75, 20 }, false);
    if (ImGui::BeginMenu("Save As"))
    {
        SaveAs();
    }
    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild(69420666, { 75, 20 }, false);
    if (ImGui::BeginMenu("Load"))
    {
        MenuLoad();
    }
    ImGui::EndChild();
}

void NodeEditorManager::MenuLoad()
{
    std::vector<std::string> files;
    std::string ext(".bytes");
    for (auto& p : std::filesystem::recursive_directory_iterator(mFolderPath))
    {
        if (p.path().extension() == ext)
        {
            files.push_back(p.path().stem().string());
        }
    }

    ImGui::SetNextItemWidth(125.f);
    static char buf[128];
    ImGui::InputTextWithHint("", "New Graph Name", buf, 128);
    ImGui::SameLine();
    if (ImGui::Button("Create New Graph"))
    {
        std::string name(buf);
        Load(name);
        ImGui::EndMenu();
        return;

    }

    for (auto& file : files)
    {
        if (ImGui::Button(file.c_str()))
        {
            Load(file);
            ImGui::EndMenu();
            return;
        }
    }
    ImGui::EndMenu();
}

void NodeEditorManager::CopyNodes()
{
    for (auto& n : mCopiedNodes)
    {
        delete n;
    }
    mCopiedNodes.clear();

    std::vector<int> nodeIds;
    nodeIds.resize(ImNodes::NumSelectedNodes());

    if (!nodeIds.empty())
    {
        ImNodes::GetSelectedNodes(&nodeIds[0]);

        for (int i = 0; i < nodeIds.size(); ++i)
        {
            auto& nodes = mCurrentGraph->GetNodes();
            for (int j = 0; j < nodes.size(); ++j)
            {
                if (nodes[j]->GetId() == nodeIds[i])
                {                    
                    mCopiedNodes.push_back(nodes[j]);
                }
            }
        }
    }
}

void NodeEditorManager::PasteNodes()
{
    for (int i = 0; i < mCopiedNodes.size(); ++i)
    {
        auto nM = NodeGraphManager::Get();
        Node* newNode = NodeRegistry::CreateNode(mCopiedNodes[i]->GetNodeType(), nM->GetId(), mCurrentGraph);
        nM->IncrementId();
        mCurrentGraph->AddNode(newNode);
    }
}

void NodeEditorManager::NodeOptions()
{
    CreateNode();
}

void NodeEditorManager::CreateNode()
{
    Node** types = NodeRegistry::GetNodeTypes();
    unsigned short noOfTypes = NodeRegistry::GetNodeTypeCount();

    std::map<std::string, std::vector<Node*>> categorys;

    for (int i = 0; i < noOfTypes; i++)
    {
        categorys[types[i]->GetNodeCategory()].push_back(types[i]);
    }

    for (auto& category : categorys)
    {
        if (ImGui::BeginMenu(category.first.c_str()))
        {
            for (int i = 0; i < category.second.size(); i++)
            {
                std::string nodeName = category.second[i]->GetNodeName();

                if (ImGui::MenuItem(nodeName.c_str()))
                {
                    auto* graphManager = NodeGraphManager::Get();

                    graphManager->IncrementId();
                    const int nodeId = graphManager->GetId();
                    Node* newNode = NodeRegistry::CreateNode(category.second[i]->GetNodeType(), nodeId, mCurrentGraph);
                    ImNodes::SetNodeScreenSpacePos(nodeId, ImGui::GetMousePos());
                    mCurrentGraph->AddNode(newNode);
                }
            }
            ImGui::EndMenu();
        }
    }
}

void NodeEditorManager::DeleteNode(const int aId)
{
    auto& nodes = mCurrentGraph->GetNodes();
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->GetId() == aId)
        {
            mCurrentGraph->RemoveNode(aId);
        }
    }
}

void NodeEditorManager::DrawNodesAndLinks()
{
    if (!mCurrentGraph) return;

    for (Node* node : mCurrentGraph->GetNodes())
    {
        ImNodes::BeginNode(node->GetId(), node->IsStartNode());

        ImNodes::BeginNodeTitleBar();
        ImGui::TextUnformatted(node->GetNodeName().c_str());
        ImNodes::EndNodeTitleBar();

        for (auto* pin : node->GetPins())
        {
            DrawPin(pin);
        }

        ImNodes::EndNode();
    }

    for (Link& link : mCurrentGraph->GetLinks())
    {
        ImNodes::Link(link.id, link.startPin, link.endPin);
    }
}

void NodeEditorManager::DrawPin(Pin* aPin)
{
    switch (aPin->direction)
    {
    case PinDirection::In:
        DrawInPin(aPin);
        return;
    case PinDirection::Out:
        DrawOutPin(aPin);
        return;
    default:
        break;
    }

    switch (aPin->type)
    {
    case PinType::Bool:
    {
        bool b = std::any_cast<bool>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::PushItemWidth(120.f);
        ImGui::Checkbox(aPin->text.c_str(), &b);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = b;
        break;
    }
    case PinType::Int:
    {
        int integer = std::any_cast<int>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::TextUnformatted(aPin->text.c_str());
        ImGui::PushItemWidth(120.f);
        ImGui::InputInt("", &integer);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = integer;
        break;
    }
    case PinType::Float:
    {
        float f = std::any_cast<float>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::PushItemWidth(120.f);
        ImGui::InputFloat(aPin->text.c_str(), &f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = f;
        break;
    }
    case PinType::String:
    {
        char buf[256];
        std::string string = std::any_cast<std::string>(aPin->data);
        strncpy_s(buf, string.c_str(), sizeof(buf) - 1);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::TextUnformatted(aPin->text.c_str());
        ImGui::PushItemWidth(120.f);
        ImGui::InputText("##edit", buf, sizeof(buf));
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        string = buf;
        aPin->data = string;
        break;
    }
    }
}

void NodeEditorManager::DrawInPin(Pin* aPin)
{
    ImNodes::BeginInputAttribute(aPin->id);
    ImGui::TextUnformatted(aPin->text.c_str());
    ImNodes::EndInputAttribute();

    switch (aPin->type)
    {
    case PinType::Bool:
    {
        bool b = std::any_cast<bool>(aPin->data);
        aPin->data = b;
        break;
    }
    case PinType::Int:
    {
        int integer = std::any_cast<int>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::PushItemWidth(120.f);
        ImGui::InputInt("", &integer);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = integer;
        break;
    }
    case PinType::Float:
    {
        float f = std::any_cast<float>(aPin->data);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.f);
        ImGui::InputFloat("", &f, sizeof(float));
        ImGui::PopItemWidth();
        aPin->data = f;
        break;
    }
    case PinType::String:
    {
        char buf[256];
        std::string string = std::any_cast<std::string>(aPin->data);
        strncpy_s(buf, string.c_str(), sizeof(buf) - 1);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.f);
        ImGui::InputText("##edit", buf, sizeof(buf));
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        string = buf;
        aPin->data = string;
        break;
    }
    }
}

void NodeEditorManager::DrawOutPin(Pin* aPin)
{
    ImNodes::BeginOutputAttribute(aPin->id);
    ImGui::TextUnformatted(aPin->text.c_str());
    ImNodes::EndOutputAttribute();

    switch (aPin->type)
    {
    case PinType::Bool:
    {
        bool b = std::any_cast<bool>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.f);
        ImGui::Checkbox("", &b);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = b;
        break;
    }
    case PinType::Int:
    {
        int integer = std::any_cast<int>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::PushItemWidth(120.f);
        ImGui::InputInt("", &integer);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = integer;
        break;
    }
    case PinType::Float:
    {
        float f = std::any_cast<float>(aPin->data);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.f);
        ImGui::InputFloat("", &f);
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        aPin->data = f;
        break;
    }
    case PinType::String:
    {
        char buf[256];
        std::string string = std::any_cast<std::string>(aPin->data);
        strncpy_s(buf, string.c_str(), sizeof(buf) - 1);
        ImNodes::BeginStaticAttribute(aPin->id);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.f);
        ImGui::InputText("##edit", buf, sizeof(buf));
        ImGui::PopItemWidth();
        ImNodes::EndStaticAttribute();
        string = buf;
        aPin->data = string;
        break;
    }
    }
}

void NodeEditorManager::UpdateLinks()
{
    Link link;
    if (ImNodes::IsLinkCreated(&link.startPin, &link.endPin))
    {
        for (auto& node : mCurrentGraph->GetNodes())
        {
            for (auto& pin : node->GetPins())
            {
                if (link.endPin == pin->id)
                {
                    link.endNode = node;
                    continue;
                }
                if (link.startPin == pin->id)
                {
                    link.startNode = node;
                    continue;
                }
            }
        }
        NodeGraphManager* nM = NodeGraphManager::Get();
        link.id = nM->GetId();
        mCurrentGraph->AddLink(link);
        nM->IncrementId();
    }

    int linkId;
    if (ImNodes::IsLinkDestroyed(&linkId))
    {
        mCurrentGraph->RemoveLink(linkId);
    }
}
