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
	void SetChristmasTree(AActor* actor);
	TOptional<FVector> GetLocationOfOverlappingWithTree() const;
	UFUNCTION() void BeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
protected:
	void BeginPlay() override;
private:
	float initialVelocity;
	AActor* christmasTree = nullptr;
	TOptional<FVector> overlapLocation;
};
