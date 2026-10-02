#include "Game/AI/AI/aiSandfallWithSound.h"

namespace uking::ai {

SandfallWithSound::SandfallWithSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandfallWithSound::~SandfallWithSound() = default;

bool SandfallWithSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandfallWithSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandfallWithSound::calc_() {
    sub_7100556370();
    sub_710055646C();
}

void SandfallWithSound::leave_() {
    sub_71005565D8();
}

void SandfallWithSound::loadParams_() {}

}  // namespace uking::ai
