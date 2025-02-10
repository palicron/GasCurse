// CAS Tutorial JsPalacios


#include "Game/LoadScreenSaveGame.h"

FSaveMap ULoadScreenSaveGame::GetSaveMapWhitMapName(const FString& InMapName)
{
	for (const FSaveMap& Map : SaveMap)
	{
		if (Map.MapAssetName == InMapName)
		{
			return Map;
		}
	}

	return FSaveMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& InMapName)
{
	for (const FSaveMap& Map : SaveMap)
	{
		if (Map.MapAssetName == InMapName)
		{
			return true;
		}
	}

	return false;
}
