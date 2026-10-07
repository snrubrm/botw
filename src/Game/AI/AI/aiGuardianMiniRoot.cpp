#include "Game/AI/AI/aiGuardianMiniRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

GuardianMiniRoot::GuardianMiniRoot(const InitArg& arg) : EnemyRoot(arg) {}

GuardianMiniRoot::~GuardianMiniRoot() = default;

bool GuardianMiniRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void GuardianMiniRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void GuardianMiniRoot::leave_() {
    EnemyRoot::leave_();
    mActor->sub_71011DA868(&_288);
    stopXLinks();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62DD0(1.0f);
}

// NON_MATCHING: loop strength reduction only: the original keeps `this + 0x330` / `this + 0x393` as two induction
// pointers (x24 / x26, `this` is dead after them); ours keeps `this` and a scaled offset (one extra register).
void GuardianMiniRoot::stopXLinks() {
    s32 i = 0;
    for (auto& handles : _330) {
        handles.mELink.kill();
        handles.mSLink.fade();
        _393[i++] = false;
    }
}

void GuardianMiniRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mNeckRotRatio_s, "NeckRotRatio");
    getStaticParam(&mJustGuardNumForBreak_s, "JustGuardNumForBreak");
    getStaticParam(&mRotStopSpeed_s, "RotStopSpeed");
    getAITreeVariable(&mDamagedCount_a, "DamagedCount");
    getAITreeVariable(&mIsTransformedGuardianMini_a, "IsTransformedGuardianMini");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

bool sub_71004282EC(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    const bool* value = nullptr;
    auto* root_ai = actor->getRootAi();
    if (!root_ai)
        return false;
    if (!root_ai->getMapUnitParam(&value, "IsAnnihilateDungeonEnemy"))
        return false;
    return *value;
}

}  // namespace uking::ai
