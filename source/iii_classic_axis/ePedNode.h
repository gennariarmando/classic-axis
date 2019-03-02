#pragma once

enum ePedNode {
	PED_WAIST,
	PED_TORSO,	// Smid on PS2/PC, Storso on mobile/xbox. We follow mobile/xbox (makes kicking on ground look better)
	PED_HEAD,
	PED_UPPERARML,
	PED_UPPERARMR,
	PED_HANDL,
	PED_HANDR,
	PED_UPPERLEGL,
	PED_UPPERLEGR,
	PED_FOOTL,
	PED_FOOTR,
	PED_LOWERLEGR,
	// This is not valid apparently
	PED_LOWERLEGL,
	// actual fixed nodes needed for hit col model
	PED_ACTUAL_TORSO,
	PED_ACTUAL_MID,
};