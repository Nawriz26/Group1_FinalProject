// Fill out your copyright notice in the Description page of Project Settings.


#include "ImmovableEnemyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"

AImmovableEnemyActor::AImmovableEnemyActor()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    TalkTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TalkTrigger"));
    TalkTrigger->SetupAttachment(RootComponent);

    TalkTrigger->SetBoxExtent(FVector(100.f, 100.f, 100.f));
    TalkTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TalkTrigger->SetCollisionObjectType(ECC_WorldDynamic);
    TalkTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    TalkTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    TalkTrigger->SetGenerateOverlapEvents(true);

    TalkTrigger->OnComponentBeginOverlap.AddDynamic(
        this,
        &AImmovableEnemyActor::OnBeginOverlap
    );

    MessageText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MessageText"));
    MessageText->SetupAttachment(RootComponent);

    MessageText->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
    MessageText->SetHorizontalAlignment(EHTA_Center);
    MessageText->SetWorldSize(35.f);
    MessageText->SetTextRenderColor(FColor::Red);
    MessageText->SetHiddenInGame(true);

    BlockedMessage = FText::FromString(TEXT("You cannot pass."));
}

void AImmovableEnemyActor::BeginPlay()
{
    Super::BeginPlay();

    if (MessageText)
    {
        MessageText->SetText(BlockedMessage);
        MessageText->SetHiddenInGame(true);
    }
}

void AImmovableEnemyActor::OnBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

    if (!PlayerCharacter || OtherActor != PlayerCharacter)
    {
        return;
    }

    SpeakToPlayer(BlockedMessage);
}

void AImmovableEnemyActor::SpeakToPlayer(const FText& Message)
{
    if (!MessageText)
    {
        return;
    }

    MessageText->SetText(Message);
    MessageText->SetHiddenInGame(false);

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HideMessageTimerHandle);

        GetWorld()->GetTimerManager().SetTimer(
            HideMessageTimerHandle,
            this,
            &AImmovableEnemyActor::HideMessage,
            MessageDisplayTime,
            false
        );
    }
}

void AImmovableEnemyActor::HideMessage()
{
    if (MessageText)
    {
        MessageText->SetHiddenInGame(true);
    }
}
