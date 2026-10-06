#include "Game/AI/AI/aiHorseEscapeRouteRailAI.h"

namespace uking::ai {

HorseEscapeRouteRailAI::HorseEscapeRouteRailAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store (a SafeString lives in the embedded Unk_71024f15f8).
HorseEscapeRouteRailAI::~HorseEscapeRouteRailAI() {
    ;
}

bool HorseEscapeRouteRailAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseEscapeRouteRailAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseEscapeRouteRailAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the original loads the `UpdatePosDistance` argument before the object / vtable of the call (C++14 evaluation order)
void HorseEscapeRouteRailAI::calc_() {
    auto* child = getCurrentChild();
    child->getName();
    if (child->isFailed()) {
        setFailed();
        return;
    }
    if (child->isFinished()) {
        ++_c0;
        if (_c0 >= *mCount_s) {
            setFinished();
            return;
        }
        _50.x(*mUpdatePosDistance_s);
        // called through a pointer in the original (not devirtualised)
        (&_50)->m4(*mUpdatePosDistance_s, nullptr, nullptr);
        sub_7100E5BE9C(false);
    }
}

void HorseEscapeRouteRailAI::loadParams_() {
    getStaticParam(&mCount_s, "Count");
    getStaticParam(&mUpdatePosDistance_s, "UpdatePosDistance");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
