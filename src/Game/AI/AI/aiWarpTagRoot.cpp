#include "Game/AI/AI/aiWarpTagRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

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
    _38.value = 0;
    _38.prev_value = 0;
    _78 = false;
    _79 = false;
    _68 = ksys::world::Manager::instance()->getPlayerPos();
    mActor->m107();
}

void WarpTagRoot::leave_() {
    _48.fadeXLink();
}

void WarpTagRoot::loadParams_() {}

}  // namespace uking::ai
