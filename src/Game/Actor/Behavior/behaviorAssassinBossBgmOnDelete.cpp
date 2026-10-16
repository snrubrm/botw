#include "Game/Actor/Behavior/behaviorAssassinBossBgmOnDelete.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

AssassinBossBgmOnDelete::AssassinBossBgmOnDelete(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmOnDelete::~AssassinBossBgmOnDelete() = default;

bool AssassinBossBgmOnDelete::init_(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmOnDelete::calc() {}

void AssassinBossBgmOnDelete::enter() {}

void AssassinBossBgmOnDelete::leave() {
    if (auto* bgm = sub_7100FFDFDC()) {
        if (mActor->isDeletedOrDeleting() || !mActor->isAwakeMaybe())
            bgm->sub_7100FF6268();
    }
}

void AssassinBossBgmOnDelete::loadParams() {

}

}  // namespace uking::behavior
