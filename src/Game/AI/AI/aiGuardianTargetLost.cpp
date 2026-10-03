#include "Game/AI/AI/aiGuardianTargetLost.h"
#include "KingSystem/ActorSystem/actActor.h"
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
