#include "Game/AI/AI/aiKeeseHangOnCeil.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KeeseHangOnCeil::KeeseHangOnCeil(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeeseHangOnCeil::~KeeseHangOnCeil() = default;

bool KeeseHangOnCeil::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KeeseHangOnCeil::enter_(ksys::act::ai::InlineParamPack* params) {
    _90.x();
    changeChild("張り付き");
}

bool KeeseHangOnCeil::isChangeable() const {
    return false;
}

void KeeseHangOnCeil::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7E9BC(1);
        awareness->sub_7100D7E9BC(0);
    }
}

void KeeseHangOnCeil::loadParams_() {}

bool KeeseHangOnCeil::handleMessage_(const ksys::Message* message) {
    if (_90._30 || !_90.m2(*message))
        return false;
    _108 = sead::GlobalRandom::instance()->getF32() * 8.0f;
    return true;
}

}  // namespace uking::ai
