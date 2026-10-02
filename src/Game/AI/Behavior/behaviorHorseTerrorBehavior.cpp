#include "Game/AI/Behavior/behaviorHorseTerrorBehavior.h"

namespace uking::behavior {

HorseTerrorBehavior::HorseTerrorBehavior(const InitArg& arg) : TerrorBehavior(arg) {}

HorseTerrorBehavior::~HorseTerrorBehavior() = default;

bool HorseTerrorBehavior::m6(sead::Heap* heap) {
    return TerrorBehavior::m6(heap);
}

void HorseTerrorBehavior::m8() {
    TerrorBehavior::m8();
}

void HorseTerrorBehavior::m9() {
    TerrorBehavior::m9();
}

void HorseTerrorBehavior::loadParams() {
    TerrorBehavior::loadParams();
    getStaticParam(&mGear1Level_s, "Gear1Level");
    getStaticParam(&mGear2Level_s, "Gear2Level");
    getStaticParam(&mGear3Level_s, "Gear3Level");
    getStaticParam(&mGearTopLevel_s, "GearTopLevel");
    getStaticParam(&mOffsetDistanceSec_s, "OffsetDistanceSec");
}

}  // namespace uking::behavior
