// Copyright Epic Games, Inc. All Rights Reserved.

#include "InterfacesNInputGameMode.h"
#include "InterfacesNInputCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInterfacesNInputGameMode::AInterfacesNInputGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
