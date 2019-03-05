#include "CGTA3D.h"
#include "CEntity.h"

void __cdecl TransformPoint(CVector *outPoint, CPlaceable *placement, CVector const& point) {
	long double v3; // st7
	long double v4; // st6

	v3 = cos(placement->GetHeading());
	v4 = sin(placement->GetHeading());
	outPoint->x = v3 * point.x - v4 * point.y + placement->m_matrix.pos.x;
	outPoint->y = v3 * point.y + v4 * point.x + placement->m_matrix.pos.y;
	outPoint->z = placement->m_matrix.pos.z + point.z;
}

CVector CEntity::TransformFromObjectSpace(CVector const& offset) {
	CVector result; // 1
	RwMatrix *p = this->m_matrix.m_pAttachMatrix;
	if (p) {
		CVector point = operator*(this->m_matrix, offset);
		result.x = point.x;
		result.y = point.y;
		result.z = point.z;
	}
	else {
		TransformPoint(&result, this, offset);
	}
	return result;
}