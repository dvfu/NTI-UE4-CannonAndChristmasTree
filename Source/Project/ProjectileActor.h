#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ProjectileActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MyProjectileLog, Log, All)

UCLASS()
class PROJECT_API AProjectileActor : public AActor
{
	GENERATED_BODY()
public:
	AProjectileActor();

	void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	void SetVelocityAngle(float angle) const;
	void SetInitialVelocity(float velocity);
protected:
	void BeginPlay() override;
	float initialVelocity;
};
