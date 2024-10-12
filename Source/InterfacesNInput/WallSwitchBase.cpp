// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSwitchBase.h"

// Sets default values
AWallSwitchBase::AWallSwitchBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallSwitchBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallSwitchBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallSwitchBase::Interact_Implementation(AActor* InteractingActor)
{
	IInteractable::Interact_Implementation(InteractingActor);

	// Assuming We Would Like To Do This In C++, Just Get Rid Of The Event In Blueprints
	IInteractable::Execute_Interact(ActorThatImplementsInteraction, this);
}

