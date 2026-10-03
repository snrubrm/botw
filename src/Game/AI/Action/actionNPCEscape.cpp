#include "Game/AI/Action/actionNPCEscape.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

NPCEscape::NPCEscape(const InitArg& arg) : RandomMoveAction(arg) {}

NPCEscape::~NPCEscape() = default;

bool NPCEscape::init_(sead::Heap* heap) {
    _a8 = sead::DynamicCast<uking::act::NPC>(mActor);
    return true;
}

void NPCEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    RandomMoveAction::enter_(params);
}

void NPCEscape::leave_() {
    auto* cc = mActor->getCharacterController();
    auto* physics = mActor->getPhysics();
    if (cc && physics) {
        const s32 idx = physics->sub_7100FBE7F0("Standing");
        if (idx >= 0)
            cc->sub_7100F5F270(idx);
    }
    RandomMoveAction::leave_();
}

void NPCEscape::loadParams_() {
    RandomMoveAction::loadParams_();
    getStaticParam(&mWallHitTime_s, "WallHitTime");
    getStaticParam(&mStopTime_s, "StopTime");
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mMinDistance_s, "MinDistance");
    getStaticParam(&mAngularRange_s, "AngularRange");
    getStaticParam(&mVerticalEscapeSpeed_s, "VerticalEscapeSpeed");
    getStaticParam(&mIsTurnToTargetPos_s, "IsTurnToTargetPos");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

void NPCEscape::calc_() {
    RandomMoveAction::calc_();
}

}  // namespace uking::action
