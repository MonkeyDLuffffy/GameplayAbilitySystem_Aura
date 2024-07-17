// copyright Druid bujingyun


#include "AbilitySystem/Data/AttributeInfo.h"

#include "AuraGameplayTags.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for(const FAuraAttributeInfo & Info:AttributeInformationArray)
	{
		if(Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Can't find info for AttributeTag [%s] On AttributeInfo [%s]."),*AttributeTag.ToString(),*GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
