#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// Note: It is auto generated and you can leave it as is, it's to help link things into BP UNLESS you need it exposed to BP's which in that case use BlueprintType
UINTERFACE(BlueprintType, MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 * Though Technically A Class, This is how we do interfaces in C++
 *
 * Please note an important note:
 * Interfaces can be called in blueprints, to do so they need the BlueprintCallable, and either BlueprintImplementableEvent or BlueprintNativeEvent
 *
 * BlueprintImplementableEvent - Only Blueprints Can Override The Logic Of The "Virtual" Function Chain
 * BlueprintNativeEvent - Allows to override the logic using a [FunctionName]_Implementation() in the code, AND Override The Blueprint version
 *
 * Final caveat is you should check if the interface is implemented
 * Docs: https://dev.epicgames.com/documentation/en-us/unreal-engine/interfaces?application_version=4.27
 * Docs: https://www.stevestreeting.com/2020/11/02/ue4-c---interfaces---hints-n-tips/
 * 
 */
class INTERFACESNINPUT_API IInteractable
{
	GENERATED_BODY()

public:

	// This is a C++ only Interface Function, Exists Solely For Example Sake
	virtual void Example(){}
	
	// Returns True By Default, Should Be Overriden Unless There Isn't A Need For It
	// Note: As it's a single line of code, I've decided to leave it in the header file
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanInteract(AActor* InteractingActor);

	// This is a pure virtual function, which is a fancy term for whomever takes this interface HAS to implement the function
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* InteractingActor);
};
