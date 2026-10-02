#include "Game/AI/Behavior/behaviorSetChemicalPower.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::behavior {

SetChemicalPower::SetChemicalPower(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetChemicalPower::~SetChemicalPower() = default;

bool SetChemicalPower::m6(sead::Heap* heap) {
    return true;
}

void SetChemicalPower::m7() {}

void SetChemicalPower::m8() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (*mIsOnOffensive_s)
            chemical->sub_7100D91098(true);
        m14(*mIsSetOn_s);
    }
}

void SetChemicalPower::m9() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (*mIsOnOffensive_s)
            chemical->sub_7100D91098(false);
        m14(!*mIsSetOn_s);
    }
}

void SetChemicalPower::loadParams() {
    getStaticParam(&mIsSetOn_s, "IsSetOn");
    getStaticParam(&mIsOnOffensive_s, "IsOnOffensive");
}

}  // namespace uking::behavior
