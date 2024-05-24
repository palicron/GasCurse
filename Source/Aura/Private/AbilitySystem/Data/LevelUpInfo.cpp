// CAS Tutorial JsPalacios


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXp(int32 XP) const
{
	int32 level = 1;
	bool bSearching = true;

	while(bSearching)
	{
		if(LevelUpInfos.Num() -1 <= level)
		{
			return level;
		}

		if(XP >= LevelUpInfos[level].LevelUpRequirement)
		{
			level++;
		}
		else
		{
			bSearching = false;
		}
	}

	return level;
	
}
