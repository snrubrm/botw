#include "Game/Actor/Behavior/behaviorCurseGanonBGMApplyLPF.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking::behavior {

CurseGanonBGMApplyLPF::CurseGanonBGMApplyLPF(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CurseGanonBGMApplyLPF::~CurseGanonBGMApplyLPF() = default;

bool CurseGanonBGMApplyLPF::init_(sead::Heap* heap) {
    return true;
}

void CurseGanonBGMApplyLPF::loadParams() {
    getStaticParam(&mLPF_s, "LPF");
}

void CurseGanonBGMApplyLPF::calc() {
    if (_30)
        return;
    _30 = sub_7100FFE5EC();
    if (_30)
        _30->sub_7101000838(*mLPF_s);
}

void CurseGanonBGMApplyLPF::enter() {
    _30 = nullptr;
}

void CurseGanonBGMApplyLPF::leave() {
    _30 = nullptr;
}

}  // namespace uking::behavior
