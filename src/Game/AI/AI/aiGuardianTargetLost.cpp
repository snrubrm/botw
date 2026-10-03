#include "Game/AI/AI/aiGuardianTargetLost.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GuardianTargetLost::GuardianTargetLost(const InitArg& arg) : GuardianAI(arg) {}

GuardianTargetLost::~GuardianTargetLost() = default;

bool GuardianTargetLost::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianTargetLost::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
    mActor->getMtx().getTranslation(_44);
    sub_710040E008(&_38);
    if (auto* nav = mActor->m45()) {
        sead::Vector3f pos;
        auto result = nav->sub_7100F76078(&pos, _38, 3.0f);
        if (result.sub_7100F7EB40())
            _38 = pos;
    }
    _50 = 0;
    _54 = 0;
    sub_710042BE9C();
}

// NON_MATCHING: the original does not hoist the two identical actor-translation copies out of the
// rail/no-rail branches and keeps the SafeString vtable store for "DynStopTime" inside them
void GuardianTargetLost::sub_710042BE9C() {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_38, "DynTargetPos", -1);
    params.addVec3(_38, "TargetPos", -1);
    params.addVec3(mActor->getMtx().getTranslation(), "DynStartPos", -1);

    sead::Vector3f pos;
    if (auto* rail = sub_7100EEF034(mActor, 0)) {
        mActor->getMtx().getTranslation(pos);
        const f32 progress = sub_7100EEF7AC(rail, pos, false, 0.2f, -0.0f);
        rail->calcTranslate(&pos, progress);
    } else {
        mActor->getMtx().getTranslation(pos);
    }
    params.addFloat(180.0f, "DynStopTime", -1);
    params.addVec3(pos, "DynStopPos", -1);
    _54 = 0;
    changeChild("移動", &params);
}

void GuardianTargetLost::leave_() {
    GuardianAI::leave_();
}

void GuardianTargetLost::loadParams_() {
    GuardianAI::loadParams_();
    getStaticParam(&mLostCountMax_s, "LostCountMax");
    getStaticParam(&mMoveRange_s, "MoveRange");
    getStaticParam(&mBackOffset_s, "BackOffset");
    getStaticParam(&mAirThreshold_s, "AirThreshold");
}

}  // namespace uking::ai
