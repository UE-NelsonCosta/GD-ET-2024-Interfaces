// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERFACESNINPUT_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInteractor();

	// We Are Going To Avoid Ticking To Reduce The Overall Cost
	// Instead We Opt For A Timer Handled By The World Class
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Similar To Unity Allows Logic To Override What Is Important To Activate/Deactivate
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

	UFUNCTION(BlueprintCallable)
	void RequestInteract();
	
protected:

	UFUNCTION()
	void OnTimerTick();

private: // Internal Helper Functions

	class APlayerCameraManager* GetPossessedPlayerCamera();
	
protected:

	// Time Between Checks, This Will Make It Roughly About 10th of a Second
	UPROPERTY(EditDefaultsOnly)
	float TimerTickInterval = 0.1f;
	
private:
	
	// Actual Handle In The Timer Class
	FTimerHandle TimerHandle;

	// Keep Track Of Our Delegate For The Timer, So We Can Add And Remove It As We See Fit
	FTimerDelegate TimerDelegate;

	UPROPERTY()
	TScriptInterface<class IInteractable> InteractableObject;

	// Caching This To Avoid Creation And Recreation Of The Same Object
	FHitResult HitResult;

	UPROPERTY(EditAnywhere)
	bool ShowDebugRay = false;
};
