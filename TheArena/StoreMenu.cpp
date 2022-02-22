#include "StoreMenu.h"

#include "gamedefs.h"
#include "languagepack.h"
#include "WeaponData.h"
#include "ArmorData.h"
#include "FileIO.h"

#include <iomanip>

#define STORE_LINEWIDTH 52
#define STORE_TEXTCOLOR ConColor::BkgBlue | ConColor::White
#define STORE_HIGHLIGHT ConColor::BkgPurple | ConColor::White

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphicsData::ConColor;

	StoreMenu::StoreMenu(LPPLAYERENTITY player, int x, int y, LPDATA data) 
		: BaseSelector(STORE_TEXTCOLOR, STORE_HIGHLIGHT, STORE_LINEWIDTH)
	{
		pauseTime = clock();
		_player = player;
		_data = data;
		// Hook up keyboard to menu system
		_controller = _player->GetMover()->GetController();
		// Set current selected item to the top of the list
		memset(&TD, 0, sizeof(TD));
		currentTab = ST_MELEE;
		// Set how long between keyboard checks
		pauseAmount = 100;
		pos.x = x;
		pos.y = y;

		box = { x, y, 60, 20 };

		// Set the current tab data structure to melee
		currentTD = &TD[ST_MELEE];
		TD[0].type = ST_ARMOR;
		TD[1].type = ST_POTIONS;
		TD[2].type = ST_MELEE;
		TD[3].type = ST_RANGED;

		_isDirty = true;
		color = ConColor::BkgBlue | ConColor::LtBlue;
		//textColor = ConColor::BkgBlue | ConColor::White;
		//highlightColor = ConColor::BkgPurple | ConColor::White;
		tabColor = ConColor::BkgRed | ConColor::LtGreen;
		tabHighColor = ConColor::BkgGreen | ConColor::White;
	}

	StoreMenu::~StoreMenu()
	{

	}

	int StoreMenu::DrawTab(Zaxis::Graphics::ConGraphics* cGfx, std::string tab, int x, int y, bool IsSelected)
	{
		std::ostringstream out;
		out << "[" << tab << "]";
		cGfx->DrawText(out.str(), x, y, IsSelected ? tabHighColor : tabColor);

		return out.str().length() + x;
	}

	void StoreMenu::Update()
	{
		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(EXITKEY))
		{
			// Unpause the game
			_stateManager->Pause(false);
			// Menu is done player wants to exit
			_stateManager->PopState();
			return;
		}

		// Check if we have waited long enough for the next key input
		clock_t pauseCount = clock() - pauseTime;
		if (pauseCount > pauseAmount)
		{
			if (_controller->ChkInput(VK_UP))
			{
				if (currentTD->lineItem > 0)
				{
					currentTD->lineItem--;
					pauseTime = clock();
				}
			}
			if (_controller->ChkInput(VK_DOWN))
			{
				if (currentTD->lineItem < currentTD->MaxItemsInList)
				{
					currentTD->lineItem++;
					pauseTime = clock();
				}
			}
			currentTD->itemStart = 0;
			if (currentTD->lineItem >= MAX_SHOW_ITEMS)
			{
				currentTD->itemStart = (currentTD->lineItem - MAX_SHOW_ITEMS) + 1;
			}

			if (_controller->ChkInput(VK_RIGHT))
			{
				currentTab = (currentTab + 1) % 4;
				pauseTime = clock();
			}

			if (_controller->ChkInput(VK_LEFT))
			{
				if (currentTab == 0)
				{
					currentTab = 3;
				}
				else
				{
					currentTab--;
				}
				pauseTime = clock();
			}

			currentTD = &TD[currentTab];

			if (_controller->ChkInput(VK_RETURN))
			{
				switch (currentTD->type)
				{
				case ST_ARMOR:
					{
						int idx = currentTD->lineItem - currentTD->itemStart;
						Game::Data::ArmorData a = _data->GetArmor(currentTD->itemList[idx]);
						if (_player->GetLevel()->Gold > a.price)
						{
							// Take gold from player
							_player->GetLevel()->Gold -= a.price;
							_player->LoadArmor(a.id);
							_player->SetArmor(a.id);
							// Close down store
							_stateManager->Pause(false);
							_stateManager->PopState();
							return;
						}
					}
					break;
				case ST_RANGED:
					{
						// Player wants to buiy an item!
						Zaxis::FileData<Game::Data::WeaponData> data;
						int idx = currentTD->lineItem - currentTD->itemStart;
						Game::Data::WeaponData w = _data->GetWeapon(currentTD->itemList[idx]);
						if (_player->GetLevel()->Gold > w.price)
						{
							// Take gold from player
							_player->GetLevel()->Gold -= w.price;
							_player->SetWeapon(w);
							_player->SetWeapon(w.Id);
							// Close down store
							_stateManager->Pause(false);
							_stateManager->PopState();
							return;
						}// Endif Player has the gold to buy item
					}
					break;
				case ST_MELEE:
					{
						// Player wants to buiy an item!
						Zaxis::FileData<Game::Data::WeaponData> data;
						int idx = currentTD->lineItem - currentTD->itemStart;
						Game::Data::WeaponData w = _data->GetWeapon(currentTD->itemList[idx]);
						if (_player->GetLevel()->Gold > w.price)
						{
							// Take gold from player
							_player->GetLevel()->Gold -= w.price;
							_player->SetWeapon(w);
							_player->SetWeapon(w.Id);
							// Close down store
							_stateManager->Pause(false);
							_stateManager->PopState();
							return;
						}// Endif Player has the gold to buy item
					}
					break;
			}
		}

			if (pauseTime == clock())
			{
				// Redraw menu
				DirtyMe();
			}
		}

	}

	void StoreMenu::Draw(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		int x;
		int y;
		// Draw menu background
		cGfx->DrawFillRect(&box, Zaxis::Graphics::ConGraphicsData::BoxType::Antique, color);
		// Draw menu title
		std::string title(SM_TITLE);
		x = pos.x + (box.Width / 2) - ((title.length() + 2)/ 2);
		std::string line(title.length() + 2, ' ');
		line[0] = 221;
		line[line.length() - 1] = 222;
		cGfx->DrawText(line, x, pos.y, color);
		cGfx->DrawText(title, x + 1, pos.y, ConColor::BkgBlue | ConColor::LtYellow);

		// Draw tabs on menu
		x = pos.x;
		y = pos.y + 1;
		std::string tabLine(box.Width - 2, ' ');
		cGfx->DrawText(tabLine, x + 1, y, tabColor);
		x = DrawTab(cGfx, SM_MELEETAB, x + 2, y, currentTab == StoreTabs::ST_MELEE);
		x = DrawTab(cGfx, SM_RANGETAB, x + 1, y, currentTab == StoreTabs::ST_RANGED);
		x = DrawTab(cGfx, SM_ARMORTAB, x + 1, y, currentTab == StoreTabs::ST_ARMOR);
		x = DrawTab(cGfx, SM_POTIONTAB, x + 1, y, currentTab == StoreTabs::ST_POTIONS);

		x = pos.x + 2;
		y = y + 2;
		switch (currentTab)
		{
		case StoreTabs::ST_ARMOR:
			{
				unsigned int idx = 0;
				unsigned int headIdx = currentTD->itemStart;
				currentTD->MaxItemsInList = 0;
				memset(currentTD->itemList, 0, sizeof(currentTD->itemList));
				for (int i = 0; i < 256; i++)
				{
					if (_data->GetArmor(i).id == 0)
					{
						break;
					}
					currentTD->MaxItemsInList++;
					if (headIdx > 0)
					{
						headIdx--;
					}
					else
					{
						currentTD->itemList[idx++] = i;
						if (idx == MAX_SHOW_ITEMS) break;
					}
				}

				// Draw the items to the screen
				for (int i = 0; i < MAX_SHOW_ITEMS; i++)
				{
					std::ostringstream out;
					idx = currentTD->itemList[i];
					out << std::setw(38) << std::left << ItemName(_data->GetArmor(idx).name, _data->GetArmor(idx).plus) << std::setw(12) << std::right << _data->GetArmor(idx).price;
					int chkIdx = i + currentTD->itemStart;
					DrawLine(cGfx, out.str(), x, y++, chkIdx == currentTD->lineItem);
					//cGfx->DrawText(out.str(), x, y++, chkIdx == currentTD->lineItem ? highlightColor : textColor);
				}
			}
			break;
		case StoreTabs::ST_MELEE:
			{
				// List of melee weapons
				unsigned int idx = 0;
				unsigned int headIdx = currentTD->itemStart;
				currentTD->MaxItemsInList = 0;
				for (int i = 0; i < 256; i++)
				{
					if (_data->GetWeapon(i).Id == 0)
					{
						break;
					}

					if (_data->GetWeapon(i).range == 1 && _data->GetWeapon(i).price > 0)
					{
						currentTD->MaxItemsInList++;
						if (headIdx > 0)
						{
							headIdx--;
						}
						else
						{
							// Add item to list
							currentTD->itemList[idx++] = i;
							if (idx == MAX_SHOW_ITEMS) break;
						}
					}
					
				} 

				// Draw the items to the screen
				for (int i = 0; i < MAX_SHOW_ITEMS; i++)
				{
					std::ostringstream out;
					idx = currentTD->itemList[i];
					out << std::setw(38) << std::left << ItemName(_data->GetWeapon(idx).name, _data->GetWeapon(idx).plus) << std::setw(12) << std::right << _data->GetWeapon(idx).price;
					int chkIdx = i + currentTD->itemStart;
					DrawLine(cGfx, out.str(), x, y++, chkIdx == currentTD->lineItem);
					//cGfx->DrawText(out.str(), x, y++, chkIdx == currentTD->lineItem ? highlightColor : textColor);
				}
			}
			break;
		case StoreTabs::ST_RANGED:
			{
				// List of melee weapons
				unsigned int idx = 0;
				unsigned int headIdx = currentTD->itemStart;
				currentTD->MaxItemsInList = 0;
				memset(currentTD->itemList, 0, sizeof(currentTD->itemList));
				for (int i = 0; i < 256; i++)
				{
					// Check if we have hit the end of the weapon list
					if (_data->GetWeapon(i).Id == 0)
					{
						break;
					}

					if (_data->GetWeapon(i).range > 1 && _data->GetWeapon(i).price > 0)
					{
						currentTD->MaxItemsInList++;
						if (headIdx > 0)
						{
							headIdx--;
						}
						else
						{
							// Add item to list
							currentTD->itemList[idx++] = i;
							if (idx == MAX_SHOW_ITEMS) break;
						}
					}
				}

				// Draw the items to the screen
				for (int i = 0; i < MAX_SHOW_ITEMS; i++)
				{
					std::ostringstream out;
					idx = currentTD->itemList[i];
					out << std::setw(38) << std::left << ItemName(_data->GetWeapon(idx).name, _data->GetWeapon(idx).plus) << std::setw(12) << std::right << _data->GetWeapon(idx).price;
					int chkIdx = i + currentTD->itemStart;
					DrawLine(cGfx, out.str(), x, y++, chkIdx == currentTD->lineItem);
					//cGfx->DrawText(out.str(), x, y++, chkIdx == currentTD->lineItem ? highlightColor : textColor);
				}
			}
			break;
		case StoreTabs::ST_POTIONS:
			{
				cGfx->DrawText("Potions!", x, y++, STORE_TEXTCOLOR);

			}
			break;

		}

		// Display store commands
		std::ostringstream out;
		out << SM_TABLEFT << " " << SM_TABRIGHT << " " << SM_BUYITEM;
		cGfx->DrawText(out.str(), box.X + 3, (box.Y + box.Height) - 1, STORE_TEXTCOLOR);
		out.str(""); out.clear();

		_isDirty = false;
	}

	std::string StoreMenu::ItemName(unsigned char name[38], int plus)
	{
		std::ostringstream out;
		out << name;
		if (plus > 0)
		{
			out << " +" << plus;
		}
		else if (plus < 0)
		{
			out << " " << plus;
		}

		return out.str();
	}

	std::string StoreMenu::ItemName(char name[30], int plus)
	{
		std::ostringstream out;
		out << name;
		if (plus > 0)
		{
			out << " +" << plus;
		}
		else if (plus < 0)
		{
			out << " " << plus;
		}

		return out.str();
	}

	void StoreMenu::Clear(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	bool StoreMenu::Shutdown()
	{
		return false;
	}

	bool StoreMenu::IsDirty()
	{
		return _isDirty;
	}

	void StoreMenu::DirtyMe()
	{
		_isDirty = true;
	}

	void StoreMenu::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
		// Stop game simulating
		_stateManager->Pause(true);
	}


} } }// End namsepsace Game::Graphics::Menus