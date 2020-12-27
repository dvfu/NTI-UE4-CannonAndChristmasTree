#define _CRT_SECURE_NO_WARNINGS

#include "CannonSceneComponent.h"
#include "ProjectileActor.h"
#include "MyProjectUtils.h"

DEFINE_LOG_CATEGORY(MyCannonLog)

UCannonSceneComponent::UCannonSceneComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UCannonSceneComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor == christmasTree) {

	}
	else if (OtherActor == floor) {

	}

	bestProjectile = currentProjectile;
	currentProjectile->OnActorBeginOverlap.Clear();
	currentProjectile = nullptr;
}

void UCannonSceneComponent::BeginPlay() {
	Super::BeginPlay();

	const auto data = MyProjectUtils::LoadInputFile();
	projectileLeft = data->projectileCount;
	initialProjectileVelocity = data->initialProjectileVelocity;
}

void UCannonSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto angle = 90.f;
	if (projectileLeft > 0 && currentProjectile == nullptr) {
		--projectileLeft;
		currentProjectile = takeAShot(angle).Release();
	}

	if (projectileLeft == 0 && currentProjectile == nullptr && !finished) {
		MyProjectUtils::SaveOutputAndExit(lastAngle, bestProjectile);
		finished = true;
	}
}
