// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CH_TypeA.generated.h"

UCLASS()
class MMEDIA_SAMPLE_01_API ACH_TypeA : public ACharacter
{
	GENERATED_BODY()

public:
	ACH_TypeA();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Actor_BP Events") <<-- no event in blueprint, only function in BP and C++
	UFUNCTION(BlueprintNativeEvent, Category = "Actor_BP Events") // event in BP + function in C++ 
		void ActivateDetection();

	UFUNCTION(BlueprintCallable, Category = "Actor_BP Functions")
		void DetectItem_01();

protected:
	virtual void BeginPlay() override;

	// all 3 functions is essential
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_Detect_01();
		bool Server_Detect_01_Validate();
		void Server_Detect_01_Implementation();


	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void Multi_Detect_01();
		bool Multi_Detect_01_Validate();
		void Multi_Detect_01_Implementation();

public:	
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input - default in character
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void checkFunction();

};
