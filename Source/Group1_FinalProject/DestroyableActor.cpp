// GameplaySystemsLabCharacter.h
// Copyright Epic Games, Inc. All Rights Reserved.

#include "DestroyableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ADestroyableActor::ADestroyableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetCollisionProfileName(TEXT("BlockAll"));

    Mesh->OnComponentHit.AddDynamic(this, &ADestroyableActor::OnHit);
}

void ADestroyableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestroyableActor::OnHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
        if (OtherActor == PlayerCharacter) {
            if (DestroySound)
            {
                UGameplayStatics::PlaySoundAtLocation(
                    this,
                    DestroySound,
                    GetActorLocation()
                );
            }

            Destroy();
        }
    }
}