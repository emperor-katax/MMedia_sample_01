#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CH_TypeA.generated.h"

UCLASS()
class MMEDIA_SAMPLE_01_API ACH_TypeA : public ACharacter{
	GENERATED_BODY()

public:
	ACH_TypeA();

	UFUNCTION(BlueprintCallable, Category = "Actor_BP Functions")	// recive action from BP
		void ActionHandler_01();	
	
	UFUNCTION(BlueprintCallable, Category = "Actor_BP Functions")	// recive action with argumrnts from BP
		void ChangeName_01(FString name, int ID);

	UFUNCTION(BlueprintNativeEvent, Category = "Actor_BP Events")	// client/server action funtion
		void ActivateAction();

	UFUNCTION(BlueprintImplementableEvent, Category = "Actor_BP Events")	// client/server set name function
		void ActivateSetName(const FString& name, int ID);

protected:
	virtual void BeginPlay() override;

	// act replication 
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Act_01();
		bool Server_Act_01_Validate();
		void Server_Act_01_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_Act_01();
		bool Multi_Act_Validate();
		void Multi_Act_Implementation();
	
	// set name replication
	UFUNCTION(Server, Reliable)
		void Server_SetName_01(const FString& name, int ID);
		void Server_SetName_01_Implementation(const FString& name, int ID);

	UFUNCTION(NetMulticast, Reliable)
		void Multi_SetName_01(const FString& name, int ID);
		void Multi_SetName_01_Implementation(const FString& name, int ID);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
