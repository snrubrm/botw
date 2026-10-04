#include "Game/AI/Action/actionHorseSaddleBindAction.h"
#include "Game/AI/aiUnk_7101ec1800.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseObject.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseObject.h"

namespace uking::action {

HorseSaddleBindAction::HorseSaddleBindAction(const InitArg& arg) : HorseSaddleDefaultAction(arg) {}

HorseSaddleBindAction::~HorseSaddleBindAction() = default;

bool HorseSaddleBindAction::init_(sead::Heap* heap) {
    return HorseSaddleDefaultAction::init_(heap);
}

void HorseSaddleBindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        auto* horse = sead::DynamicCast<ksys::act::Actor>(mHorse_d->getProc(nullptr, nullptr));
        if (sead::DynamicCast<act::HorseBase>(horse)) {
            auto* rider = sead::DynamicCast<ksys::act::Actor>(mRider_d->getProc(nullptr, nullptr));
            reins->_850.acquire(rider, false);
            reins->sub_7100E7BC10(horse);
            reins->_868.change(1, *mIsLeftBind_d);
            reins->_868.change(2, *mIsRightBind_d);
            auto* horse_base = static_cast<act::HorseBase*>(horse);
            if (!horse_base->_880.hasProc()) {
                if (mActor->getParam()->getRes().mGParamList->getHorseObject()->mIsHorseClothDisable.ref())
                    horse_base->_b70.setBitOn(4);
                horse_base->_b70.setBitOn(5);
            }
        }
    }
    HorseSaddleDefaultAction::enter_(params);
}

void HorseSaddleBindAction::leave_() {
    if (auto* reins = sead::DynamicCast<act::HorseReins>(mActor)) {
        reins->_850.acquire(nullptr, false);
        auto* horse = sead::DynamicCast<act::HorseBase>(reins->sub_7100E7BA64());
        if (!horse || !horse->sub_7100E6B068(reins))
            reins->sub_7100E7BC10(nullptr);
    }
    HorseSaddleDefaultAction::leave_();
}

void HorseSaddleBindAction::loadParams_() {
    HorseSaddleDefaultAction::loadParams_();
    getDynamicParam(&mIsLeftBind_d, "IsLeftBind");
    getDynamicParam(&mIsRightBind_d, "IsRightBind");
    getDynamicParam(&mIsZelda_d, "IsZelda");
    getDynamicParam(&mRider_d, "Rider");
    getDynamicParam(&mHorse_d, "Horse");
}

void HorseSaddleBindAction::calc_() {
    HorseSaddleDefaultAction::calc_();
}

const sead::Vector3f* HorseSaddleBindAction::m32() {
    return !*mIsZelda_d ? &sUnk_7101ec1818 : &sUnk_7101ec1800;
}

const sead::Vector3f* HorseSaddleBindAction::m33() {
    return !*mIsZelda_d ? &sUnk_7101ec1824 : &sUnk_7101ec180c;
}

}  // namespace uking::action
