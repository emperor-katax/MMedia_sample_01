#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "TRHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdate_01); // delegate event handler
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdate_02); // delegate event handler

UENUM(BlueprintType) // interaction type
enum class ActivateTypes : uint8 {
	NOT_SET		UMETA(DisplayName = "NotSet"),
	Act_TypeA	UMETA(DisplayName = "TypeA"),
	Act_TypeB	UMETA(DisplayName = "TypeB"),
	Act_TypeC	UMETA(DisplayName = "TypeC"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMEDIA_SAMPLE_01_API UTRHelper : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTRHelper();

	// set up varibale and move object
	UFUNCTION(BlueprintCallable, Category = "Path Director")
		void initValues(ActivateTypes Type, UStaticMeshComponent* comp, FVector move_target, float move_Speed, float move_revDelay = .8f);
	
	UFUNCTION(BlueprintCallable, Category = "Path Director")
		void Activate_TypeA();

	// action events 
	UPROPERTY(BlueprintAssignable, Category = "Path Director")
		FUpdate_01 Action_TypeA;	
	
	UPROPERTY(BlueprintAssignable, Category = "Path Director")
		FUpdate_02 CheckPoint_TypeA;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle_01;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ActivateTypes ACType = ActivateTypes::NOT_SET;						// interaction type
	UStaticMeshComponent* MeshObject;									// move component
	FVector MeshObject_defaultLocation = FVector(FVector::ZeroVector);	// component default location
	FVector Target = FVector(FVector::ZeroVector);						// destination to move
	FVector Target_defaultLocation = FVector(FVector::ZeroVector);		// default destination for revers move
	
	bool InRevers = false;				// revers move flag
	bool InTransition = false;			// transmition flag , when true no action will accepted
	bool Action_TypeA_Allowed = true;	// if true, TypeA actions are allowed
	
	float TransitionDelay = .1f;		// delay on accept interaction in second
	float TransitionSpeed = 500.f;		// movement speed

	bool Active = false;				// enable and disable for moving procedure
	bool DestinationReached = false;	// set true when component is reached to Target

	void Move();		// move function
	void CheckTypeA();	// proccess of type A 
	void ReverseAct();	// reverse move

	// temporary variables
	FVector temp_01 = FVector(FVector::ZeroVector);
	float temp_02 = 0.f;


};
