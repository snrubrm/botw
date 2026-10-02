#include "Game/AI/AI/aiWarpSafeTagRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WarpSafeTagRoot::WarpSafeTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg), _48() {
    _38.value = 0;
    _38.prev_value = 0;
}

WarpSafeTagRoot::~WarpSafeTagRoot() = default;

bool WarpSafeTagRoot::init_(sead::Heap* heap) {
    _68 = false;
    return true;
}

void WarpSafeTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38.value = 0;
    _38.prev_value = 0;
    _68 = false;
    _69 = false;
    _6a = false;
    mActor->m107();
}

void WarpSafeTagRoot::leave_() {
    _48.fadeXLink();
}

void WarpSafeTagRoot::loadParams_() {}

}  // namespace uking::ai
