#pragma once

class CCurrentVehicle {
public:
	class CVehicle *m_pCurrentVehicle;

	//funcs

	CCurrentVehicle();
	void Display();
	void Init();
	void Process();
};

VALIDATE_SIZE(CCurrentVehicle, 0x04);
