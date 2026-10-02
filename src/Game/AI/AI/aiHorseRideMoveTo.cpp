#include "Game/AI/AI/aiHorseRideMoveTo.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideMoveTo::HorseRideMoveTo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideMoveTo::~HorseRideMoveTo() = default;

bool HorseRideMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("指令", &pack);
    _60.x();
    _98.x();
}

void HorseRideMoveTo::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        if (child->isChangeable()) {
            auto* actor = mActor;
            const f32 x = actor->getMtx().m[0][3];
            const f32 z = actor->getMtx().m[2][3];
            const f32 range = *mFinRadius_s + sub_71007320F0(actor, *mWeaponIdx_s);
            const f32 dx = x - mTargetPos_d->x;
            const f32 dz = z - mTargetPos_d->z;
            if (dx * dx + dz * dz <= range * range || _60._30)
                setFinished();
            else if (_98._30)
                setFailed();
        }
    } else if (isCurrentChild("指令")) {
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &params);
    } else if (child->isFinished()) {
        setFinished();
    } else {
        setFailed();
    }
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void HorseRideMoveTo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideMoveTo::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool HorseRideMoveTo::handleMessage_(const ksys::Message& message) {
    return _60.m2(message) || _98.m2(message);
}

}  // namespace uking::ai
