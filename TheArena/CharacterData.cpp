#include "CharacterData.h"

namespace Game{ namespace Data
{

	int CharacterData::NextStatId = 0;
	int CharacterData::GetNextId()
	{
		INTSTAT id = NextStatId++;
		return id;
	}

	CharacterData::CharacterData()
	{
		Init();
	}

	CharacterData::CharacterData(const CharacterData &data)
	{
		Init(data);
	}

	void CharacterData::Init(const CharacterData &data)
	{
		dataId = CharacterData::GetNextId();
		Str = data.Str;
		Dex = data.Dex;
		Con = data.Con;
		Int = data.Int;
		Health = data.Health;
		MaxHealth = data.MaxHealth;
		HealingSpeed = data.HealingSpeed;
		HealingAmount = data.HealingAmount;
		NextHealing = data.NextHealing;
		Mana = data.Mana;
		MaxMana = data.MaxMana;
		ManaRegen = data.ManaRegen;
		ManaRegenSpeed = data.ManaRegenSpeed;
		NextMana = data.NextMana;
		AttackRating = data.AttackRating;
		AttackMinDamage = data.AttackMinDamage;
		AttackBonus = 0;
		AttackDamage = data.AttackDamage;
		AttackSpeed = data.AttackSpeed;
		AttackRange = data.AttackRange;
		NextAttack = data.NextAttack;
		DefenseRating = data.DefenseRating;
		DefenseBonus = 0;
		Speed = data.Speed;
		Move = data.Move;
		NextMove = data.NextMove;
	}

	void CharacterData::Init()
	{
		dataId = CharacterData::GetNextId();
		Str = 0;
		Dex = 0;
		Con = 0;
		Int = 0;
		Health = 0;
		MaxHealth = 0;
		HealingSpeed = 0;
		HealingAmount = 0;
		NextHealing = 0;
		Mana = 0;
		MaxMana = 0;
		ManaRegen = 0;
		ManaRegenSpeed = 0;
		NextMana = 0;
		AttackRating = 0;
		AttackMinDamage = 0;
		AttackBonus = 0;
		AttackDamage = 0;
		AttackSpeed = 0;
		AttackRange = 0;
		NextAttack = 0;
		DefenseRating = 0;
		DefenseBonus = 0;
		Speed = 0;
		Move = 0;
		NextMove = 0;
	}

	CharacterData::~CharacterData()
	{
	}

	void CharacterData::Update()
	{
		AttackDamage = static_cast<INTSTAT>(Str * 1.5);
	}

	int CharacterData::GetScore()
	{
		// Create a percentage based on life left on player
		return static_cast<int>(AttackMinDamage + AttackBonus + AttackDamage + DefenseBonus + DefenseRating + Health);
	}

	/********************************
	* Operator Overloads
	*********************************/

	CharacterData CharacterData::operator+(const CharacterData &data)
	{
		CharacterData newdata(data);
		newdata.Str += Str;
		newdata.Dex += Dex;
		newdata.Con += Con;
		newdata.Int += Int;
		newdata.Health += Health;
		newdata.MaxHealth += MaxHealth;
		newdata.HealingSpeed += HealingSpeed;
		newdata.HealingAmount += HealingAmount;
		newdata.NextHealing += NextHealing;
		newdata.Mana += Mana;
		newdata.MaxMana += MaxMana;
		newdata.ManaRegen += ManaRegen;
		newdata.ManaRegenSpeed += ManaRegenSpeed;
		newdata.NextMana += NextMana;
		newdata.AttackRating += AttackRating;
		newdata.AttackMinDamage += AttackMinDamage;
		newdata.AttackBonus += AttackBonus;
		newdata.AttackDamage += AttackDamage;
		newdata.AttackSpeed += AttackSpeed;
		newdata.AttackRange += AttackRange;
		newdata.NextAttack += NextAttack;
		newdata.DefenseRating += DefenseRating;
		newdata.DefenseBonus += DefenseBonus;
		newdata.Speed += Speed;
		newdata.Move += Move;
		newdata.NextMove += NextMove;

		return newdata;
	}

	void CharacterData::Add(LPCHARACTER data)
	{
		Str += data->Str;
		Dex += data->Dex;
		Con += data->Con;
		Int += data->Int;
		Health += data->Health;
		MaxHealth += data->MaxHealth;
		HealingSpeed += data->HealingSpeed;
		HealingAmount += data->HealingAmount;
		NextHealing += data->NextHealing;
		Mana += data->Mana;
		MaxMana += data->MaxMana;
		ManaRegen += data->ManaRegen;
		ManaRegenSpeed += data->ManaRegenSpeed;
		NextMana += data->NextMana;
		AttackRating += data->AttackRating;
		AttackMinDamage += data->AttackMinDamage;
		AttackBonus += data->AttackBonus;
		AttackDamage += data->AttackDamage;
		AttackSpeed += data->AttackSpeed;
		AttackRange += data->AttackRange;
		NextAttack += data->NextAttack;
		DefenseRating += data->DefenseRating;
		DefenseBonus += data->DefenseBonus;
		Speed += data->Speed;
		Move += data->Move;
		NextMove += data->NextMove;
	}


	CharacterData CharacterData::operator-(const CharacterData &data)
	{
		CharacterData newdata(data);
		newdata.Str -= Str;
		newdata.Dex -= Dex;
		newdata.Con -= Con;
		newdata.Int -= Int;
		newdata.Health -= Health;
		newdata.MaxHealth -= MaxHealth;
		newdata.HealingSpeed -= HealingSpeed;
		newdata.HealingAmount -= HealingAmount;
		newdata.NextHealing -= NextHealing;
		newdata.Mana -= Mana;
		newdata.MaxMana -= MaxMana;
		newdata.ManaRegen -= ManaRegen;
		newdata.ManaRegenSpeed -= ManaRegenSpeed;
		newdata.NextMana -= NextMana;
		newdata.AttackRating -= AttackRating;
		newdata.AttackMinDamage -= AttackMinDamage;
		newdata.AttackBonus -= AttackBonus;
		newdata.AttackDamage -= AttackDamage;
		newdata.AttackSpeed -= AttackSpeed;
		newdata.AttackRange -= AttackRange;
		newdata.NextAttack -= NextAttack;
		newdata.DefenseRating -= DefenseRating;
		newdata.DefenseBonus -= DefenseBonus;
		newdata.Speed -= Speed;
		newdata.Move -= Move;
		newdata.NextMove -= NextMove;

		return newdata;
	}

} }// End namespace Game::Stats