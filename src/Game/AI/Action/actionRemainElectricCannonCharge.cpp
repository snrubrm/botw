#include "Game/AI/Action/actionRemainElectricCannonCharge.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

RemainElectricCannonCharge::RemainElectricCannonCharge(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonCharge::~RemainElectricCannonCharge() = default;

bool RemainElectricCannonCharge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = 0;
    _30 = ksys::eft::searchAndEmitELink(mActor, "ChargeCore");
    _30.setPosition(mActor->getMtx().getTranslation(), 0.0f);
    if (auto* gdm = ksys::gdt::Manager::instance())
        ksys::gdt::getBoolByNameBypassPerm(gdm, &_40, "IsPlayed_Demo709_0");
    if (!_40) {
        _48.initWithName(mActor, "Demo709_0", "Demo709_0");
        _48.loadEvent();
    }
    mFlags.set(Flag::Changeable);
}

void RemainElectricCannonCharge::leave_() {
    _30.fade();
    if (_48.mEventFlow)
        _48.unloadEvent();
}

void RemainElectricCannonCharge::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
}

void RemainElectricCannonCharge::calc_() {
    ksys::Timer::update(&_28, 1.0f);
    _30.setPosition(mActor->getMtx().getTranslation(), _28 / *mChargeTime_s);
    if (_28 >= *mChargeTime_s)
        setFinished();
    if (!_40) {
        _48.sendMessageToEventMgrActor(mActor);
        _40 = true;
    }
}

}  // namespace uking::action
