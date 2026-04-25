// GameplaySystemsLabCharacter.h
// Copyright Epic Games, Inc. All Rights Reserved.

#include "DamageableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ADamageableActor::ADamageableActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetCollisionProfileName(TEXT("BlockAll"));

    Mesh->OnComponentHit.AddDynamic(this, &ADamageableActor::OnHit);
    CurrentHealth = MaxHealth;
}

void ADamageableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADamageableActor::OnHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    if (OtherActor || OtherActor != this)
    {
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

        if (PlayerCharacter && OtherActor == PlayerCharacter) {
            if (CurrentHealth <= 0.f) {
                Destroy();
			}
			CurrentHealth -= DamagePerHit;
        }
    }

}
