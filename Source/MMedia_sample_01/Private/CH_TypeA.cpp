#include "CH_TypeA.h"
#include "Math/UnrealMathUtility.h"

ACH_TypeA::ACH_TypeA(){
	PrimaryActorTick.bCanEverTick = true;
}

void ACH_TypeA::BeginPlay(){
	Super::BeginPlay();	
}

void ACH_TypeA::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ACH_TypeA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// //////////////////////////////////////////////////////////////////////////////////////
void ACH_TypeA::DetectItem_01() { // check action 
	Server_Detect_01();
}

void ACH_TypeA::ChangeName_01(FString name, int ID) { // check values
	Server_SetName_01(name, ID);
}

void ACH_TypeA::checkFunction() { // support action 
	ActivateDetection(); // blueprint event call
}

void ACH_TypeA::ActivateDetection_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> ActivateDetection"));	
}

// detect object network implementation //////////////////////////////
bool ACH_TypeA::Server_Detect_01_Validate() {// SERVER 
	return true;
}

void ACH_TypeA::Server_Detect_01_Implementation() {// SERVER 
	Multi_Detect_01();
}

bool ACH_TypeA::Multi_Detect_01_Validate() {// MULTICAST
	return true;
}

void ACH_TypeA::Multi_Detect_01_Implementation() {// MULTICAST
	checkFunction();
}

// set name network implementation //////////////////////////////
void ACH_TypeA::Server_SetName_01_Implementation(const FString& name, int ID) {// SERVER  
	Multi_SetName_01(name, ID);
}

void ACH_TypeA::Multi_SetName_01_Implementation(const FString& name, int ID) {// MULTICAST
	ActivateSetName(name, ID); // send data to BP by event
}

/*
	//UE_LOG(LogTemp, Warning, TEXT("  ----ACH_TypeA-->> checkFunction --- "));
	//UE_LOG(LogTemp, Log, TEXT("   >>> HasAuthority result:  %s"), (HasAuthority() ? TEXT("true") : TEXT("false")));
	//UE_LOG(LogTemp, Log, TEXT("   >>> GetWorld()->IsServer() result: %s"), (GetWorld()->IsServer() ? TEXT("true") : TEXT("false")));
	//UE_LOG(LogTemp, Display, TEXT("    ---- ------------ --- "));

	//ENetRole NetRoleState = GetLocalRole();
	//UE_LOG(LogTemp, Log, TEXT("   >>> GetLocalRole() result: %s"), *UEnum::GetValueAsString(NetRoleState));

*/