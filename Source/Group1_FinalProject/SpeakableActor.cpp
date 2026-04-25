// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeakableActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Sound/SoundBase.h"

ASpeakableActor::ASpeakableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    RootComponent = BoxCollider;

    BoxCollider->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
    BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    BoxCollider->SetGenerateOverlapEvents(true);

    BoxCollider->OnComponentBeginOverlap.AddDynamic(
        this,
        &ASpeakableActor::OnBoxBeginOverlap
    );
}

void ASpeakableActor::BeginPlay()
{
    Super::BeginPlay();
}

void ASpeakableActor::OnBoxBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (bHasPlayedSound)
    {
        return;
    }

    AActor* Player = UGameplayStatics::GetPlayerPawn(this, 0);

    if (OtherActor == Player && SpeakSound)
    {
        bHasPlayedSound = true;

        UGameplayStatics::PlaySoundAtLocation(
            this,
            SpeakSound,
            GetActorLocation()
        );

        BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}
