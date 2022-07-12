#include "TRHelper.h"
#include "Math/UnrealMathUtility.h"


UTRHelper::UTRHelper(){
	PrimaryComponentTick.bCanEverTick = true;
}

void UTRHelper::BeginPlay(){
	Super::BeginPlay();
	FTimerManager* tm = new FTimerManager();
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle_01, this, &UTRHelper::tempResult, 6.0f, false);
	
	//float u = FMath::GetMappedRangeValueClamped(FVector2D(7, 90), FVector2D(700, 9000), 23);
	//UE_LOG(LogTemp, Log, TEXT("   >>> HasAuthority result:  %f"), u);
	// https://chowdera.com/2021/09/20210914053908424b.html
}

void UTRHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TimerHandle_01.IsValid()) {
		//UE_LOG(LogTemp, Log, TEXT("   >>> HasAuthority result:  %s"), *TimerHandle_01.StaticStruct());
	}
	
	temp_02 = Speed * DeltaTime;
	if (Active)	Move();
	//if (impact)	OnImpact.Broadcast();
	if (impact && !OnRevers) {
		Active = false;
		impact = false;
		OnImpact.Broadcast();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_01, this, &UTRHelper::ReverseAct, timerDelay, false);
	}

	if (impact && OnRevers) {
		Active = false;
		impact = false;
		OnRevers = false;
		MeshObject->SetWorldLocation(MeshObject_defaultLocation);
		Target = Target_defaultLocation;
		OnTransition = false;
	}

}

void UTRHelper::ReverseAct() {
	OnImpact.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("    ----UTRHelper-->> ReverseAct called from BP"));
	Target = MeshObject_defaultLocation;
	impact = false;
	OnRevers = true;
	OnTransition = false;
}
/*
	// Ensure the fuze timer is cleared by using the timer handle
	GetWorld()->GetTimerManager().ClearTimer(FuzeTimerHandle);
	// Alternatively you can clear ALL timers that belong to this (Actor) instance.
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	
	more on timers from tom
	// https://www.tomlooman.com/unreal-engine-cpp-timers/
*/

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void UTRHelper::Move() {
	OnTransition = true;
	temp_01 = MeshObject->GetComponentLocation();
	temp_01 += (temp_02 * (Target - temp_01).GetSafeNormal());
	if ((FVector::Distance(Target, temp_01)) <= temp_02) {
		temp_01 = Target;
		impact = true;
		UE_LOG(LogTemp, Warning, TEXT("KTX ---------------------- dook"));
	}
	MeshObject->SetWorldLocation(temp_01);
}

void UTRHelper::SetupValues(ActivateTypes Type , UStaticMeshComponent* comp, FVector move_target, float move_Speed, float move_revDelay) {
	if (comp != NULL) {
		
		switch (Type) {
			case ActivateTypes::Act_TypeA :
				timerDelay = move_revDelay;
				MeshObject = comp;
				Target = move_target;
				Target_defaultLocation = move_target;
				MeshObject_defaultLocation = comp->GetComponentLocation();
				Speed = move_Speed;
			break;
			default: break;
		}



		//UE_LOG(LogTemp, Warning, TEXT("KTX ----------------------I just started running"));
		//UE_LOG(LogTemp, Error, TEXT("KTX --- traget location: %s"), *Target.ToString());
		//Active = true;
	}
}

void UTRHelper::Activate_TypeA() {
	if (!OnTransition) Active = true;
}
