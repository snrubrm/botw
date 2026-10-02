#include "Game/AI/AI/aiKorokStartStandRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KorokStartStandRoot::KorokStartStandRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokStartStandRoot::~KorokStartStandRoot() = default;

bool KorokStartStandRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokStartStandRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
}

void KorokStartStandRoot::calc_() {
    if (!mActor->checkBasicSig()) {
        _38 = false;
        return;
    }
    if (_38)
        return;
    xlinkSearchAndEmit(mActor, "Start", 2, &_40);
    _38 = true;
}

void KorokStartStandRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokStartStandRoot::loadParams_() {}

}  // namespace uking::ai
