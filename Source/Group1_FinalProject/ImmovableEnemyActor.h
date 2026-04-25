// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImmovableEnemyActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UTextRenderComponent;
class UPrimitiveComponent;

UCLASS()
class GROUP1_FINALPROJECT_API AImmovableEnemyActor : public AActor
{
    GENERATED_BODY()

public:
    AImmovableEnemyActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TalkTrigger;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UTextRenderComponent* MessageText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FText BlockedMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    float MessageDisplayTime = 2.0f;

private:
    FTimerHandle HideMessageTimerHandle;

public:
    UFUNCTION()
    void OnBeginOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void SpeakToPlayer(const FText& Message);

    UFUNCTION()
    void HideMessage();
};
