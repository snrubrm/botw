#include "Game/AI/AI/aiMiniGolemSleep.h"

namespace uking::ai {

MiniGolemSleep::MiniGolemSleep(const InitArg& arg) : SpecialEnemySleep(arg) {}

MiniGolemSleep::~MiniGolemSleep() = default;

bool MiniGolemSleep::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void MiniGolemSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
}

void MiniGolemSleep::calc_() {
    SpecialEnemySleep::calc_();
}

void MiniGolemSleep::leave_() {
    SpecialEnemySleep::leave_();
}

void MiniGolemSleep::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

bool MiniGolemSleep::handleMessage_(const ksys::Message& message) {
    return _68.m2(message);
}

bool MiniGolemSleep::m36() {
    return _68._30;
}

}  // namespace uking::ai
