// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CH_TypeA.generated.h"

UCLASS()
class MMEDIA_SAMPLE_01_API ACH_TypeA : public ACharacter{
	GENERATED_BODY()

public:
	ACH_TypeA();

	UFUNCTION(BlueprintCallable, Category = "Actor_BP Functions")	// run detect funtion from  BP
		void ActionHandler_01();	
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actor_BP Events")	// client/server detect funtion
		void ActivateAction();

	UFUNCTION(BlueprintCallable, Category = "Actor_BP Functions")			// run change name function from BP 
		void ChangeName_01(FString name, int ID);

	UFUNCTION(BlueprintImplementableEvent, Category = "Actor_BP Events")	// client/server set name function
		void ActivateSetName(const FString& name, int ID);

protected:
	virtual void BeginPlay() override;

	// detect object
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Detect_01();
		bool Server_Detect_01_Validate();
		void Server_Detect_01_Implementation();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_Detect_01();
		bool Multi_Detect_01_Validate();
		void Multi_Detect_01_Implementation();
	
	// set name
	UFUNCTION(Server, Reliable)
		void Server_SetName_01(const FString& name, int ID);
		void Server_SetName_01_Implementation(const FString& name, int ID);

	UFUNCTION(NetMulticast, Reliable)
		void Multi_SetName_01(const FString& name, int ID);
		void Multi_SetName_01_Implementation(const FString& name, int ID);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void checkFunction(); // support detect funtion on each player


};
