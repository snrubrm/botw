#include "Game/AI/Action/actionHorseReinsBindAction.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseObject.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseReinsBindAction::HorseReinsBindAction(const InitArg& arg) : HorseReinsDefaultAction(arg) {}

HorseReinsBindAction::~HorseReinsBindAction() = default;

bool HorseReinsBindAction::init_(sead::Heap* heap) {
    return HorseReinsDefaultAction::init_(heap);
}

void HorseReinsBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        auto* horse = sead::DynamicCast<ksys::act::Actor>(mHorse_d->getProc(nullptr, nullptr));
        if (sead::DynamicCast<act::HorseBase>(horse)) {
            auto* rider = sead::DynamicCast<ksys::act::Actor>(mRider_d->getProc(nullptr, nullptr));
            reins->_850.acquire(rider, false);
            reins->sub_7100E7BC10(horse);
            reins->_868.change(1, *mIsLeftBind_d);
            reins->_868.change(2, *mIsRightBind_d);
            if (!static_cast<act::HorseBase*>(horse)->_870.hasProc())
                static_cast<act::HorseBase*>(horse)->_b70 |= 0x20;
        }
    }
    HorseReinsDefaultAction::enter_(params);
}

void HorseReinsBindAction::leave_() {
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        reins->_850.acquire(nullptr, false);
        auto* horse = sead::DynamicCast<act::HorseBase>(reins->sub_7100E7BA64());
        if (!horse || !horse->sub_7100E6AF2C(reins))
            reins->sub_7100E7BC10(nullptr);
    }
    HorseReinsDefaultAction::leave_();
}

void HorseReinsBindAction::loadParams_() {
    HorseReinsDefaultAction::loadParams_();
    getDynamicParam(&mIsLeftBind_d, "IsLeftBind");
    getDynamicParam(&mIsRightBind_d, "IsRightBind");
    getDynamicParam(&mRider_d, "Rider");
    getDynamicParam(&mHorse_d, "Horse");
}

void HorseReinsBindAction::calc_() {
    HorseReinsDefaultAction::calc_();
}

}  // namespace uking::action
