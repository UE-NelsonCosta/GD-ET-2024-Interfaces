// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "Interactable.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Turned off to improve performance
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	if(UWorld* World = GetWorld())
	{
		// If its a BindUFUnction, your function NEEDS th UFUNCTION macro on it's declaration, otherwise it's not
		// Registered Correctly Which Means The System Can't Find It
		TimerDelegate.BindUFunction(this, "OnTimerTick");
		World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, TimerTickInterval, true);
	}
}

void UInteractor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(TimerHandle.IsValid())
	{
		TimerHandle.Invalidate();
	}
}

void UInteractor::Activate(bool bReset)
{
	Super::Activate(bReset);

	UWorld* World = GetWorld();
	if(!TimerHandle.IsValid() && World)
	{
		World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, TimerTickInterval, true);
	}
}

void UInteractor::Deactivate()
{
	Super::Deactivate();

	if(TimerHandle.IsValid())
	{
		TimerHandle.Invalidate();
	}
}

void UInteractor::RequestInteract()
{
	// Always Check Your Pointers!
	if(InteractableObject.GetObject() && IInteractable::Execute_CanInteract(InteractableObject.GetObject(), GetOwner()))
	{
		// Use This Variant, It Will Execute Either The C++ Version If A BP One Isn't Specified
		IInteractable::Execute_Interact(InteractableObject.GetObject(), GetOwner());
	}
}

void UInteractor::OnTimerTick()
{
	// Guard Clause TO Protect Against Mistakes Or Worlds Being Destroyed
	UWorld* World = GetWorld();
	if(!World)
		return;

	APlayerCameraManager* CameraManager = GetPossessedPlayerCamera();
	if(!CameraManager)
		return;
	
	// Note For Memory Efficiency We Can Cache This In The Header File
	FVector LineTraceStartPoint = CameraManager->GetCameraLocation();
	FVector LineTraceEndPoint = CameraManager->GetCameraLocation() + CameraManager->GetActorForwardVector() * 10000.0f;

	if(ShowDebugRay)
		DrawDebugLine(World, LineTraceStartPoint, LineTraceEndPoint, FColor::Red, true, 10000.0f, 0);

	// TODO: Cache This Structure
	FCollisionQueryParams CollisionQueryParameters;
	CollisionQueryParameters.AddIgnoredActor(GetOwner());

	if(World->LineTraceSingleByChannel(HitResult, LineTraceStartPoint, LineTraceEndPoint, ECC_Visibility, CollisionQueryParameters))
	{
		// Lets Ensure It's Interactable And A Different Object
		if(HitResult.GetActor()->Implements<UInteractable>())
		{
			if(InteractableObject.GetObject() == HitResult.GetActor())
				return;
			
			// Pulls The Interface Out Of The Object For Us
			InteractableObject = HitResult.GetActor();

			// Testing Purposes
			// Use The Wrapper Itself When Calling The Interface, Will Save You A Lot Of Hassle For All Sorts of Edge Cases
			// Have A Look At The interactable.h second piece of documentation
			// IInteractable::Execute_Interact(InteractableObject.GetObject(), GetOwner());

			return;
		}
	}

	// Otherwise We Didn't Hit Anything Therefore We Should Be Clearing It Up
	InteractableObject = nullptr;
}

APlayerCameraManager* UInteractor::GetPossessedPlayerCamera()
{
	APawn* Owner = GetOwner<APawn>();
	if(!Owner)
		return nullptr;

	APlayerController* PlayerController = Cast<APlayerController>(Owner->Controller);
	if(!PlayerController)
		return nullptr;

	return PlayerController->PlayerCameraManager;
}
