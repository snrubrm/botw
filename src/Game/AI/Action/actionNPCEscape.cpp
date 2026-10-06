#include "Game/AI/Action/actionNPCEscape.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

NPCEscape::NPCEscape(const InitArg& arg) : RandomMoveAction(arg) {}

NPCEscape::~NPCEscape() = default;

void NPCEscape::sub_71001F76D8() {
    if (!_a8)
        return;
    const u32 flags = _a8->_fe8;
    auto* controller = mActor->getCharacterController();
    auto* physics = mActor->getPhysics();
    const bool has_both = controller && physics;
    if (flags & 0x8000000) {
        if (has_both) {
            const s32 idx = physics->sub_7100FBE7F0(sead::SafeString("Swimming"));
            if (idx >= 0)
                controller->sub_7100F5F270(idx);
        }
        playAS("Swim_Escape", true, 0, 0, -1.0f);
    } else {
        if (has_both) {
            const s32 idx = physics->sub_7100FBE7F0(sead::SafeString("Standing"));
            if (idx >= 0)
                controller->sub_7100F5F270(idx);
        }
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    }
}

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

s32 NPCEscape::m32(RandomMovePoints* points) {
    points->add(_9c);
    return -1;
}

}  // namespace uking::action
