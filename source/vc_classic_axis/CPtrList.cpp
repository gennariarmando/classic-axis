#include "CGTAVC.h"
#include "CPtrList.h"

// Converted from cdecl void CPtrNode::operator delete(void *data) 0x4A3DE0
void CPtrNode::operator delete(void* data) {
	((void(__cdecl *)(void*))0x4A3DE0)(data);
}

// Converted from cdecl void* CPtrNode::operator new(uint size) 0x4A3DD0
void* CPtrNode::operator new(unsigned int size) {
	return ((void* (__cdecl *)(unsigned int))0x4A3DD0)(size);
}

// Converted from thiscall void CPtrList::Flush(void) 0x4A3E00
void CPtrList::Flush() {
	((void(__thiscall *)(CPtrList*))0x4A3E00)(this);
}
