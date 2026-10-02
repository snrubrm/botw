#include "Game/AI/Behavior/behaviorGelDisableEyeControl.h"
#include "Game/Actor/actGelEnemy.h"

namespace uking::behavior {

GelDisableEyeControl::GelDisableEyeControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

GelDisableEyeControl::~GelDisableEyeControl() = default;

bool GelDisableEyeControl::m6(sead::Heap* heap) {
    return true;
}

void GelDisableEyeControl::m7() {}

void GelDisableEyeControl::loadParams() {
    getStaticParam(&mIsImmediate_s, "IsImmediate");
}

void GelDisableEyeControl::m8() {
    auto* gel = sead::DynamicCast<uking::act::GelEnemy>(mActor);
    if (!gel)
        return;
    const bool immediate = *mIsImmediate_s;
    gel->_1678 |= 2;
    if (immediate)
        gel->_1620.z = 1.0f;
}

void GelDisableEyeControl::m9() {
    if (auto* gel = sead::DynamicCast<uking::act::GelEnemy>(mActor))
        gel->_1678 &= ~2;
}

}  // namespace uking::behavior
