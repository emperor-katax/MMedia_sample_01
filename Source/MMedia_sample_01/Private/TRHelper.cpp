#include "TRHelper.h"
#include "Math/UnrealMathUtility.h"


UTRHelper::UTRHelper(){
	PrimaryComponentTick.bCanEverTick = true;
}

void UTRHelper::BeginPlay(){
	Super::BeginPlay();
}

void UTRHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	temp_02 = TransitionSpeed * DeltaTime;
	if (Active)	Move();
	if (ACType == ActivateTypes::Act_TypeA) CheckTypeA();
}

void UTRHelper::Move() {
	InTransition = true;
	temp_01 = MeshObject->GetComponentLocation();
	temp_01 += (temp_02 * (Target - temp_01).GetSafeNormal());
	if ((FVector::Distance(Target, temp_01)) <= temp_02) {
		temp_01 = Target;
		DestinationReached = true;
	}
	MeshObject->SetWorldLocation(temp_01);
}




/// //////////////////////////////////
void UTRHelper::CheckTypeA() {
	
	if (DestinationReached) { 
		Active = false;
		DestinationReached = false;
		Action_TypeA.Broadcast();	// activate event
		if (InRevers) {				// reset values for next intract
			InRevers = false;
			MeshObject->SetWorldLocation(MeshObject_defaultLocation);
			Target = Target_defaultLocation;
			InTransition = false;
			Action_TypeA_Allowed = true;
			CheckPoint_TypeA.Broadcast();	// activate event
		} else {					// set delay for reverce move
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_01, this, &UTRHelper::ReverseAct, TransitionDelay, false);
		}
	}
}

void UTRHelper::ReverseAct() {
	//UE_LOG(LogTemp, Warning, TEXT("    ----UTRHelper-->> ReverseAct "));
	Target = MeshObject_defaultLocation;
	DestinationReached = false;
	InRevers = true;
	InTransition = false;
	Action_TypeA_Allowed = true;
	CheckPoint_TypeA.Broadcast();	// activate event
}

void UTRHelper::SetupValues(ActivateTypes Type , UStaticMeshComponent* comp, FVector move_target, float move_Speed, float move_revDelay) {
	if (comp != NULL) {		
		switch (Type) {
			case ActivateTypes::Act_TypeA :
				TransitionDelay = move_revDelay;
				MeshObject = comp;
				Target = move_target;
				Target_defaultLocation = move_target;
				MeshObject_defaultLocation = comp->GetComponentLocation();
				TransitionSpeed = move_Speed;
				ACType = ActivateTypes::Act_TypeA;
			break;
			default: break;
		}
	}
}

void UTRHelper::Activate_TypeA() {
	if (ACType != ActivateTypes::Act_TypeA) {
		UE_LOG(LogTemp, Warning, TEXT("KTX missin setup data for 'Activate_TypeA' transition. "));
		return;
	}
	if (!InTransition) Active = true;
	if (Action_TypeA_Allowed) Action_TypeA.Broadcast(); // activate event at begin
	Action_TypeA_Allowed = false;
}


