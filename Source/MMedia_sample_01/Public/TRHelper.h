#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "TRHelper.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdate_01);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdate_02);

UENUM(BlueprintType)
enum class ActivateTypes : uint8 {
	NOT_SET		UMETA(DisplayName = "NotSet"),
	Act_TypeA	UMETA(DisplayName = "TypeA"),
	Act_TypeB	UMETA(DisplayName = "TypeB"),
	Act_TypeC	UMETA(DisplayName = "TypeC"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMEDIA_SAMPLE_01_API UTRHelper : public UActorComponent{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTRHelper();

	// set up varibale and move object
	UFUNCTION(BlueprintCallable, Category = "Path Director")
		void SetupValues(ActivateTypes Type, UStaticMeshComponent* comp, FVector move_target, float move_Speed, float move_revDelay = .8f);
	
	UFUNCTION(BlueprintCallable, Category = "Path Director")
		void Activate_TypeA();

	// action event 
	UPROPERTY(BlueprintAssignable, Category = "Path Director")
		FUpdate_01 Action_TypeA;	
	
	UPROPERTY(BlueprintAssignable, Category = "Path Director")
		FUpdate_02 CheckPoint_TypeA;


	void ReverseAct();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle_01;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	ActivateTypes ACType = ActivateTypes::NOT_SET;	
	UStaticMeshComponent* MeshObject;
	FVector MeshObject_defaultLocation = FVector(FVector::ZeroVector);
	FVector Target = FVector(FVector::ZeroVector);
	FVector Target_defaultLocation = FVector(FVector::ZeroVector);
	
	bool InRevers = false;
	bool InTransition = false;
	bool Action_TypeA_Allowed = true;
	float TransitionDelay = .1f;
	float TransitionSpeed = 500.f;

	bool Active = false;
	bool DestinationReached = false;


	FVector temp_01 = FVector(FVector::ZeroVector);
	float temp_02 = 0.f;


	void Move(); // move function
	void CheckTypeA(); // proccess of type A 
		
};
