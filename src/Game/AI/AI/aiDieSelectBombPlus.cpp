#include "Game/AI/AI/aiDieSelectBombPlus.h"

namespace uking::ai {

DieSelectBombPlus::DieSelectBombPlus(const InitArg& arg) : DieSelect(arg) {}

DieSelectBombPlus::~DieSelectBombPlus() = default;

bool DieSelectBombPlus::init_(sead::Heap* heap) {
    return DieSelect::init_(heap);
}

void DieSelectBombPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelect::enter_(params);
}

void DieSelectBombPlus::calc_() {
    DieSelect::calc_();
}

void DieSelectBombPlus::leave_() {
    DieSelect::leave_();
}

void DieSelectBombPlus::loadParams_() {
    DieSelect::loadParams_();
}

void DieSelectBombPlus::m34(s32 a2, s32 a3, bool a4, bool a5) {
    if (a2 == 4) {
        changeChild("爆死");
        return;
    }
    DieSelect::m34(a2, a3, a4, a5);
}

}  // namespace uking::ai
