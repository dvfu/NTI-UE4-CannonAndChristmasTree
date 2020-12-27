#pragma once

#include "CoreMinimal.h"

struct InputData {
	int projectileCount;
	float initialProjectileVelocity;

	InputData(int aProjectileCount, float aInitialProjectileVelocity);
};

class PROJECT_API MyProjectUtils {
public:
	static TUniquePtr<InputData> LoadInputFile();
	static void SaveOutputAndExit(float lastAngle, FVector lastProjectilePosition);
};
