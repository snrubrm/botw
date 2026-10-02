#include "Game/AI/AI/aiSiteBossLswordTornadoRoot.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossLswordTornadoRoot::SiteBossLswordTornadoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossLswordTornadoRoot::~SiteBossLswordTornadoRoot() = default;

bool SiteBossLswordTornadoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossLswordTornadoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
        boss->_1558.reset(0x40000);
    sub_710057DD54();
}

void SiteBossLswordTornadoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossLswordTornadoRoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mDestPos_d, "DestPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
