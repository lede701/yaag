#ifndef H_ENGLISHPACK
#define H_ENGLISHPACK

// Global game keys
#define EXITKEY 'X'
#define EXITTEXT "Exit"
#define CONTINUEKEY 'C'
#define CONTINUETEXT "Continue"
#define ANYKEYTEXT "Press any key to continue"
#define DONEKEY 'D'
#define DONETEXT "Done"

// Player prompts 
#define PLAYERNAMEPROMPT "Enter GameJolt User:"
#define CREATEPLAYERNAMEPROMPT "Character Name:"
#define PASSWORDPROMPT "Enter Token:"
#define CONFIRMPROMPT "Confirm Password:"

// Create player messages
#define ERROR_CONFIRM "Your password didn't match please enter your password"
#define ERROR_ACCOUNTEXISTS "Account is already in use!"
#define CREATEDSUCCESS "Player created!"

// Game Text Commands
#define GAMEQUIT "QUIT"
#define GAMEEXIT "EXIT"
#define GAMELIST "LISTALL"
#define GAMELIST2 "LIST"
#define TOP10 "TOP10"
#define GAMECREATE "NEW"
#define GAMEHELP "HELP"
#define CONTINUEMSG "Press [ENTER] to continue"
#define LM_LOGINKEY 'L'
#define LM_LOGINTEXT "Login"
#define LM_HELPKEY 'H'
#define LM_HELPTEXT "Help"
#define LM_CREATEKEY 'N'
#define LM_CREATETEXT "New Player"
#define LM_LISTKEY 'S'
#define LM_LISTTEXT "Show Players"
#define LM_QUITKEY 'Q'
#define LM_QUITTEXT "Quit"
#define LM_CONFIGKEY 'C'
#define LM_CONFIGTEXT "Game Configuration"


// Login messages
#define NOACCOUNT "Account name and password do not match"
#define DBMISSING "Error data file missing!"

// List players messages
#define PLLISTHEADING "List of Players"
#define PLNAME "Player Name"
#define PLLEVEL "Level"
#define PLWINS "Wins"
#define PLLOSSES "Losses"
#define PLDEATHS "Deaths"
#define PLEXP  "Exp."

// New Player Messages
#define NEWWELCOME "Welcome to The Arena!  You have just entered into a new chapter of your life filled\nwith adventure, fighting, and fans. Do you have what it takes to get to the top?"
#define LOGINMSG "To enter the Arena just type in your name and password or type HELP for\nmore options."
#define CREAETACCOUNT "Welcome fighter to The Arena.  Please tell us your name so we will know what\nto carve on your tomb stone."
#define LOGINHELP "Login Help\n \nQUIT    - Exit game without logging in.\nNEW     - Create a new player.\nLISTALL - List all registered players."

// Player Game Menu
#define KEYATTACKMENU "Attack"

// Select Monster Menu
#define SMM_TITLE "Select Monster"

// Level Up Menu
#define LUM_TITLE "Level Up"
#define LUM_POINTS "Points"

// Player menu commands
#define CMD_LEVELUPKEY 'L'
#define CMD_LEVELUPTEXT "Level Up"
#define CMD_STOREKEY 'S'
#define CMD_STORETEXT "The Store"
#define CMD_HEALKEY 'H'
#define CMD_HEALTEXT "Heal"
#define CMD_RANDOMKEY 'R'
#define CMD_RANDOMTEXT "Random Monster"
#define CMD_ENTERARENAKEY 'E'
#define CMD_ENTERARENATEXT "Enter the Arena"
#define CMD_PLAYERLISTKEY 'P'
#define CMD_PLAYERLISTTEXT "Player List"
#define CMD_UPKEY "UP"
#define CMD_UPSELECT "Move Selection Up"
#define CMD_DOWNKEY "DOWN"
#define CMD_DOWNSELECT "Move Selection Down"
#define CMD_ENTERKEY "ENTER"
#define CMD_SELECTMONSTER "Fight Monster"
#define CMD_SELECTWEAPON "Buy Weapon"
#define CMD_SELECTBOW "Buy Bow"
#define CMD_SELECTARMOR "Buy Armor"
#define CMD_SELECTPOTION "Buy Potion"

// Player Stats
#define PS_STR "Str"
#define PS_DEX "Dex"
#define PS_CON "Con"
#define PS_INT "Int"
#define PS_HEALTH "Health"
#define PS_SPEED "Speed"
#define PS_HEAL "Heal"
#define PS_SAVETEXT "Save"
#define PS_SAVEKEY 'S'


// Player game menu
#define PG_YOU "YOU"
#define PG_WEAPON "Weapon"
#define PG_ARMOR "Armor"
#define PG_HEALTH "Health"
#define PG_LEVEL "Level"
#define PG_EXPERIENCE "Exp."

// Store commands
#define SM_TITLE  "The Shop"
#define SM_MELEETAB "Swords"
#define SM_RANGETAB "Bows"
#define SM_ARMORTAB "Armor"
#define SM_POTIONTAB "Potions"
#define SM_TABLEFT "[<-] Left one tab"
#define SM_TABRIGHT "[->] Right one tab"
#define SM_BUYITEM "[ENTER] Buy Item"

// Win messages
#define WIN_TEXT "Congradulations you have won!"
#define WIN_EXP "You have gained %i experience"
#define WIN_GOLD "and %i gold."
#define WIN_FLEE_TEXT "Congradulations you have won because your oppent was scared of you!"
#define WIN_FLEE_EXP "You earned no experience."
#define WIN_FLEE_GOLD "But you have earned %i gold for the fight."

// Player lost
#define LOSS_TEXT1 "Sorry you don't have enough gold to revive this"
#define LOSS_TEXT2 "character.  Press the [ESC] return to town."
#define LOSS_EXIT VK_ESCAPE

// Player List Commands
#define PLIST_SELECTKEY "Enter"
#define PLIST_SELECTTEXT "View selected player"

// Configuration text
#define CFG_TITLE "Configuration"

#endif