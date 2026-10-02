#include "Game/AI/AI/aiEnemyHideGrass.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyHideGrass::EnemyHideGrass(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHideGrass::~EnemyHideGrass() = default;

bool EnemyHideGrass::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyHideGrass::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* awareness = mActor->getAwareness()) {
        _48 = awareness->sub_7100D7EC34(0);
        if (*mSightRatio_s > 0.0f)
            awareness->sub_7100D7EC14(0, *mSightRatio_s);
        else
            awareness->sub_7100D7EAE4(0);

        _4c = awareness->sub_7100D7EC34(1);
        if (*mHearingRatio_s > 0.0f)
            awareness->sub_7100D7EC14(1, *mHearingRatio_s);
        else
            awareness->sub_7100D7EAE4(1);
    }
    changeChild("待機");
}

void EnemyHideGrass::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        setFinished();
    else
        child->isChangeable();
}

void EnemyHideGrass::leave_() {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;

    if (_48 > 0.0f) {
        awareness->sub_7100D7E9BC(0);
        awareness->sub_7100D7EC14(0, _48);
    } else {
        awareness->sub_7100D7EAE4(0);
    }

    if (_4c > 0.0f) {
        awareness->sub_7100D7E9BC(1);
        awareness->sub_7100D7EC14(1, _4c);
    } else {
        awareness->sub_7100D7EAE4(1);
    }
}

void EnemyHideGrass::loadParams_() {
    getStaticParam(&mSightRatio_s, "SightRatio");
    getStaticParam(&mHearingRatio_s, "HearingRatio");
}

}  // namespace uking::ai
