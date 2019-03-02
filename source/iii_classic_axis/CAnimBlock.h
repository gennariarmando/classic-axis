#pragma once

class CAnimBlock {
public:
	char name[24];
	int animIndex;	// into CAnimBlock::ms_aAnimations[]
	int numAnims;
};