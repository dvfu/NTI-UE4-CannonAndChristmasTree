#include "ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"

DEFINE_LOG_CATEGORY(MyProjectileLog)

AProjectileActor::AProjectileActor() {
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile"));
	CollisionComponent->InitSphereRadius(1.f);
	CollisionComponent->SetRelativeScale3D({ 0.1f, 0.1f, 0.1f });
	CollisionComponent->SetRelativeRotation({ 0.f, 0.f, 0.f });
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHAPE"));
	MeshComponent->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	MeshComponent->SetStaticMesh(SphereMeshAsset.Object);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->MaxSpeed = 0;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.5f;

	CollisionComponent->GetCollisionResponseToComponent(CollisionComponent);
}

void AProjectileActor::SetVelocityAngle(float angle) const {
	const auto radians = FMath::DegreesToRadians(angle);
	ProjectileMovementComponent->InitialSpeed = initialVelocity;
	ProjectileMovementComponent->Velocity = { -initialVelocity * FMath::Cos(radians), 0.f, initialVelocity * FMath::Sin(radians) };
}

void AProjectileActor::SetInitialVelocity(float velocity) {
	initialVelocity = velocity;
}

void AProjectileActor::BeginPlay() {
	Super::BeginPlay();
}

void AProjectileActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
