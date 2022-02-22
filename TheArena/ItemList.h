#ifndef H_ITEMLIST
#define H_ITEMLIST

namespace Game{ namespace Data
{ 

	enum ItemList
	{
		IL_NONE = 0x0000,
		IL_STICK = 0x0001,
		IL_SWORD = 0x0002,
		IL_DAGGER = 0x0003,
		IL_SLING = 0x0004,
		IL_BOW = 0x0005,
		IL_MACE = 0x0006,
		IL_LONGBOW = 0x0007,
		IL_COMPOUNDBOW = 0x0008,
		IL_BROADSWORD = 0x0009,
		IL_LONGSWORD = 0x0010,
		IL_BREAST = 0x0011,
		IL_HELM = 0x0012,
		IL_GLOVES = 0x0013,
		IL_WAND = 0x0014
	};

	enum ItemMaterial
	{
		IM_NONE = 0x0000,
		IM_HANDS = 0x0100,
		IM_WOOD = 0x0200,
		IM_CLOTH = 0x0300,
		IM_LEATHER = 0x0400,
		IM_RUSTED = 0x0500,
		IM_IRON = 0x0600,
		IM_HARDWOOD = 0x0700,
		IM_STEAL = 0x0800,
		IM_MITHRIL = 0x0900,
		IM_DIAMOND = 0x1000,
		IM_GOLD = 0x1100,
		IM_BONE = 0x1200,
		IM_SCALE = 0x1300
	};


} }// End namespace Game::Data
#endif