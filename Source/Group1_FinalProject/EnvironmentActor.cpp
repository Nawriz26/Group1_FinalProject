// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentActor.h"
#include "Math/UnrealMathUtility.h"

AEnvironmentActor::AEnvironmentActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SceneRoot);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(SceneRoot);

	RotationSpeed = 45.0f;
	MovementOffset = FVector(0.0f, 0.0f, 0.0f);
	OscillationAmplitude = 20.0f;
	OscillationSpeed = 1.0f;

	MaterialScalarValue = 1.0f;
	MaterialColor = FLinearColor::White;
	ScalarParameterName = TEXT("Glow");
	ColorParameterName = TEXT("BaseColor");

	MinLightIntensity = 1000.0f;
	MaxLightIntensity = 5000.0f;
	LightAnimationSpeed = 2.0f;
	LightColor = FLinearColor::White;
	bLightEnabled = true;

	DynamicMaterial = nullptr;
	RunningTime = 0.0f;
}

void AEnvironmentActor::BeginPlay()
{
	Super::BeginPlay();

	DefaultLocation = GetActorLocation();
	DefaultRotation = GetActorRotation();
	DefaultTransform = GetActorTransform();

	if (MeshComponent && MeshComponent->GetMaterial(0))
	{
		DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
	}

	if (PointLight)
	{
		PointLight->SetLightColor(LightColor);
		PointLight->SetIntensity(MinLightIntensity);
		PointLight->SetVisibility(bLightEnabled);
	}

	UpdateMaterialParameters();
}

void AEnvironmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	ApplyTransformAnimation(DeltaTime);

	if (PointLight && bLightEnabled)
	{
		const float PulseAlpha = (FMath::Sin(RunningTime * LightAnimationSpeed) + 1.0f) * 0.5f;
		const float CurrentIntensity = FMath::Lerp(MinLightIntensity, MaxLightIntensity, PulseAlpha);

		PointLight->SetIntensity(CurrentIntensity);
		PointLight->SetLightColor(LightColor);
	}

	if (DynamicMaterial)
	{
		const float AnimatedScalar = MaterialScalarValue + (FMath::Sin(RunningTime * 2.0f) * 0.5f);
		DynamicMaterial->SetScalarParameterValue(ScalarParameterName, AnimatedScalar);
		DynamicMaterial->SetVectorParameterValue(ColorParameterName, MaterialColor);
	}
}

void AEnvironmentActor::ToggleLightState()
{
	bLightEnabled = !bLightEnabled;

	if (PointLight)
	{
		PointLight->SetVisibility(bLightEnabled);
	}
}

void AEnvironmentActor::UpdateMaterialParameters()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(ScalarParameterName, MaterialScalarValue);
		DynamicMaterial->SetVectorParameterValue(ColorParameterName, MaterialColor);
	}
}

void AEnvironmentActor::ResetActorTransform()
{
	SetActorTransform(DefaultTransform);
}

FTransform AEnvironmentActor::GetCurrentTransformState() const
{
	return GetActorTransform();
}

void AEnvironmentActor::ApplyTransformAnimation(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(CurrentRotation);

	FVector NewLocation = DefaultLocation + MovementOffset;
	NewLocation.Z += FMath::Sin(RunningTime * OscillationSpeed) * OscillationAmplitude;
	SetActorLocation(NewLocation);
}
