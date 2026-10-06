#include "Game/AI/AI/aiGuardianRoot.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapRail.h"

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

// NON_MATCHING: register allocation (the original keeps the rail pointer in x20 from the call on and the string-temp
// vtable pointer in x22).
void GuardianRoot::changeToChase() {
    sead::Vector3f pos;
    if (sub_710040E008(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        sead::Vector3f stop_pos;
        if (auto* rail = sub_7100EEF034(mActor, 0)) {
            mActor->getMtx().getTranslation(stop_pos);
            const f32 progress = sub_7100EEF7AC(rail, stop_pos, false, 0.2f, -0.0f);
            rail->calcTranslate(&stop_pos, progress);
        } else {
            mActor->getMtx().getTranslation(stop_pos);
        }
        pack.addFloat(180.0f, "DynStopTime", -1);
        pack.addVec3(stop_pos, "DynStopPos", -1);
        changeChild("追跡", &pack);
        sub_710040DDB0(5);
        sub_710040DE48(true);
    }
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
