#include "Game/AI/Action/actionCapturedActElectricParalyisis.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

CapturedActElectricParalyisis::CapturedActElectricParalyisis(const InitArg& arg)
    : ElectricParalysis(arg) {}

CapturedActElectricParalyisis::~CapturedActElectricParalyisis() = default;

bool CapturedActElectricParalyisis::init_(sead::Heap* heap) {
    return ElectricParalysis::init_(heap);
}

void CapturedActElectricParalyisis::enter_(ksys::act::ai::InlineParamPack* params) {
    ElectricParalysis::enter_(params);
    if (*mPauseDelayFrames_s < 0.0f)
        _48.reset(1.0f, 0.0f);
    else
        _48.reset(*mPauseDelayFrames_s);
}

void CapturedActElectricParalyisis::leave_() {
    for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
        mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    ElectricParalysis::leave_();
}

void CapturedActElectricParalyisis::loadParams_() {
    ElectricParalysis::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
}

void CapturedActElectricParalyisis::calc_() {
    _48.update();
    if (_48.value <= sead::Mathf::epsilon()) {
        for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
            mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
        _48.reset(1.0f, 0.0f);
    }
    ElectricParalysis::calc_();
}

}  // namespace uking::action
