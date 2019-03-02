#include "CGTAVC.h"
#include "CEntryInfoList.h"

void CEntryInfoNode::operator delete(void* data) {
	((void(__cdecl *)(void*))0x475A50)(data);
}

void* CEntryInfoNode::operator new(unsigned int size) {
	return ((void* (__cdecl *)(unsigned int))0x475A40)(size);
}

void CEntryInfoList::Flush() {
	((void(__thiscall *)(CEntryInfoList*))0x475A70)(this);
}