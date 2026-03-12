// Fill out your copyright notice in the Description page of Project Settings. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "EnvironmentActor.generated.h"

UCLASS()
class GROUP1_FINALPROJECT_API AEnvironmentActor : public AActor
{
	GENERATED_BODY()

public:
	AEnvironmentActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* PointLight;

	// Transform Control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Control", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Control", meta = (AllowPrivateAccess = "true"))
	FVector MovementOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Control", meta = (AllowPrivateAccess = "true"))
	float OscillationAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Control", meta = (AllowPrivateAccess = "true"))
	float OscillationSpeed;

	// Material Control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Control", meta = (AllowPrivateAccess = "true"))
	float MaterialScalarValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Control", meta = (AllowPrivateAccess = "true"))
	FLinearColor MaterialColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Control", meta = (AllowPrivateAccess = "true"))
	FName ScalarParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Control", meta = (AllowPrivateAccess = "true"))
	FName ColorParameterName;

	// Lighting Control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Control", meta = (AllowPrivateAccess = "true"))
	float MinLightIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Control", meta = (AllowPrivateAccess = "true"))
	float MaxLightIntensity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Control", meta = (AllowPrivateAccess = "true"))
	float LightAnimationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Control", meta = (AllowPrivateAccess = "true"))
	FLinearColor LightColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting Control", meta = (AllowPrivateAccess = "true"))
	bool bLightEnabled;

	// Runtime State
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime", meta = (AllowPrivateAccess = "true"))
	FVector DefaultLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime", meta = (AllowPrivateAccess = "true"))
	FRotator DefaultRotation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Runtime", meta = (AllowPrivateAccess = "true"))
	FTransform DefaultTransform;

	// Runtime-only object; no reflection needed here
	UMaterialInstanceDynamic* DynamicMaterial;

	float RunningTime;

public:
	UFUNCTION(BlueprintCallable, Category = "Environment Actor|Lighting")
	void ToggleLightState();

	UFUNCTION(BlueprintCallable, Category = "Environment Actor|Material")
	void UpdateMaterialParameters();

	UFUNCTION(BlueprintCallable, Category = "Environment Actor|Transform")
	void ResetActorTransform();

	UFUNCTION(BlueprintCallable, Category = "Environment Actor|Transform")
	FTransform GetCurrentTransformState() const;

	UFUNCTION(BlueprintCallable, Category = "Environment Actor|Transform")
	void ApplyTransformAnimation(float DeltaTime);
};