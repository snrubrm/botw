#include "Game/AI/AI/aiGuardianRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianRoot::GuardianRoot(const InitArg& arg) : GuardianAI(arg) {}

GuardianRoot::~GuardianRoot() = default;

bool GuardianRoot::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianRoot::leave_() {
    GuardianAI::leave_();
}

// NON_MATCHING: the two flag updates merge into a shared OR operation.
bool GuardianRoot::handleMessage_(const ksys::Message* message) {
    auto* guardian = sub_710040DA6C();
    if (!message || !guardian)
        return true;
    if (_50.sub_710070AFFC(message, guardian))
        return true;
    if (message->getType() == 0x800004b) {
        _48 |= 1;
    } else if (message->getType() == 0x800004c) {
        _48 |= 2;
    } else if (message->getType() == 0x3000003) {
        auto* life = guardian->getLife();
        if (life && *life < 1)
            return true;
        changeChild("待機", nullptr);
        sub_710040DDB0(0);
        sub_710040DE48(false);
        return false;
    }
    return true;
}

void GuardianRoot::loadParams_() {
    GuardianAI::loadParams_();
    getMapUnitParam(&mIsSuspended_m, "IsSuspended");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
}

void GuardianRoot::changeToReactToSight() {
    sead::Vector3f pos;
    if (sub_710040E008(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("視覚反応", &pack);
        sub_710040DDB0(4);
        sub_710040DE48(false);
    }
}

void GuardianRoot::changeToReactToSound() {
    sead::Vector3f pos;
    if (sub_710040E048(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("音反応", nullptr);
        sub_710040DDB0(2);
        sub_710040DE48(false);
    }
}

}  // namespace uking::ai
