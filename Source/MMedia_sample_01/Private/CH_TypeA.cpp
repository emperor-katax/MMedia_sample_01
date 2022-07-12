#include "CH_TypeA.h"

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

// //////////////////////////////////////////////////


// begin function of replication of an "Action" in network
void ACH_TypeA::DetectItem_01() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> DetectItem_01_Implementation called from BP"));
	Server_Detect_01();
}

// final function of replication of an "Action" in network which runs on each client
void ACH_TypeA::checkFunction() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> checkFunction --- "));
	UE_LOG(LogTemp, Log, TEXT("   >>> HasAuthority result:  %s"), (HasAuthority() ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Log, TEXT("   >>> GetWorld()->IsServer() result: %s"), (GetWorld()->IsServer() ? TEXT("true") : TEXT("false")));
	UE_LOG(LogTemp, Display, TEXT("    ---- ------------ --- "));
	ENetRole NetRoleState = GetLocalRole();
	UE_LOG(LogTemp, Log, TEXT("   >>> GetLocalRole() result: %s"), *UEnum::GetValueAsString(NetRoleState));

	ActivateDetection(); // blueprint event call
}

void ACH_TypeA::ActivateDetection_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> ActivateDetection fires from BP"));	
}




// SERVER     /////////////////////////////////////////

bool ACH_TypeA::Server_Detect_01_Validate() {
	return true;
}

void ACH_TypeA::Server_Detect_01_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> Server_Detect_01_Implementation called from SERVER"));
	Multi_Detect_01();
}

// MULTICAST /////////////////////////////////////////

bool ACH_TypeA::Multi_Detect_01_Validate() {
	return true;
}

void ACH_TypeA::Multi_Detect_01_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("    ----ACH_TypeA-->> Multi_Detect_01_Implementation ---  Multicat"));
	checkFunction();
}