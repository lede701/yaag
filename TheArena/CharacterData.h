#ifndef H_CHARACTERDATA
#define H_CHARACTERDATA

#define INTSTAT int
#define UINTSTAT unsigned int

#define LPCHARACTER Game::Data::CharacterData*

namespace Game{ namespace Data
{
	struct CharacterData
	{
	public:
		UINTSTAT dataId; // Used to know list position when added to an item list
		INTSTAT Str;
		INTSTAT Dex;
		INTSTAT Con;
		INTSTAT Int;
		INTSTAT Health;
		INTSTAT MaxHealth;
		INTSTAT HealingSpeed;
		INTSTAT HealingAmount;
		INTSTAT NextHealing;
		INTSTAT Mana;
		INTSTAT MaxMana;
		INTSTAT ManaRegen;
		INTSTAT ManaRegenSpeed;
		INTSTAT NextMana;
		INTSTAT AttackRating;
		INTSTAT AttackDamage;
		INTSTAT AttackMinDamage;
		INTSTAT AttackBonus;
		INTSTAT AttackSpeed;
		INTSTAT AttackRange;
		INTSTAT NextAttack;
		INTSTAT DefenseRating;
		INTSTAT DefenseBonus;

		INTSTAT Speed;
		INTSTAT Move;
		INTSTAT NextMove;

		CharacterData();
		CharacterData(const CharacterData &data);
		virtual ~CharacterData();

		void Init();
		void Init(const CharacterData &data);

		void Update();

		void Add(LPCHARACTER data);

		int GetScore();

		// Character data management
		static INTSTAT NextStatId;
		static INTSTAT GetNextId();

		CharacterData operator+(const CharacterData &data);
		CharacterData operator-(const CharacterData &data);

	};

} }// End namespace Game::Stats

#endif