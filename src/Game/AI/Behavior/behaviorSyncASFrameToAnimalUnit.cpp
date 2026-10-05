#include "Game/AI/Behavior/behaviorSyncASFrameToAnimalUnit.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SyncASFrameToAnimalUnit::SyncASFrameToAnimalUnit(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SyncASFrameToAnimalUnit::~SyncASFrameToAnimalUnit() = default;

bool SyncASFrameToAnimalUnit::m6(sead::Heap* heap) {
    return true;
}

void SyncASFrameToAnimalUnit::m7() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    auto* rideable = mActor->m132();
    if (!rideable)
        return;
    const int bank = rideable->_18._9 ? rideable->_18._2e : rideable->_18.sub_7100E76CEC();
    list->sub_710115F158(list, *mTargetBone_s, 0, *mSeqBank_s, bank);
}

void SyncASFrameToAnimalUnit::m8() {}

void SyncASFrameToAnimalUnit::m9() {}

void SyncASFrameToAnimalUnit::loadParams() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

}  // namespace uking::behavior
