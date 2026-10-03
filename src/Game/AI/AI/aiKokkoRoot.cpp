#include "Game/AI/AI/aiKokkoRoot.h"

namespace uking::ai {

KokkoRoot::KokkoRoot(const InitArg& arg) : PreyRoot(arg) {}

KokkoRoot::~KokkoRoot() = default;

bool KokkoRoot::init_(sead::Heap* heap) {
    return PreyRoot::init_(heap);
}

void KokkoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyRoot::enter_(params);
    _220 = 0;
    _228.reset();
    _238 = ksys::Timer(-1, -1, 0);
    _248._28 = mAvoidCountActorName_s;
    setDamageCallbackTiming(mActor, 0, &_248);
}

void KokkoRoot::leave_() {
    sub_71005DA114(mActor, &_248);
    PreyRoot::leave_();
}

void KokkoRoot::loadParams_() {
    PreyRoot::loadParams_();
    getStaticParam(&mStartSpecialAttackCount_s, "StartSpecialAttackCount");
    getStaticParam(&mAvoidCountActorName_s, "AvoidCountActorName");
}

void KokkoRoot::m40() {
    if (!isCurrentChild("怒り"))
        PreyRoot::m40();
}

void KokkoRoot::m41() {
    if (!isCurrentChild("怒り"))
        PreyRoot::m41();
}

}  // namespace uking::ai
