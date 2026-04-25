// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeakableActor.generated.h"

class UBoxComponent;
class USoundBase;
class UPrimitiveComponent;

UCLASS()
class GROUP1_FINALPROJECT_API ASpeakableActor : public AActor
{
    GENERATED_BODY()

public:
    ASpeakableActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* BoxCollider;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundBase* SpeakSound;

private:
    bool bHasPlayedSound = false;

public:
    UFUNCTION()
    void OnBoxBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
};
