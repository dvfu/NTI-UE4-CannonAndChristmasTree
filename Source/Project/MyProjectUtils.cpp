#include "MyProjectUtils.h"

InputData::InputData(int aProjectileCount, float aInitialProjectileVelocity)
	: projectileCount(aProjectileCount), initialProjectileVelocity(aInitialProjectileVelocity)
{}

TUniquePtr<InputData> MyProjectUtils::LoadInputFile() {
	auto projectileCount = 0;
	auto initialProjectileVelocity = 0.0f;

	FString text;
	FFileHelper::LoadFileToString(text, *FPaths::Combine(FPaths::LaunchDir(), FString("input.txt")));
	if (text.Len() > 0) {
		int32 pos;
		text.FindChar(_T(' '), pos);
		FCString::Atof(*text.Mid(0, pos));

		projectileCount = FCString::Atoi(*text.Mid(pos + 1));
		initialProjectileVelocity = FCString::Atof(*text.Mid(0, pos));
	}
	
	return MakeUnique<InputData>(projectileCount, initialProjectileVelocity);
}

void MyProjectUtils::SaveOutputAndExit(float lastAngle, FVector lastProjectilePosition) {
	TArray<FString> outputItems;
	for (const auto& value : { lastAngle, lastProjectilePosition.X, lastProjectilePosition.Y, lastProjectilePosition.Z }) {
		outputItems.Add(FString::SanitizeFloat(value));
	}

	const auto path = FPaths::Combine(FPaths::LaunchDir(), FString("output.txt"));
	FFileHelper::SaveStringToFile(GetData(FString::Join(outputItems, _T(" "))), *path);
	FGenericPlatformMisc::RequestExit(false);
}
