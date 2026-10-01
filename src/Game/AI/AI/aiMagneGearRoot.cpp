#include "Game/AI/AI/aiMagneGearRoot.h"

namespace uking::ai {

MagneGearRoot::MagneGearRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneGearRoot::~MagneGearRoot() = default;

bool MagneGearRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MagneGearRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = 0;
    changeChild("通常");
}

void MagneGearRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneGearRoot::loadParams_() {}

}  // namespace uking::ai
