#include "Game/AI/Behavior/behaviorAssassinBossBgmOnDelete.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

AssassinBossBgmOnDelete::AssassinBossBgmOnDelete(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmOnDelete::~AssassinBossBgmOnDelete() = default;

bool AssassinBossBgmOnDelete::m6(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmOnDelete::m7() {}

void AssassinBossBgmOnDelete::m8() {}

void AssassinBossBgmOnDelete::m9() {
    if (auto* bgm = sub_7100FFDFDC()) {
        if (mActor->isDeletedOrDeleting() || !mActor->isAwakeMaybe())
            bgm->sub_7100FF6268();
    }
}

void AssassinBossBgmOnDelete::loadParams() {

}

}  // namespace uking::behavior
