// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "GameFramework/Character.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADoor::CanInteract_Implementation(AActor* InteractingActor)
{
	// Just To Check it's Only Interactable By Characters As An Example
 	if(InteractingActor->IsA<ACharacter>())
 	{
 		return true;
 	}
 
 	return false;
}

void ADoor::Interact_Implementation(AActor* InteractingActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with %s"), *InteractingActor->GetName());

	// Pass The Responsibility Over To Blueprints To Handle The Animation
	AnimateDoor();
}
