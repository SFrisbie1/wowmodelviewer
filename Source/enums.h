#ifndef ENUMS_H
#define ENUMS_H

enum InterfaceMode
{
	INTERFACEMODE_VIEWER,		// Default/Classic Viewer mode
	INTERFACEMODE_CINEMA		// Cinema Mode, for Machinima & the like.
};

enum Viewer_InterfaceType
{
	VIEWER_INTERFACETYPE_NONE,			// No File
	VIEWER_INTERFACETYPE_CHARACTER,		// Character M2 File
	VIEWER_INTERFACETYPE_CREATURE,		// Creatures & NPC M2 Files
	VIEWER_INTERFACETYPE_ITEM,			// M2 Models that aren't a Character, Creature or NPC.
	VIEWER_INTERFACETYPE_SET,			// WMO Files
	VIEWER_INTERFACETYPE_LANDSCAPE,		// ADT Files
	VIEWER_INTERFACETYPE_IMAGE,			// Image Files
	VIEWER_INTERFACETYPE_SOUND			// Sound Files
};

enum FileType
{
	FILETYPE_MODEL,		// M2 Files
	FILETYPE_SET,		// WMO Files
	FILETYPE_LANDSCAPE,	// ADT Files
	FILETYPE_IMAGE,		// BLP Files
	FILETYPE_SOUND		// WAV, OGG & MP3 Files
};

enum WoWVersion
{
	WOW_VANILLA = 10000,
	WOW_TBC = 20000,
	WOW_WOTLK = 30000,
	WOW_CATACLYSM = 40000
};

#endif
