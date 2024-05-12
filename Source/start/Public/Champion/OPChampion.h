// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OPChampion.generated.h"

class AOPDiavolo;

UCLASS()
class START_API AOPChampion : public ACharacter
{
	GENERATED_BODY()

public:
	AOPChampion();

protected:
	FHitResult MouseCursorHit; // 마우스 커서 위치에서 Hit 했을 때 얻을 수 있는 정보
	virtual void BeginPlay() override;

	// 아래 함수들은 롤 챔피언들에게 모두 있는 기능이므로 override를 위해 virtual 함수로 설정
	virtual void Passive();
	virtual void MeleeAttack();
	virtual void Skill_1();
	virtual void Skill_2();
	virtual void Skill_3();
	virtual void Skill_4();
	virtual void Ult();


public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void TurnCharacterToLocation(FVector TurnPoint);
	void TurnCharacterToCursor(FHitResult HitResult);

protected:
	class AOPPlayerController* OPPlayerController; // 말 그대로 플레이어 컨트롤러

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* ChampionMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MeleeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillAction1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillAction3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SkillAction4;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UltAction;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

	// 애님 몽타주 재생에 필요한 애니메이션 인스턴스
	class UOPAnimInstance* ChampionAnimInstance;

	// 실험체 디아블로
	TObjectPtr<AOPDiavolo> TestDiavolo;

	/**********************************************************************************************************/

	bool bIsDamaged = false;
	bool bIsDead = false;

	// 애님 몽타주 = 쉽게 생각하면 재생할 애니메이션이라고 생각하면 됨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damaged", meta = (AllowPrivateAccess = "true")) // 평타 Animation.
	class UAnimMontage *DamagedAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damaged", meta = (AllowPrivateAccess = "true")) // 평타 Animation.
	class UAnimMontage *DeadAnimMontage;

	void PlayDiavoloRandomDeadMontage();
	
	/**********************************************************************************************************/
	
	FTimerHandle MeleeAttackCooltimeTimer;
	bool bMeleeAttack = true; // 평타를 사용할 수 있는지 여부
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttack", meta = (AllowPrivateAccess = "true"))
	float MeleeAttackCooltime = 1.f; // 공격 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Attack", meta = (AllowPrivateAccess = "true")) // 평타 Animation.
	class UAnimMontage *MeleeAttackAnimMontage;
	
	/**********************************************************************************************************/
	
	FTimerHandle PassiveTimer;
	bool bPassive = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive", meta = (AllowPrivateAccess = "true"))
	float Passive_Cooltime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* Passive_AnimMontage;

	/**********************************************************************************************************/
	
	FTimerHandle Skill_1_CooltimeTimer;
	bool bSkill_1 = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 1", meta = (AllowPrivateAccess = "true"))
	float Skill_1_Cooltime = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 1", meta = (AllowPrivateAccess = "true")) 
	class UAnimMontage* Skill_1_AnimMontage;

	/**********************************************************************************************************/
	
	bool bSkill_2 = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 2", meta = (AllowPrivateAccess = "true"))
	float Skill_2_Cooltime = 10.f;
	
	FTimerHandle Skill_2_CooltimeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 2", meta = (AllowPrivateAccess = "true")) 
	class UAnimMontage* Skill_2_AnimMontage;

	/**********************************************************************************************************/
	
	bool bSkill_3 = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 3", meta = (AllowPrivateAccess = "true"))
	float Skill_3_Cooltime = 10.f;
	
	FTimerHandle Skill_3_CooltimeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 3", meta = (AllowPrivateAccess = "true")) 
	class UAnimMontage *Skill_3_AnimMontage;

	/**********************************************************************************************************/
	
	bool bSkill_4 = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 4", meta = (AllowPrivateAccess = "true"))
	float Skill_4_Cooltime = 10.f;
	
	FTimerHandle Skill_4_CooltimeTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill 4", meta = (AllowPrivateAccess = "true")) 
	class UAnimMontage *Skill_4_AnimMontage;

	/**********************************************************************************************************/
	
	bool bUlt = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ult", meta = (AllowPrivateAccess = "true"))
	float Ult_Cooltime = 10.f;
	
	FTimerHandle Ult_CooltimeTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ult", meta = (AllowPrivateAccess = "true")) 
	class UAnimMontage *Ult_AnimMontage;

public: // 주로 Setter와 Getter가 있음
	FORCEINLINE AOPPlayerController* GetOPPlayerController() const { return OPPlayerController; }
	FORCEINLINE FHitResult GetMouseCursorHit() { return MouseCursorHit; }

	FORCEINLINE bool GetbIsDamaged() const { return bIsDamaged; }
	FORCEINLINE void SetbIsDamagedTrue() { bIsDamaged = true; }
	FORCEINLINE bool GetbIsDead() const { return bIsDead; }
	FORCEINLINE void SetbIsDeadTrue() { bIsDead = true; }
	FORCEINLINE UAnimMontage* GetDamagedAnimMontage() const { return DamagedAnimMontage; }
	FORCEINLINE UAnimMontage* GetDeadAnimMontage() const { return DeadAnimMontage; }
	
	FORCEINLINE bool GetbMeleeAttack() const { return bMeleeAttack; }
	FORCEINLINE float GetMeleeAttackCooltime() const { return MeleeAttackCooltime; }
	FORCEINLINE void SetbMeleeAttack(bool value) { bMeleeAttack = value; }
	FORCEINLINE void SetbMeleeAttack_True() { bMeleeAttack = true; }
	FORCEINLINE void SetbMeleeAttack_False() { bMeleeAttack = false; }
	FORCEINLINE FTimerHandle GetMeleeAttackTimerHandle() { return MeleeAttackCooltimeTimer; }
	FORCEINLINE UAnimMontage* GetMeleeAttackAnimMontage() const { return MeleeAttackAnimMontage; }

	FORCEINLINE bool GetbPassive() const { return bPassive; }
	FORCEINLINE float GetPassiveCooltime() const { return Passive_Cooltime; }
	FORCEINLINE void SetbPassive(bool value) { bPassive = value; }
	FORCEINLINE void SetbPassive_True() { bPassive = true; }
	FORCEINLINE void SetbPassive_False() { bPassive = false; }
	FORCEINLINE FTimerHandle GetPassiveTimerHandle() const { return PassiveTimer; }
	FORCEINLINE UAnimMontage* GetPassiveAnimMontage() const { return Passive_AnimMontage; }
	
	FORCEINLINE bool GetbSkill_1() const { return bSkill_1; }
	FORCEINLINE float GetSkill_1_Cooltime() const { return Skill_1_Cooltime; }
	FORCEINLINE void SetbSkill_1(bool value) { bSkill_1 = value; }
	FORCEINLINE void SetbSkill_1_True() { bSkill_1 = true; }
	FORCEINLINE void SetbSkill_1_False() { bSkill_1 = false; }
	FORCEINLINE FTimerHandle GetSkill_1_TimerHandle() const { return Skill_1_CooltimeTimer; }
	FORCEINLINE UAnimMontage* GetSkill_1_AnimMontage() const { return Skill_1_AnimMontage; }
	
	FORCEINLINE bool GetbSkill_2() const { return bSkill_2; }
	FORCEINLINE float GetSkill_2_Cooltime() const { return Skill_2_Cooltime; }
	FORCEINLINE void SetbSkill_2(bool value) { bSkill_2 = value; }
	FORCEINLINE void SetbSkill_2_True()  { bSkill_2 = true; }
	FORCEINLINE void SetbSkill_2_False()  { bSkill_2 = false; }
	FORCEINLINE FTimerHandle GetSkill_2_TimerHandle() const { return Skill_2_CooltimeTimer; }
	FORCEINLINE UAnimMontage* GetSkill_2_AnimMontage() const { return Skill_2_AnimMontage; }
	
	FORCEINLINE bool GetbSkill_3() const { return bSkill_3; }
	FORCEINLINE float GetSkill_3_Cooltime() const { return Skill_3_Cooltime; }
	FORCEINLINE void SetbSkill_3(bool value) { bSkill_3 = value; }
	FORCEINLINE void SetbSkill_3_True()  { bSkill_3 = true; }
	FORCEINLINE void SetbSkill_3_False()  { bSkill_3 = false; }
	FORCEINLINE FTimerHandle GetSkill_3_TimerHandle() const { return Skill_3_CooltimeTimer; }
	FORCEINLINE UAnimMontage* GetSkill_3_AnimMontage() const { return Skill_3_AnimMontage; }
	
	FORCEINLINE bool GetbSkill_4() const { return bSkill_4; }
	FORCEINLINE float GetSkill_4_Cooltime() const { return Skill_4_Cooltime; }
	FORCEINLINE void SetbSkill_4(bool value) { bSkill_4 = value; }
	FORCEINLINE void SetbSkill_4_True()  { bSkill_4 = true; }
	FORCEINLINE void SetbSkill_4_False()  { bSkill_4 = false; }
	FORCEINLINE FTimerHandle GetSkill_4_TimerHandle() const { return Skill_4_CooltimeTimer; }
	FORCEINLINE UAnimMontage* GetSkill_4_AnimMontage() const { return Skill_4_AnimMontage; }
	
	FORCEINLINE bool GetbUlt() const { return bUlt; }
	FORCEINLINE float GetUlt_Cooltime() const { return Ult_Cooltime; }
	FORCEINLINE void SetbUlt(bool value) { bUlt = value; }
	FORCEINLINE void SetbUlt_True()  { bUlt = true; }
	FORCEINLINE void SetbUlt_False()  { bUlt = false; }
	FORCEINLINE FTimerHandle GetUlt_TimerHandle() const { return Ult_CooltimeTimer; }
	FORCEINLINE UAnimMontage* GetUlt_AnimMontage() const { return Ult_AnimMontage; }

	FORCEINLINE UOPAnimInstance* GetChampionAnimInstance() const { return ChampionAnimInstance; }

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetChampionSkeletalMeshComponent() const { return GetMesh(); }
	
};
