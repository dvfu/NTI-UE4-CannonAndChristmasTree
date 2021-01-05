#include "MyProjectUtils.h"
#include "ProjectileActor.h"

InputData::InputData(int aProjectileCount, float aInitialProjectileVelocity)
	: projectileCount(aProjectileCount), initialProjectileVelocity(aInitialProjectileVelocity)
{}

TUniquePtr<InputData> MyProjectUtils::LoadInputFile() {
	auto projectileCount = 0;
	auto initialProjectileVelocity = 0.0f;

	auto launchDir = FPaths::LaunchDir();
	FString text;
	FFileHelper::LoadFileToString(text, *FPaths::Combine(launchDir, FString("input.txt")));
	if (text.Len() > 0) {
		int32 pos;
		text.FindChar(_T(' '), pos);
		FCString::Atof(*text.Mid(0, pos));

		projectileCount = FCString::Atoi(*text.Mid(pos + 1));
		initialProjectileVelocity = FCString::Atof(*text.Mid(0, pos));
	}
	else {
		ensureMsgf(false, TEXT("Put your input.txt here %s"), *launchDir);

		// default values
		initialProjectileVelocity = 1000;
		projectileCount = 8;
	}
	
	return MakeUnique<InputData>(projectileCount, initialProjectileVelocity);
}

void MyProjectUtils::SaveOutputAndExit(float lastAngle, AProjectileActor* projectile) {
	TOptional<FVector> optLocation;
	if (projectile) {
		optLocation = projectile->GetLocationOfOverlappingWithTree();
	}

	TArray<FString> outputItems;
	if (optLocation.IsSet()) {
		const auto location = optLocation.GetValue();
		for (const auto& value : { lastAngle, location.X, location.Y, location.Z }) {
			outputItems.Add(FString::SanitizeFloat(value));
		}
	}

	const auto path = FPaths::Combine(FPaths::LaunchDir(), FString("output.txt"));
	FFileHelper::SaveStringToFile(GetData(FString::Join(outputItems, _T(" "))), *path);
	FGenericPlatformMisc::RequestExit(false);
}
