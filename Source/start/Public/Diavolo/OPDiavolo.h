// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Champion/OPChampion.h"
#include "OPDiavolo.generated.h"

UCLASS()
class START_API AOPDiavolo : public AOPChampion
{
    GENERATED_BODY()

    public:
    virtual void Tick(float DeltaTime) override;

    void ApplySlowEffect(float SlowAmount, float Duration);
    void ApplySlowAttackEffect(float SlowAmount, float Duration);
    void ResetSpeed();

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical Tests", meta = (AllowPrivateAccess = "true"))
    bool bCanBeTestedMultipleTimes = false;

    FTimerHandle SlowEffectTimerHandle;
    float OriginalSpeed;

    /************* 리신 상대 애님 몽타주 **************/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LeeSin", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> Diavolo_DamagedByLeeSinMeleeAttack_AnimMontage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LeeSin", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> Diavolo_DamagedByLeeSinSonicWave_AnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LeeSin", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> Diavolo_DamagedByLeeSinResonatingStrike_AnimMontage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LeeSin", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> Diavolo_DamagedByLeeSinSkill_3_AnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LeeSin", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAnimMontage> Diavolo_DamagedByLeeSinDragonsRage_AnimMontage;

public:
    bool bTrueSightOn = false;

    FORCEINLINE bool GetbCanBeTestedMultipleTimes() const { return bCanBeTestedMultipleTimes; }

    USkeletalMeshComponent* GetDiavoloMesh() const;

    void PlayDiavoloRandomDeadMontage();

    void PlayDiavoloRandomDamagedMontage();

    TObjectPtr<UAnimMontage> GetDiavolo_DamagedByLeeSinMeleeAttack_AnimMontage() { return Diavolo_DamagedByLeeSinMeleeAttack_AnimMontage; }
    TObjectPtr<UAnimMontage> GetDiavolo_DamagedByLeeSinSonicWave_AnimMontage() { return Diavolo_DamagedByLeeSinSonicWave_AnimMontage; }
    TObjectPtr<UAnimMontage> GetDiavolo_DamagedByLeeSinResonatingStrike_AnimMontage() { return Diavolo_DamagedByLeeSinResonatingStrike_AnimMontage; }
    TObjectPtr<UAnimMontage> GetDiavolo_DamagedByLeeSinSkill_3_AnimMontage() { return Diavolo_DamagedByLeeSinSkill_3_AnimMontage; }
    TObjectPtr<UAnimMontage> GetDiavolo_DamagedByLeeSinDragonsRage_AnimMontage() { return Diavolo_DamagedByLeeSinDragonsRage_AnimMontage; }

};