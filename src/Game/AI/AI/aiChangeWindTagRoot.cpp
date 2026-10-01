#include "Game/AI/AI/aiChangeWindTagRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

ChangeWindTagRoot::ChangeWindTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChangeWindTagRoot::~ChangeWindTagRoot() = default;

bool ChangeWindTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChangeWindTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->m107();
}

// NON_MATCHING: instruction order (original loads the params before the world::Manager instance)
void ChangeWindTagRoot::calc_() {
    if (mActor->checkBasicSig()) {
        mActor->m107();
        ksys::world::Manager::instance()->changeWind(*mDirection_m, true, *mWindSpeed_m);
    } else {
        ksys::world::Manager::instance()->resetManualWind();
    }
}

void ChangeWindTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChangeWindTagRoot::loadParams_() {
    getMapUnitParam(&mDirection_m, "Direction");
    getMapUnitParam(&mWindSpeed_m, "WindSpeed");
}

}  // namespace uking::ai
