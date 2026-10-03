#include "Game/AI/Action/actionCapturedActFreeze.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

CapturedActFreeze::CapturedActFreeze(const InitArg& arg) : Freeze(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
CapturedActFreeze::~CapturedActFreeze() {
    ;
}

bool CapturedActFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void CapturedActFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
    if (!mASKeyName_s.isEmpty())
        playAS(mASKeyName_s.cstr(), true, 0, 0, -1.0f);
    for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
        mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (*mPauseDelayFrames_s < 0)
        _90.reset(1.0f, 0.0f);
    else
        _90.reset(*mPauseDelayFrames_s);
}

void CapturedActFreeze::leave_() {
    for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
        mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    Freeze::leave_();
}

void CapturedActFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mPauseDelayFrames_s, "PauseDelayFrames");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void CapturedActFreeze::calc_() {
    _90.update();
    if (_90.value <= sead::Mathf::epsilon()) {
        for (int i = 0; i < mActor->getASList()->getSlot0BankCount(); ++i)
            mActor->getASList()->x_3(0, i, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
        _90.reset(1.0f, 0.0f);
    }
    Freeze::calc_();
}

}  // namespace uking::action
