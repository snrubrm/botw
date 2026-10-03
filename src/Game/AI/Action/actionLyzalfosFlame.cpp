#include "Game/AI/Action/actionLyzalfosFlame.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

LyzalfosFlame::LyzalfosFlame(const InitArg& arg) : ChemicalAttackBall(arg) {}

LyzalfosFlame::~LyzalfosFlame() = default;

bool LyzalfosFlame::init_(sead::Heap* heap) {
    if (!ChemicalAttackBall::init_(heap))
        return false;
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor))
        bullet->_cf4 |= 0x200;
    return true;
}

void LyzalfosFlame::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttackBall::enter_(params);
}

void LyzalfosFlame::leave_() {
    xlink::fade(_1c8, -1);
    ChemicalAttackBall::leave_();
}

void LyzalfosFlame::loadParams_() {
    ChemicalAttackBall::loadParams_();
    getStaticParam(&mParams.mLengthFrame_s, "LengthFrame");
    getStaticParam(&mParams.mAtResetTime_s, "AtResetTime");
    getStaticParam(&mParams.mAtChaseFrame_s, "AtChaseFrame");
    getStaticParam(&mParams.mBindGrabNodeIdx_s, "BindGrabNodeIdx");
    getStaticParam(&mParams.mChaseMax_s, "ChaseMax");
    getStaticParam(&mParams.mChaseRate_s, "ChaseRate");
    getStaticParam(&mParams.mOffsetRot_s, "OffsetRot");
}

void LyzalfosFlame::calc_() {
    ChemicalAttackBall::calc_();
}

bool LyzalfosFlame::m33() {
    return false;
}

}  // namespace uking::action
