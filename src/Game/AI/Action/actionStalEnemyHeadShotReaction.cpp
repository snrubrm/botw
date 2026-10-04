#include "Game/AI/Action/actionStalEnemyHeadShotReaction.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

StalEnemyHeadShotReaction::StalEnemyHeadShotReaction(const InitArg& arg)
    : ActionWithPosAngReduce(arg) {}

StalEnemyHeadShotReaction::~StalEnemyHeadShotReaction() = default;

bool StalEnemyHeadShotReaction::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StalEnemyHeadShotReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void StalEnemyHeadShotReaction::leave_() {
    ActionWithPosAngReduce::leave_();
    auto* actor = mActor;
    if (_90 >= 1) {
        _90 = 0;
        sub_71007275C8(sub_7100724D7C(actor));
    }
    if (*mIsTgOff_s)
        sub_71007A3800(actor);
    sub_7100738DC8(actor);
}

void StalEnemyHeadShotReaction::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mUseAddVec_s, "UseAddVec");
    getStaticParam(&mIsTgOff_s, "IsTgOff");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mHeadBoneKey_s, "HeadBoneKey");
    getStaticParam(&mAddVec_s, "AddVec");
    getStaticParam(&mRotVec_s, "RotVec");
}

void StalEnemyHeadShotReaction::calc_() {
    ActionWithPosAngReduce::calc_();
    if (_90 > 0) {
        --_90;
        if (_90 == 0)
            sub_71007275C8(sub_7100724D7C(mActor));
    }
    if (!mASName_s.isEmpty() && isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
