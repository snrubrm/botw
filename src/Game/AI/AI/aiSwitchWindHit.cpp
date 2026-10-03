#include "Game/AI/AI/aiSwitchWindHit.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SwitchWindHit::SwitchWindHit(const InitArg& arg) : SwitchAI(arg) {}

SwitchWindHit::~SwitchWindHit() = default;

bool SwitchWindHit::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchWindHit::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
    _46 = false;
    _44 = false;
    _45 = false;
    _40 = *mWaitTime_s;
}

void SwitchWindHit::leave_() {
    SwitchAI::leave_();
}

void SwitchWindHit::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

bool SwitchWindHit::handleMessage_(const ksys::Message& message) {
    if (!isCurrentChild("オフ待機") && message.getType() == 0x8000080) {
        _46 = true;
        return true;
    }
    return false;
}

void SwitchWindHit::calc_() {
    _44 = false;
    _45 = false;
    auto* actor = mActor;
    _44 = ksys::VFR::chase(&_40, *mWaitTime_s);
    if (auto* chemical = actor->getChemicalStuff())
        _45 = chemical->_bc >> 13 & 1;
    SwitchAI::calc_();
}

bool SwitchWindHit::m35() {
    if (!_45 || !_44)
        return false;
    auto* actor = mActor;
    return actor->checkBasicSig() && !actor->checkLinkBasicSig();
}

bool SwitchWindHit::m36() {
    if (!_45 || !_44)
        return false;
    auto* actor = mActor;
    return !actor->checkBasicSig() || actor->checkLinkBasicSig();
}

bool SwitchWindHit::m37() {
    auto* child = getCurrentChild();
    return isCurrentChild("オン") && child->isChangeable();
}

bool SwitchWindHit::m38() {
    auto* child = getCurrentChild();
    if (isCurrentChild("オフ") && child->isChangeable())
        return true;
    return _46;
}

void SwitchWindHit::m40() {
    _46 = false;
    _40 = 0;
    changeChild("オフ待機");
}

void SwitchWindHit::m41() {
    _40 = 0;
    changeChild("オン待機");
}

void SwitchWindHit::m42() {
    changeChild("オフ");
}

void SwitchWindHit::m43() {
    changeChild("オン");
}

}  // namespace uking::ai
