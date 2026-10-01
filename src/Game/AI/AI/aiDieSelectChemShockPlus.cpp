#include "Game/AI/AI/aiDieSelectChemShockPlus.h"

namespace uking::ai {

DieSelectChemShockPlus::DieSelectChemShockPlus(const InitArg& arg) : DieSelectChemicalPlus(arg) {}

DieSelectChemShockPlus::~DieSelectChemShockPlus() = default;

bool DieSelectChemShockPlus::init_(sead::Heap* heap) {
    return DieSelectChemicalPlus::init_(heap);
}

void DieSelectChemShockPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelectChemicalPlus::enter_(params);
}

void DieSelectChemShockPlus::calc_() {
    DieSelectChemicalPlus::calc_();
}

void DieSelectChemShockPlus::leave_() {
    DieSelectChemicalPlus::leave_();
}

void DieSelectChemShockPlus::loadParams_() {
    DieSelectChemicalPlus::loadParams_();
}

void DieSelectChemShockPlus::m34(s32 a2, s32 a3, bool a4, bool a5) {
    if (a3 >= 6 && a3 <= 8) {
        changeChild("ショック死");
        return;
    }
    DieSelectChemicalPlus::m34(a2, a3, a4, a5);
}

}  // namespace uking::ai
