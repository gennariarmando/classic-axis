#pragma once

#include "CVector.h"
#include "RenderWare.h"

class CMatrix {
public:
	CVector      right;
	unsigned int flags;
	CVector      up;
	unsigned int pad1;
	CVector      at;
	unsigned int pad2;
	CVector      pos;
	unsigned int pad3;

	RwMatrix *m_pAttachMatrix;
	unsigned int m_bOwnsAttachedMatrix;

	inline CMatrix() {
		this->m_pAttachMatrix = 0;
		this->m_bOwnsAttachedMatrix = 0;
	}

	//CMatrix() {}

	void Attach(RwMatrix* rwMatrix, bool deleteOnDetach);
	void AttachRW(RwMatrixTag* rwMatrix, bool deleteOnDetach);
	CMatrix(CMatrix const& src);
	CMatrix(RwMatrixTag* rwMatrix, bool deleteOnDetach);
	void CopyOnlyMatrix(CMatrix const& src);
	void Detach();
	void Reorthogonalise();
	void SetOrientation(float x, float y, float z);
	void ResetOrientation();
	void Rotate(float x, float y, float z);
	void RotateX(float angle);
	void RotateZ(float angle);
	void SetRotate(float x, float y, float z);
	void SetRotateX(float angle);
	void SetRotateXOnly(float angle);
	void SetRotateY(float angle);
	void SetRotateYOnly(float angle);
	void SetRotateZ(float angle);
	void SetRotateZOnly(float angle);
	void SetScale(float factor);
	void SetTranslate(float x, float y, float z);
	void SetUnity();
	void Update();
	void UpdateRW();
	void operator+=(CMatrix const& right);
	void operator=(CMatrix const& right);
	~CMatrix();
};

VALIDATE_SIZE(CMatrix, 0x48);

void Invert(CMatrix const& in, CMatrix&out);
CMatrix Invert(CMatrix const& in);
CMatrix operator*(CMatrix const& a, CMatrix const& b);
CVector operator*(CMatrix const& m, CVector const& v);
RwV3d operator*(CMatrix const& m, RwV3d const& v);
CVector Multiply3x3(CVector const& v, CMatrix const& m);
CVector Multiply3x3(CMatrix const& m, CVector const& v);