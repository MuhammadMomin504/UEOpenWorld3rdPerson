// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonTutorialGameMode.h"
#include "ThirdPersonTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonTutorialGameMode::AThirdPersonTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BatteryMan_GameMode_BP"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		
	}
}
