#include "Game/AI/AI/aiSwitchRightAndWrong.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

SwitchRightAndWrong::SwitchRightAndWrong(const InitArg& arg) : SwitchAI(arg) {}

SwitchRightAndWrong::~SwitchRightAndWrong() = default;

bool SwitchRightAndWrong::init_(sead::Heap* heap) {
    return SwitchAI::init_(heap);
}

void SwitchRightAndWrong::enter_(ksys::act::ai::InlineParamPack* params) {
    SwitchAI::enter_(params);
    _44 = false;
    _45 = false;
    _46 = false;
    _47 = true;
    _40 = *mWaitTime_s;
    mActor->emitBasicSigOn();
}

void SwitchRightAndWrong::leave_() {
    SwitchAI::leave_();
}

void SwitchRightAndWrong::loadParams_() {
    SwitchAI::loadParams_();
    getStaticParam(&mWaitTime_s, "WaitTime");
}

// NON_MATCHING: *mWaitTime_s is loaded before the VFR delta instead of after (see lane2 log, Borderline)
void SwitchRightAndWrong::calc_() {
    _44 = false;
    _44 = sead::Mathf::chase(&_40, *mWaitTime_s, ksys::VFR::instance()->getDeltaFrame());
    SwitchAI::calc_();
}

bool SwitchRightAndWrong::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x800007f)
        _45 = true;

    if (message.getType().value == 0x8000080 && !isCurrentChild("オフ待機")) {
        _46 = true;
        return true;
    }
    return false;
}

bool SwitchRightAndWrong::m34() {
    auto* actor = mActor;
    return actor->checkBasicSig() && actor->checkLinkBasicSig();
}

bool SwitchRightAndWrong::m44() {
    if (!_47)
        return false;
    return _44 && _45;
}

bool SwitchRightAndWrong::m35() {
    if (_47)
        return false;
    return _44 && _45;
}

bool SwitchRightAndWrong::m36() {
    return _44 && _46;
}

bool SwitchRightAndWrong::m37() {
    auto* child = getCurrentChild();
    return (isCurrentChild("オン") || isCurrentChild("初回オン")) && child->isFinished();
}

bool SwitchRightAndWrong::m38() {
    auto* child = getCurrentChild();
    return isCurrentChild("オフ") && child->isFinished();
}

void SwitchRightAndWrong::m39() {
    if (m44())
        m45();
}

void SwitchRightAndWrong::m40() {
    _46 = false;
    _47 = true;
    _40 = 0;
    changeChild("オフ待機");
}

void SwitchRightAndWrong::m41() {
    _45 = false;
    _40 = 0;
    changeChild("オン待機");
}

void SwitchRightAndWrong::m42() {
    _46 = false;
    changeChild("オフ");
}

void SwitchRightAndWrong::m43() {
    _45 = false;
    changeChild("オン");
}

void SwitchRightAndWrong::m45() {
    _45 = false;
    _47 = false;
    changeChild("初回オン");
}

}  // namespace uking::ai
