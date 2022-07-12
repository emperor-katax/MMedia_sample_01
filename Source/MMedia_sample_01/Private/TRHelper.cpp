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

/// ///////////////////////////////////////////////////////
void UTRHelper::CheckTypeA() {	
	if (DestinationReached) { 
		Active = false;
		DestinationReached = false;
		Action_TypeA.Broadcast();			// activate event on switch transition
		if (InRevers) {	// reset values for next intract
			InRevers = false;
			MeshObject->SetWorldLocation(MeshObject_defaultLocation);
			Target = Target_defaultLocation;
			InTransition = false;
			Action_TypeA_Allowed = true;
			CheckPoint_TypeA.Broadcast();	// activate event on end of transition
		} else {		// set delay for reverce move
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_01, this, &UTRHelper::ReverseAct, TransitionDelay, false);
		}
	}
}

void UTRHelper::ReverseAct() {
	Target = MeshObject_defaultLocation;
	DestinationReached = false;
	InRevers = true;
	InTransition = false;
	Action_TypeA_Allowed = true;
	CheckPoint_TypeA.Broadcast();	// activate event on end of delay
}

void UTRHelper::SetupValues(ActivateTypes Type , UStaticMeshComponent* comp, FVector move_target, float move_Speed, float move_revDelay) {
	if (comp != NULL) {		
		switch (Type) {
			case ActivateTypes::Act_TypeA :
				MeshObject = comp; // get component		
				MeshObject_defaultLocation = comp->GetComponentLocation(); // get component default location			
				Target = move_target; // set destination to move
				Target_defaultLocation = move_target; // save default destination for revers move
				TransitionDelay = move_revDelay; // delay on accept interaction
				TransitionSpeed = move_Speed; // movement speed
				ACType = ActivateTypes::Act_TypeA; // interaction type
			break;
			default: break;
		}
	}
}

void UTRHelper::Activate_TypeA() {
	if (ACType != ActivateTypes::Act_TypeA) {
		UE_LOG(LogTemp, Warning, TEXT("Please setup default data for 'Activate_TypeA' transition."));
		return;
	}
	if (!InTransition) Active = true;
	if (Action_TypeA_Allowed) Action_TypeA.Broadcast(); // activate event on begin transition
	Action_TypeA_Allowed = false;
}

/*
	//UE_LOG(LogTemp, Warning, TEXT("    ----UTRHelper-->> ReverseAct "));
*/
