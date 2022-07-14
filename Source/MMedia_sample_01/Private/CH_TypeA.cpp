#include "CH_TypeA.h"
#include "Math/UnrealMathUtility.h"

ACH_TypeA::ACH_TypeA(){	PrimaryActorTick.bCanEverTick = true; }

void ACH_TypeA::BeginPlay(){	Super::BeginPlay();	 }

void ACH_TypeA::Tick(float DeltaTime){	Super::Tick(DeltaTime); }

void ACH_TypeA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// recive an act event from player
void ACH_TypeA::ActionHandler_01() { // check action 
	Server_Act_01();
}

// recive act and argument from player
void ACH_TypeA::ChangeName_01(FString name, int ID) { // check values
	Server_SetName_01(name, ID);
}

// blueprint event
void ACH_TypeA::ActivateAction_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> ActivateAction"));	
}

// action replication ////////////////////////////////////////////////////////
bool ACH_TypeA::Server_Act_01_Validate() {	return true; }	// SERVER 

void ACH_TypeA::Server_Act_01_Implementation() {// SERVER 
	Multi_Act_01();
}

bool ACH_TypeA::Multi_Act_01_Validate() {	return true; }// MULTICAST

void ACH_TypeA::Multi_Act_01_Implementation() {// MULTICAST
	ActivateAction(); // blueprint event call
}

// action and argument replication //////////////////////////////////////
void ACH_TypeA::Server_SetName_01_Implementation(const FString& name, int ID) {// SERVER  
	Multi_SetName_01(name, ID);
}

void ACH_TypeA::Multi_SetName_01_Implementation(const FString& name, int ID) {// MULTICAST
	ActivateSetName(name, ID); // send data to BP by event
}

/* // notes
	//UE_LOG(LogTemp, Warning, TEXT("  ----ACH_TypeA-->> checkFunction --- "));
	//UE_LOG(LogTemp, Log, TEXT("   >>> HasAuthority result:  %s"), (HasAuthority() ? TEXT("true") : TEXT("false")));
	//UE_LOG(LogTemp, Log, TEXT("   >>> GetWorld()->IsServer() result: %s"), (GetWorld()->IsServer() ? TEXT("true") : TEXT("false")));
	//UE_LOG(LogTemp, Display, TEXT("    ---- ------------ --- "));

	//ENetRole NetRoleState = GetLocalRole();
	//UE_LOG(LogTemp, Log, TEXT("   >>> GetLocalRole() result: %s"), *UEnum::GetValueAsString(NetRoleState));

*/