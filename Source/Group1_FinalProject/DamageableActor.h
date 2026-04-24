// GameplaySystemsLabCharacter.h
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageableActor.generated.h"

class UStaticMeshComponent;

// ================================================================
// THIS CLASS WILL ALSO BE EXTENDED BY BluePrints
// ================================================================
UCLASS()
class GROUP1_FINALPROJECT_API ADamageableActor : public AActor
{
    GENERATED_BODY()

public:
    ADamageableActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float MaxHealth = 50.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamagePerHit = 10.f;

    UFUNCTION()
    void OnHit(
        UPrimitiveComponent* HitComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );
};
