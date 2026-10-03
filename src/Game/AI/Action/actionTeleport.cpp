#include "Game/AI/Action/actionTeleport.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

Teleport::Teleport(const InitArg& arg) : TeleportBase(arg) {}

Teleport::~Teleport() = default;

bool Teleport::init_(sead::Heap* heap) {
    return TeleportBase::init_(heap);
}

void Teleport::enter_(ksys::act::ai::InlineParamPack* params) {
    TeleportBase::enter_(params);
    _94 = sead::Vector3f::zero;
    const f32 angle = s32(sead::GlobalRandom::instance()->getU32(360)) / 360.0f * sead::Mathf::pi2();
    _94.x = sead::Mathf::cos(angle) * *mDistXZ_s;
    _94.z = sead::Mathf::sin(angle) * *mDistXZ_s;
    _94.y = *mDistY_s;
}

void Teleport::leave_() {
    TeleportBase::leave_();
}

void Teleport::loadParams_() {
    TeleportBase::loadParams_();
    getStaticParam(&mDistXZ_s, "DistXZ");
    getStaticParam(&mDistY_s, "DistY");
}

void Teleport::calc_() {
    TeleportBase::calc_();
}

void Teleport::m36() {
    _88 = sub_71002955BC() + _94;
}

}  // namespace uking::action
