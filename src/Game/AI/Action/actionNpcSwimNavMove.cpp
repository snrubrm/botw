#include "Game/AI/Action/actionNpcSwimNavMove.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

void NpcSwimNavMove::m34() {
    if (m35().isEmpty())
        return;
    playAS(m35().cstr(), true, 0, 0, -1.0f);
}

NpcSwimNavMove::NpcSwimNavMove(const InitArg& arg) : RandomMoveAction(arg) {}

NpcSwimNavMove::~NpcSwimNavMove() = default;

bool NpcSwimNavMove::init_(sead::Heap* heap) {
    return RandomMoveAction::init_(heap);
}

void NpcSwimNavMove::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void NpcSwimNavMove::leave_() {
    auto* actor = mActor;
    if (auto* npc = sead::DynamicCast<act::NPC>(actor))
        npc->_fe8 &= ~0x10000000;
    _130.resetMotionType(_130.sub_710072ACF8(actor));
    RandomMoveAction::leave_();
}

void NpcSwimNavMove::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mUpdateTargetPosInterval_s, "UpdateTargetPosInterval");
    getStaticParam(&mRotRadPerSec_s, "RotRadPerSec");
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinHeight_s, "FinHeight");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatRadius_s, "FloatRadius");
    getStaticParam(&mFloatCycleTime_s, "FloatCycleTime");
    getStaticParam(&mChangeDepthSpeed_s, "ChangeDepthSpeed");
    getStaticParam(&mIsClampRotVel_s, "IsClampRotVel");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAddCalcStickX_s, "AddCalcStickX");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void NpcSwimNavMove::calc_() {
    RandomMoveAction::calc_();
}

s32 NpcSwimNavMove::m32(RandomMovePoints* points) {
    points->add(*mTargetPos_d);
    return *mUpdateTargetPosInterval_s;
}

}  // namespace uking::action
