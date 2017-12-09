#include "scenenode.h"

SceneNode::SceneNode(float X, float Y, float Z, float RotX, float RotY, float RotZ, float Scale)
{
	m_pModel = NULL;

	m_x = X;
	m_y = Y;
	m_z = Z;
	m_xangle = RotX;
	m_yangle = RotY;
	m_zangle = RotZ;
	m_scale = Scale;
}

void SceneNode::AddChildNode(SceneNode* Node)
{
	m_children.push_back(Node);
}

bool SceneNode::DetatchNode(SceneNode* Node)
{
	//traverse tree to find node to detatch
	for (int i = 0; i < m_children.size(); i++)
	{
		if (Node == m_children[i])
		{
			m_children.erase(m_children.begin() + i);
			return true;
		}
		if (m_children[i]->DetatchNode(Node) == true) return true;
	}

	return false; //note not in this tree
}

void SceneNode::Execute(XMMATRIX* World, XMMATRIX* View, XMMATRIX* Projection)
{
	//the local_world_matrix will be used to calc the local transformations fir this node
	XMMATRIX local_world = XMMatrixIdentity();

	local_world = XMMatrixScaling(m_scale, m_scale, m_scale);
	local_world *= XMMatrixRotationX(XMConvertToRadians(m_xangle));
	local_world *= XMMatrixRotationY(XMConvertToRadians(m_yangle));
	local_world *= XMMatrixRotationZ(XMConvertToRadians(m_zangle));
	local_world *= XMMatrixTranslation(m_x, m_y, m_z);

	//the local matrix is multiplied by the passed in world matrix that contains the concatenated
	//transformations of all parent nodes so that this nodes transformations are relative to those
	local_world *= *World;

	//only draw if there is a model attached
	if (m_pModel) m_pModel->Draw(&local_world, View, Projection);

	//traverse all child nodes, passing in the concatenated world matrix
	for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->Execute(&local_world, View, Projection);
	}	
}

void SceneNode::LookAt_XZ(float X, float Z)
{
	float DX = X - m_x;
	float DZ = Z - m_z;

	m_yangle = atan2(DX, DZ) * (180.0 / XM_PI);
}

void SceneNode::MoveForwards(float Distance)
{
	m_x += sin(m_yangle * (XM_PI / 180.0)) * Distance;
	m_z += cos(m_yangle * (XM_PI / 180.0)) * Distance;
}

bool SceneNode::CheckCollision(SceneNode* Node)
{
	return m_pModel->CheckCollision(Node->GetModel());
}

//SETTER
void SceneNode::SetPosX(float X) { m_x = X; }
void SceneNode::SetPosY(float Y) { m_y = Y; }
void SceneNode::SetPosZ(float Z) { m_z = Z; }
void SceneNode::SetRotX(float Amount) { m_xangle = Amount; }
void SceneNode::AddRotX(float Amount) { m_xangle += Amount; }
void SceneNode::SetRotY(float Amount) { m_yangle = Amount; }
void SceneNode::SetRotZ(float Amount) { m_zangle = Amount; }
//void SceneNode::SetScale(float Amount) { m_scale = Amount; }
void SceneNode::SetModel(Model* Model) { m_pModel = Model; }

//GETTER
Model* SceneNode::GetModel() { return m_pModel; };