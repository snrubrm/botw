#include "Game/AI/AI/aiEnemyMimicrySelect.h"

namespace uking::ai {

EnemyMimicrySelect::EnemyMimicrySelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMimicrySelect::~EnemyMimicrySelect() = default;

bool EnemyMimicrySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyMimicrySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = 0xff;
    if (*mIsMimicry_m)
        sub_71003988E0(params);
    else
        sub_7100398A34(params);
}

bool EnemyMimicrySelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyMimicrySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyMimicrySelect::loadParams_() {
    getMapUnitParam(&mIsMimicry_m, "IsMimicry");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
