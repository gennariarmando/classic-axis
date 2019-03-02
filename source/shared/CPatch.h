#include "../injector/injector.hpp"

class CPatch {
public:
	static void Nop(int address, size_t size, bool vp = true);
	static void RedirectCall(int address, void *func, bool vp = true);
	static void RedirectJump(int address, void *func, bool vp = true);
	static void SetChar(int address, char value, bool vp = true);
	static void SetUChar(int address, unsigned char value, bool vp = true);
	static void SetShort(int address, short value, bool vp = true);
	static void SetUShort(int address, unsigned short value, bool vp = true);
	static void SetInt(int address, int value, bool vp = true);
	static void SetUInt(int address, unsigned int value, bool vp = true);
	static void SetFloat(int address, float value, bool vp = true);
	static void SetPointer(int address, void *value, bool vp = true);
	static char GetChar(int address, bool vp = true);
	static unsigned char GetUChar(int address, bool vp = true);
	static short GetShort(int address, bool vp = true);
	static unsigned short GetUShort(int address, bool vp = true);
	static int GetInt(int address, bool vp = true);
	static unsigned int GetUInt(int address, bool vp = true);
	static float GetFloat(int address, bool vp = true);
	static void *GetPointer(int address, bool vp = true);
	static void SetRaw(int address, void* value, size_t size, bool vp = true);
	static void GetRaw(int address, void* ret, size_t size, bool vp = true);
	static void RedirectShortJump(int address, void* dest = nullptr, bool vp = true);
	static void PutRetn(int address, unsigned short BytesToPop = 0, bool vp = true);
	static void PutRetn0(int address, unsigned short BytesToPop = 0, bool vp = true);

	template <typename T>
	static void Set(int address, T value, bool vp = true) {
		injector::WriteMemory((address), value, vp);
	}

	template <typename T>
	static T Get(int address, bool vp = true) {
		return injector::ReadMemory<T>((address), vp);
	}

	template <typename T>
	static T TranslateCallOffset(int address) {
		if (GetUChar(address) == 0xE8) {
			auto offset = GetInt(address + 1);
			offset += ((address) + 5);
			return reinterpret_cast<T>(offset);
		}
		return nullptr;
	}

	template <typename T>
	static T TranslateJumpOffset(int address) {
		if (GetUChar(address) == 0xE9) {
			auto offset = GetInt(address + 1);
			offset += ((address) + 5);
			return reinterpret_cast<T>(offset);
		}
		return nullptr;
	}

	static void ReplaceFunction(int address, void *func, bool vp = true);
	static void ReplaceFunctionCall(int address, void *func, bool vp = true);

private:
	using InjectPatches = void(*)();

	InjectPatches m_func;
	CPatch*	m_next;

	static CPatch* ms_head;

private:
	void Run() { m_func(); }

public:
	CPatch(InjectPatches func);

	static void	Inject();
};

// From MemoryMgr
enum {
	III_10 = 1,
	III_11,
	III_STEAM,
	VC_10,
	VC_11,
	VC_STEAM
};

extern int gtaversion;

template<typename T>
inline T AddressByVersion(uintptr_t addressIII10, uintptr_t addressIII11, uintptr_t addressIIISteam, uintptr_t addressvc10, uintptr_t addressvc11, uintptr_t addressvcSteam) {
	if (gtaversion == -1) {
		if (*(uintptr_t*)0x5C1E75 == 0xB85548EC) gtaversion = III_10;
		else if (*(uintptr_t*)0x5C2135 == 0xB85548EC) gtaversion = III_11;
		else if (*(uintptr_t*)0x5C6FD5 == 0xB85548EC) gtaversion = III_STEAM;
		else if (*(uintptr_t*)0x667BF5 == 0xB85548EC) gtaversion = VC_10;
		else if (*(uintptr_t*)0x667C45 == 0xB85548EC) gtaversion = VC_11;
		else if (*(uintptr_t*)0x666BA5 == 0xB85548EC) gtaversion = VC_STEAM;
		else gtaversion = 0;
	}
	switch (gtaversion) {
	case III_10:
		return (T)addressIII10;
	case III_11:
		return (T)addressIII11;
	case III_STEAM:
		return (T)addressIIISteam;
	case VC_10:
		return (T)addressvc10;
	case VC_11:
		return (T)addressvc11;
	case VC_STEAM:
		return (T)addressvcSteam;
	default:
		return (T)0;
	}
}

inline bool
is10(void)
{
	return gtaversion == III_10 || gtaversion == VC_10;
}

inline bool
isIII(void)
{
	return gtaversion >= III_10 && gtaversion <= III_STEAM;
}

inline bool
isVC(void)
{
	return gtaversion >= VC_10 && gtaversion <= VC_STEAM;
}