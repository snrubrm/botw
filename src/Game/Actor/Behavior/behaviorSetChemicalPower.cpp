#include "Game/Actor/Behavior/behaviorSetChemicalPower.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::behavior {

SetChemicalPower::SetChemicalPower(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetChemicalPower::~SetChemicalPower() = default;

bool SetChemicalPower::init_(sead::Heap* heap) {
    return true;
}

void SetChemicalPower::calc() {}

void SetChemicalPower::enter() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (*mIsOnOffensive_s)
            chemical->sub_7100D91098(true);
        m14(*mIsSetOn_s);
    }
}

void SetChemicalPower::leave() {
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
