#include "Game/AI/Behavior/behaviorCurseGanonBGMApplyLPF.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

CurseGanonBGMApplyLPF::CurseGanonBGMApplyLPF(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CurseGanonBGMApplyLPF::~CurseGanonBGMApplyLPF() = default;

bool CurseGanonBGMApplyLPF::m6(sead::Heap* heap) {
    return true;
}

void CurseGanonBGMApplyLPF::loadParams() {
    getStaticParam(&mLPF_s, "LPF");
}

void CurseGanonBGMApplyLPF::m7() {
    if (_30)
        return;
    _30 = sub_7100FFE5EC();
    if (_30)
        _30->sub_7101000838(*mLPF_s);
}

void CurseGanonBGMApplyLPF::m8() {
    _30 = nullptr;
}

void CurseGanonBGMApplyLPF::m9() {
    _30 = nullptr;
}

}  // namespace uking::behavior
