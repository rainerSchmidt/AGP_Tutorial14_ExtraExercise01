#pragma once
#include "model.h"
#define _XM_NO_INTINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class SceneNode
{
private:
	Model*				m_pModel;
	vector<SceneNode*>	m_children;

	float m_x, m_y, m_z;
	float m_xangle, m_zangle, m_yangle;
	float m_scale;

public:
	SceneNode(float X, float Y, float Z, float RotX, float RotY, float RotZ, float Scale);
	~SceneNode();

	void LookAt_XZ(float X, float Z);
	void MoveForwards(float Distance);
	bool CheckCollision(SceneNode* Node);

	float GetX();
	float GetY();
	float GetZ();
	float GetRotX();
	float GetRotY();
	float GetRotZ();
	float GetScale();
	Model* GetModel();

	void SetPosX(float pos);
	void SetPosY(float pos);
	void SetPosZ(float pos);
	void SetRotX(float rot);
	void AddRotX(float rot);
	void SetRotY(float rot);
	void SetRotZ(float rot);
	void SetScale(float amount);
	void SetModel(Model* Model);

	void AddChildNode(SceneNode* Node);
	bool DetatchNode(SceneNode* Node);
	void Execute(XMMATRIX* World, XMMATRIX* View, XMMATRIX* Projection);
};