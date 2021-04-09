#pragma once
#include "GOAPActionResult.generated.h"

UENUM(BlueprintType)
enum class EGOAPActionResult : uint8
{
	Continue,
	Cancel,
	Complete
};
