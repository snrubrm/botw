#include "Game/AI/Action/actionNearHomePosTeleport.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

NearHomePosTeleport::NearHomePosTeleport(const InitArg& arg) : LandTeleport(arg) {}

NearHomePosTeleport::~NearHomePosTeleport() = default;

bool NearHomePosTeleport::init_(sead::Heap* heap) {
    return LandTeleport::init_(heap);
}

void NearHomePosTeleport::enter_(ksys::act::ai::InlineParamPack* params) {
    LandTeleport::enter_(params);
}

void NearHomePosTeleport::leave_() {
    LandTeleport::leave_();
}

void NearHomePosTeleport::loadParams_() {
    LandTeleport::loadParams_();
}

void NearHomePosTeleport::calc_() {
    LandTeleport::calc_();
}

// NON_MATCHING: scheduling of the three `_a4` stores (the original delays the first one behind the loads
// for z and keeps the 1.0f constant for the end).
void NearHomePosTeleport::m40() {
    sead::Vector3f dir;
    mActor->getHomePos(&dir);
    dir -= mActor->getMtx().getTranslation();
    dir.normalize();
    const f32 angle =
        (s32(sead::GlobalRandom::instance()->getU32(90)) - 45) / 360.0f * sead::Mathf::pi2();
    ksys::util::sub_71011EF010(&dir, angle);
    dir.x = *mDistXZ_s * dir.x;
    _a4.x = dir.x;
    _a4.y = 1.0f;
    _a4.z = *mDistXZ_s * dir.z;
}

bool NearHomePosTeleport::m41() {
    return sub_71001CDF68(m33());
}

}  // namespace uking::action
