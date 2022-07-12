#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "TRHelper.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdate_01);

UENUM(BlueprintType)
enum class ActivateTypes : uint8 {
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

	// impact event 
	UPROPERTY(BlueprintAssignable, Category = "Path Director")
		FUpdate_01 OnImpact;


	void ReverseAct();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle_01;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UStaticMeshComponent* MeshObject;
	FVector MeshObject_defaultLocation;
	FVector Target_defaultLocation;
	bool OnRevers = false;
	bool OnTransition = false;
	float timerDelay = .1f;

	float Speed = 500.f;

	FVector temp_01 = FVector(FVector::ZeroVector);
	float temp_02 = 0.f;

	bool Active = false;
	bool impact = false;
	FVector Target = FVector(FVector::ZeroVector);

	void Move();
		
};
