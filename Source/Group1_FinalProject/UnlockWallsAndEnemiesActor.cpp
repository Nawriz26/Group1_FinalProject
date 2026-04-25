// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockWallsAndEnemiesActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"
#include "ImmovableEnemyActor.h"

class UBoxComponent;

AUnlockWallsAndEnemiesActor::AUnlockWallsAndEnemiesActor()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    TriggerBox->SetGenerateOverlapEvents(true);

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUnlockWallsAndEnemiesActor::OnOverlapBegin);
}

void AUnlockWallsAndEnemiesActor::BeginPlay()
{
	Super::BeginPlay();
}

void AUnlockWallsAndEnemiesActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
        if (Player)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Walls and Enemies have been destroyed!!"));
        }

        TArray<AActor*> FoundEnemies;
        UGameplayStatics::GetAllActorsOfClass(
            GetWorld(),
            AImmovableEnemyActor::StaticClass(),
            FoundEnemies
        );
        for (AActor* Actor : FoundEnemies)
        {
            Actor->Destroy();
        }

		if (UnlockSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				UnlockSound,
				GetActorLocation()
			);
		}
    }
}
