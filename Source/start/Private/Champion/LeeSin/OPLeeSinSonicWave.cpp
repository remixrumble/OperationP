// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#include "Champion/LeeSin/OPLeeSinSonicWave.h"
#include "Champion/OPChampion.h"
#include "Animation/AnimInstance.h" // 애니메이션 인스턴스 헤더 포함
#include "Animation/OPAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Champion/LeeSin/OPLeeSin.h"
#include "Diavolo/OPDiavolo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void AOPLeeSinSonicWave::OnDamageCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnDamageCollisionBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    if (OtherActor && OtherActor != this && GetOwner() != nullptr && OtherActor != GetOwner())
    {
        AOPDiavolo* TestDiavolo = Cast<AOPDiavolo>(OtherActor);
        AOPLeeSin* LeeSinOwner = Cast<AOPLeeSin>(GetOwner());
        if (TestDiavolo)
        {
            // Log the impact direction for debugging
            UE_LOG(LogTemp, Log, TEXT("Sonic Wave Hit!!"));

            LeeSinOwner->Skill_1_Stack++;
            TestDiavolo->bTrueSightOn = true;

            // Get the animation instance from the mesh and play the AM_Diavolo_damaged montage
            // 그냥 Diavolo에 몽타주를 선언해서 재생하는게 더 안전할 거 같아용
            TestDiavolo->GetChampionAnimInstance()->Montage_Play(TestDiavolo->GetDiavolo_DamagedByLeeSinSonicWave_AnimMontage());
            // UAnimInstance* AnimInstance = TestDiavolo->GetDiavoloMesh()->GetAnimInstance();
            // if (AnimInstance && AM_Diavolo_damaged)
            // {
            //     UE_LOG(LogTemp, Log, TEXT("Diavolo Damaged"));
            //     AnimInstance->Montage_Play(AM_Diavolo_damaged);
            // }
            FVector ImpactDirection = (TestDiavolo->GetActorLocation() - SweepResult.ImpactPoint).GetSafeNormal();

            // Add an upward component to the impact direction
            //ImpactDirection.Z += AngleOfFloating;
            ImpactDirection = ImpactDirection.GetSafeNormal();

            // Log the impact direction for debugging
            UE_LOG(LogTemp, Log, TEXT("Impact Direction: %s"), *ImpactDirection.ToString());

            // Apply an impulse to the Diavolo character based on the impact direction and AirborneRate
            TestDiavolo->GetCharacterMovement()->AddImpulse(ImpactDirection * 10, true);

            if (!TestDiavolo->GetbCanBeTestedMultipleTimes())
            {
                TestDiavolo->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
            }
            if (LeeSinOwner)
            {
                LeeSinOwner->GetWorldTimerManager().SetTimer(LeeSinOwner->Skill_1_StackTimer, [LeeSinOwner, TestDiavolo]()
                    {
                        LeeSinOwner->SetbSkill_1_True();
                        LeeSinOwner->RemoveMarkerOnTarget(TestDiavolo);
                    }, LeeSinOwner->Skill_1_StackTime, false); // 루프 여부

                // 타겟 머리 위에 마커 생성
                LeeSinOwner->CreateMarkerOnTarget(TestDiavolo);
            }
        }
    }
    Destroy();
}