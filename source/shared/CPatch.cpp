#include "CPatch.h"

void CPatch::Nop(int address, size_t size, bool vp) {
	injector::MakeNOP((address), size, vp);
}

void CPatch::RedirectCall(int address, void *func, bool vp) {
	injector::MakeCALL((address), func, vp);
}

void CPatch::RedirectJump(int address, void *func, bool vp) {
	injector::MakeJMP((address), func, vp);
}

void CPatch::SetChar(int address, char value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetUChar(int address, unsigned char value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetShort(int address, short value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetUShort(int address, unsigned short value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetInt(int address, int value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetUInt(int address, unsigned int value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetFloat(int address, float value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

void CPatch::SetPointer(int address, void *value, bool vp) {
	injector::WriteMemory((address), value, vp);
}

char CPatch::GetChar(int address, bool vp) {
	return injector::ReadMemory<char>((address), vp);
}

unsigned char CPatch::GetUChar(int address, bool vp) {
	return injector::ReadMemory<unsigned char>((address), vp);
}

short CPatch::GetShort(int address, bool vp) {
	return injector::ReadMemory<short>((address), vp);
}

unsigned short CPatch::GetUShort(int address, bool vp) {
	return injector::ReadMemory<unsigned short>((address), vp);
}

int CPatch::GetInt(int address, bool vp) {
	return injector::ReadMemory<int>((address), vp);
}

unsigned int CPatch::GetUInt(int address, bool vp) {
	return injector::ReadMemory<unsigned int>((address), vp);
}

float CPatch::GetFloat(int address, bool vp) {
	return injector::ReadMemory<float>((address), vp);
}

void *CPatch::GetPointer(int address, bool vp) {
	return injector::ReadMemory<void *>((address), vp);
}

void CPatch::ReplaceFunction(int address, void *func, bool vp) {
	RedirectJump(address, func, vp);
}

void CPatch::ReplaceFunctionCall(int address, void *func, bool vp) {
	RedirectCall(address, func, vp);
}

void CPatch::SetRaw(int address, void* value, size_t size, bool vp) {
	injector::WriteMemoryRaw((address), value, size, vp);
}

void CPatch::GetRaw(int address, void* ret, size_t size, bool vp) {

	injector::ReadMemoryRaw((address), ret, size, vp);
}

void CPatch::RedirectShortJump(int address, void* dest, bool vp) {

	int GlobalAddress = (address);
	injector::WriteMemory<uint8_t>(GlobalAddress, 0xEB, vp);
	if (dest)
		injector::MakeRelativeOffset(GlobalAddress + 1, dest, 1, vp);
}

void CPatch::PutRetn(int address, unsigned short BytesToPop, bool vp) {
	injector::MakeRET((address), BytesToPop, vp);
}

void CPatch::PutRetn0(int address, unsigned short BytesToPop, bool vp) {

	int GlobalAddress = (address);
	injector::WriteMemory(GlobalAddress, 0x33, vp); // xor eax, eax
	injector::WriteMemory(GlobalAddress + 1, 0xC0, vp);
	injector::MakeRET(GlobalAddress + 2, BytesToPop, vp);
}

CPatch* CPatch::ms_head = nullptr;

CPatch::CPatch(InjectPatches func)
	: m_func(func)
{
	m_next = ms_head;
	ms_head = this;
}

void CPatch::Inject()
{
	CPatch* current = ms_head;
	while (current != nullptr)
	{
		current->Run();
		current = current->m_next;
	}
	ms_head = nullptr;
}

int gtaversion = -1;
