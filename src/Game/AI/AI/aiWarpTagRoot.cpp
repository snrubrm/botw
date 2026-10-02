#include "Game/AI/AI/aiWarpTagRoot.h"

namespace uking::ai {

// NON_MATCHING: store order only (the original writes _38 after the _68 / _78 stores)
WarpTagRoot::WarpTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg), _48() {
    _38.value = 0;
    _38.prev_value = 0;
}

WarpTagRoot::~WarpTagRoot() = default;

bool WarpTagRoot::init_(sead::Heap* heap) {
    _78 = false;
    return true;
}

void WarpTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WarpTagRoot::leave_() {
    _48.fadeXLink();
}

void WarpTagRoot::loadParams_() {}

}  // namespace uking::ai
