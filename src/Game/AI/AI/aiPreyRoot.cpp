#include "Game/AI/AI/aiPreyRoot.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PreyRoot::PreyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyRoot::~PreyRoot() = default;

bool PreyRoot::init_(sead::Heap* heap) {
    _188 = sead::DynamicCast<act::Enemy>(mActor);
    return _188 != nullptr;
}

void PreyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyRoot::loadParams_() {
    getStaticParam(&mAfterEscapeForceEndState_s, "AfterEscapeForceEndState");
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mEscapeForceEndTime_s, "EscapeForceEndTime");
    getStaticParam(&mIsCheckFreeFall_s, "IsCheckFreeFall");
    getStaticParam(&mIsCheckStuckConsiderY_s, "IsCheckStuckConsiderY");
    getStaticParam(&mIsUseWeakForcePushOutside_s, "IsUseWeakForcePushOutside");
    getStaticParam(&mIsEnableEscapeForceEndCheck_s, "IsEnableEscapeForceEndCheck");
    getAITreeVariable(&mCreateDeadConditionType_a, "CreateDeadConditionType");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
    getAITreeVariable(&mIsChangeableStateFreeFall_a, "IsChangeableStateFreeFall");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

bool PreyRoot::m34() {
    if (!mActor->get68f().load())
        return false;
    const f32 y = mActor->getMtx().m[1][3];
    return mActor->get6f0() - y > *mInWaterDepth_s;
}

bool PreyRoot::m35() {
    return m34() && !isCurrentChild("水中行動");
}

// NON_MATCHING: the original's SEAD_ENUM round trip uses the stack slot shared with the SafeString (sp+0, as for an
// inlined by-value parameter); a named local gets its own slot at x29-4
bool PreyRoot::m36() {
    if (mActor->getHorseOptionsMaybe()) {
        const act::Unk_7100e8b2b8::Unk8 type = mActor->getHorseOptionsMaybe()->Unk_7100e8b2b8::_8 & 0xff;
        return int(type) != 0 && !isCurrentChild("騎乗中");
    }
    return false;
}

// NON_MATCHING: the target returns _205 without normalising it (no cmp/cset)
bool PreyRoot::m37() {
    if (*mIsChangeableStateFreeFall_a && !isCurrentChild("落下"))
        return _205;
    return false;
}

bool PreyRoot::m38() {
    if (isCurrentChild("落下")) {
        if (!_205)
            return true;
    }
    return false;
}

bool PreyRoot::handleMessage_(const ksys::Message& message) {
    if (!isCurrentChild("所持")) {
        auto* actor = mActor;
        if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40000000) && !_148._30 &&
            _148.m2(message)) {
            _148.sub_710070B5A0(actor);
            return true;
        }
    }
    return false;
}

}  // namespace uking::ai
