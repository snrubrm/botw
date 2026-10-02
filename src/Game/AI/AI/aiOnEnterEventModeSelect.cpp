#include "Game/AI/AI/aiOnEnterEventModeSelect.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"

namespace uking::ai {

OnEnterEventModeSelect::OnEnterEventModeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnEnterEventModeSelect::~OnEnterEventModeSelect() = default;

bool OnEnterEventModeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnEnterEventModeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::evt::sub_7100DC866C())
        changeChild("デモ中", params);
    else
        changeChild("非デモ中", params);
}

void OnEnterEventModeSelect::calc_() {}

void OnEnterEventModeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnEnterEventModeSelect::loadParams_() {}

}  // namespace uking::ai
