#include "Game/Actor/Behavior/behaviorHorseTerrorBehavior.h"

#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

HorseTerrorBehavior::HorseTerrorBehavior(const InitArg& arg) : TerrorBehavior(arg) {}

HorseTerrorBehavior::~HorseTerrorBehavior() = default;

bool HorseTerrorBehavior::m6(sead::Heap* heap) {
    return TerrorBehavior::m6(heap);
}

void HorseTerrorBehavior::m8() {
    TerrorBehavior::m8();
}

// NON_MATCHING: row selection stays in registers; switch and request setup stack scheduling differ.
void HorseTerrorBehavior::m7() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;
    const act::Rideable::Gear gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b);
    f32 level = 0.0f;
    switch (gear) {
    case act::Rideable::Gear::_0: level = *mLevel_s; break;
    case act::Rideable::Gear::_1: level = *mGear1Level_s; break;
    case act::Rideable::Gear::_2: level = *mGear2Level_s; break;
    case act::Rideable::Gear::_3: level = *mGear3Level_s; break;
    case act::Rideable::Gear::_4: level = *mGearTopLevel_s; break;
    }
    s32 row = rideable->_18._a;
    const auto* speed = &act::sUnk_7102603058;
    if (gear != act::Rideable::Gear::_0 && rideable->_170) {
        if (row >= rideable->_178)
            row = 0;
        speed = &rideable->_170->mGears[row][int(gear) - 1];
    }
    const f32 distance = speed->mSpeed * rideable->_164 * *mOffsetDistanceSec_s;
    const u32 flags = sub_7100E93098();
    _a0._10._10.makeAllZero();
    _a0._10._18.m15();
    _a0.x(2, flags, level);
    _a0._88.set(0.0f, 0.0f, distance);
    _a0.setRadius(*mRadius_s);
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
