#include "Game/AI/AI/aiPriestBossShadowCloneThrow.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossShadowCloneThrow::PriestBossShadowCloneThrow(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (SafeString members); written
// like upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
PriestBossShadowCloneThrow::~PriestBossShadowCloneThrow() {
    ;
}

bool PriestBossShadowCloneThrow::init_(sead::Heap* heap) {
    for (auto& sender : _b8)
        sender._8 = &mActor->getMessageTransceiver();
    return true;
}

void PriestBossShadowCloneThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("準備完了待ち", params);
    _80 = ksys::Timer(*mPrepareTimer_s, *mPrepareTimer_s);
    _8c = 0;
    _90 = 2;
    _3ea = false;
    _3e8 = true;
    _3e9 = false;
}

bool PriestBossShadowCloneThrow::m37() {
    return mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                  true);
}

void PriestBossShadowCloneThrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossShadowCloneThrow::loadParams_() {
    getStaticParam(&mShadowCloneOffsetY_s, "ShadowCloneOffsetY");
    getStaticParam(&mShadowCloneRadius_s, "ShadowCloneRadius");
    getStaticParam(&mShadowCloneAngleOffset_s, "ShadowCloneAngleOffset");
    getStaticParam(&mPrepareTimer_s, "PrepareTimer");
    getStaticParam(&mShadowCloneLefeBoneName_s, "ShadowCloneLefeBoneName");
    getStaticParam(&mShadowCloneRightBoneName_s, "ShadowCloneRightBoneName");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
