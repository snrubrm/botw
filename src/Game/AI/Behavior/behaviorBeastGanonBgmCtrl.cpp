#include "Game/AI/Behavior/behaviorBeastGanonBgmCtrl.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::behavior {

BeastGanonBgmCtrl::BeastGanonBgmCtrl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BeastGanonBgmCtrl::~BeastGanonBgmCtrl() = default;

bool BeastGanonBgmCtrl::hasUpdateForPreDeleteCb() {
    return true;
}

void BeastGanonBgmCtrl::m9() {}

void BeastGanonBgmCtrl::loadParams() {
    getStaticParam(&mLevel_s, "Level");
}

void BeastGanonBgmCtrl::m7() {
    if (!_30)
        applyLevelMaybe();
}

void BeastGanonBgmCtrl::m8() {
    if (mActor->getRootAi()->getI() == 5)
        applyLevelMaybe();
}

bool BeastGanonBgmCtrl::updateForPreDelete() {
    if (auto* bgm = sub_7100FFE468())
        bgm->sub_71010101EC(0.0f);
    return true;
}

bool BeastGanonBgmCtrl::m6(sead::Heap* heap) {
    _30 = false;
    return true;
}

}  // namespace uking::behavior
