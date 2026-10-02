#include "Game/AI/Behavior/behaviorAwarenessScale.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::behavior {

AwarenessScale::AwarenessScale(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AwarenessScale::~AwarenessScale() = default;

bool AwarenessScale::m6(sead::Heap* heap) {
    return true;
}

void AwarenessScale::m7() {}

void AwarenessScale::loadParams() {
    getStaticParam(&mSight_s, "Sight");
    getStaticParam(&mHearing_s, "Hearing");
    getStaticParam(&mTerror_s, "Terror");
    getStaticParam(&mWorry_s, "Worry");
}

void AwarenessScale::m8() {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    if (*mSight_s <= 0)
        awareness->sub_7100D7EAE4(0);
    else
        awareness->sub_7100D7EC14(0, awareness->sub_7100D7EC34(0) * *mSight_s);
    if (*mHearing_s <= 0)
        awareness->sub_7100D7EAE4(1);
    else
        awareness->sub_7100D7EC14(1, awareness->sub_7100D7EC34(1) * *mHearing_s);
    if (*mTerror_s <= 0)
        awareness->sub_7100D7EAE4(2);
    else
        awareness->sub_7100D7EC14(2, awareness->sub_7100D7EC34(2) * *mTerror_s);
    if (*mWorry_s <= 0)
        awareness->sub_7100D7EAE4(3);
    else
        awareness->sub_7100D7EC14(3, awareness->sub_7100D7EC34(3) * *mWorry_s);
}

void AwarenessScale::m9() {
    if (mActor->getRootAi()->isActorDeletedOrDeleting())
        return;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    if (*mSight_s <= 0)
        awareness->sub_7100D7E9BC(0);
    else
        awareness->sub_7100D7EC14(0, awareness->sub_7100D7EC34(0) / *mSight_s);
    if (*mHearing_s <= 0)
        awareness->sub_7100D7E9BC(1);
    else
        awareness->sub_7100D7EC14(1, awareness->sub_7100D7EC34(1) / *mHearing_s);
    if (*mTerror_s <= 0)
        awareness->sub_7100D7E9BC(2);
    else
        awareness->sub_7100D7EC14(2, awareness->sub_7100D7EC34(2) / *mTerror_s);
    if (*mWorry_s <= 0)
        awareness->sub_7100D7E9BC(3);
    else
        awareness->sub_7100D7EC14(3, awareness->sub_7100D7EC34(3) / *mWorry_s);
}

}  // namespace uking::behavior
