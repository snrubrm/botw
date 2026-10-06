#include "Game/AI/AI/aiWaterFallWithSound.h"

namespace uking::ai {

WaterFallWithSound::WaterFallWithSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaterFallWithSound::~WaterFallWithSound() {
    if (_38) {
        _38->destroy();
        _38 = nullptr;
    }
}

bool WaterFallWithSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaterFallWithSound::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005EBEC0();
}

void WaterFallWithSound::leave_() {
    sub_71005EC090();
}

void WaterFallWithSound::loadParams_() {}

}  // namespace uking::ai
