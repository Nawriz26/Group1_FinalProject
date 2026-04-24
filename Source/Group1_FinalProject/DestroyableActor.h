// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class GROUP1_FINALPROJECT_API ADestroyableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestroyableActor();

protected:
	virtual void BeginPlay() override;

public:	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);
};
