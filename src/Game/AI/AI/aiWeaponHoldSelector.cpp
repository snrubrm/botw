#include "Game/AI/AI/aiWeaponHoldSelector.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::ai {

WeaponHoldSelector::WeaponHoldSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponHoldSelector::~WeaponHoldSelector() = default;

bool WeaponHoldSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponHoldSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* weapons = mActor->getWeapons();
    changeChild(weapons && weapons->mWeapons[*mWeaponIdx_s]._10 ? "納刀" : "抜刀", params);
}

void WeaponHoldSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        auto* weapons = mActor->getWeapons();
        if (weapons && weapons->mWeapons[*mWeaponIdx_s]._10) {
            if (isCurrentChild("納刀")) {
                if (child->isFinished())
                    setFinished();
                else
                    setFailed();
            } else {
                changeChild("納刀");
            }
        } else {
            if (isCurrentChild("抜刀")) {
                if (child->isFinished())
                    setFinished();
                else
                    setFailed();
            } else {
                changeChild("抜刀");
            }
        }
    } else if (child->isChangeable()) {
        auto* weapons = mActor->getWeapons();
        if (weapons && weapons->mWeapons[*mWeaponIdx_s]._10) {
            if (!isCurrentChild("納刀"))
                changeChild("納刀");
        } else {
            if (!isCurrentChild("抜刀"))
                changeChild("抜刀");
        }
    }
}

void WeaponHoldSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponHoldSelector::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

}  // namespace uking::ai
