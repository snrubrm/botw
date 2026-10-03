#include "Game/AI/AI/aiSandfallWithSound.h"

namespace uking::ai {

SandfallWithSound::SandfallWithSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandfallWithSound::~SandfallWithSound() {
    if (_38) {
        _38->destroy();
        _38 = nullptr;
    }
}

bool SandfallWithSound::init_(sead::Heap* heap) {
    _38 = aal::ShapeSegment::create("Sandfall", heap);
    if (_38) {
        _38->mFlags.resetBit(aal::Shape::KeepPosition);
        _38->mFlags.resetBit(aal::Shape::KeepRotation);
        sub_7100556370();
    }
    return true;
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
