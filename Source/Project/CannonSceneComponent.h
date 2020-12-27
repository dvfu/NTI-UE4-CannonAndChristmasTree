#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProjectileActor.h"
#include "CannonSceneComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(MyCannonLog, Log, All)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_API UCannonSceneComponent : public USceneComponent {
	GENERATED_BODY()
public:
	UCannonSceneComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cannon")
	AProjectileActor* currentProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cannon")
	AActor* christmasTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cannon")
	AActor* floor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cannon")
	AProjectileActor* bestProjectile = nullptr;

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
	TUniquePtr<AProjectileActor> takeAShot(float angle) {
		auto actor = GetWorld()->SpawnActor<AProjectileActor>();
		actor->SetActorLocation(GetComponentLocation());
		actor->SetInitialVelocity(initialProjectileVelocity);
		actor->SetVelocityAngle(angle);
		actor->SetChristmasTree(christmasTree);
		lastAngle = angle;

		FScriptDelegate delegate;
		delegate.BindUFunction(this, "BeginOverlap");
		actor->OnActorBeginOverlap.Add(delegate);

		return TUniquePtr<AProjectileActor>(actor);
	}
	
	float initialProjectileVelocity;
	int projectileLeft;
	bool finished = false;

	float lastAngle = 0;
};
