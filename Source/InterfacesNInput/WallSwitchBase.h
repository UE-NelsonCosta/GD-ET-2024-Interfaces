// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "WallSwitchBase.generated.h"

/*
 * Just a Base Switch Really, Takes The Interface To Ensure All Children Have Access To It, However The Implementation
 * Is Done In The Blueprints For Example Sake
 *
 * MetaData does the heavy lifting to ensure out actor reference (could be a FComponentReference instead depending on impelmentation)
 * This ensures only the right data is passed into the pointer.
 * 
 */

UCLASS()
class INTERFACESNINPUT_API AWallSwitchBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallSwitchBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* InteractingActor) override;
	
	// TScriptInterface Works Mostly Just For C++ Impelmentations
	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Transient, meta=(MustImplement="Interactable"))
	//TScriptInterface<UInteractable> ObjectToInteractWith;

	// As We Want An Actor In The Scene With An Implemented Type, We Also Say "AllowedClasses" so we can filter the options available in editor
	// Docs: https://benui.ca/unreal/uproperty/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta=(MustImplement="Interactable", AllowedClasses="Interactable"))
	AActor* ActorThatImplementsInteraction;
	
};
