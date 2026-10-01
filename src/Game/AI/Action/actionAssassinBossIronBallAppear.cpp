#include "Game/AI/Action/actionAssassinBossIronBallAppear.h"

namespace uking::action {

AssassinBossIronBallAppear::AssassinBossIronBallAppear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AssassinBossIronBallAppear::~AssassinBossIronBallAppear() = default;

bool AssassinBossIronBallAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AssassinBossIronBallAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    _70.fill(false);
    _80 = 0;
    mFlags.set(Flag::Changeable);
}

void AssassinBossIronBallAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void AssassinBossIronBallAppear::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mCreateDist_s, "CreateDist");
    getStaticParam(&mBackDist_s, "BackDist");
    getStaticParam(&mTopOffsetY_s, "TopOffsetY");
    getStaticParam(&mBaseOffsetY_s, "BaseOffsetY");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
    getStaticParam(&mUDLimit_s, "UDLimit");
}

void AssassinBossIronBallAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

void AssassinBossIronBallAppear::m32() {}

}  // namespace uking::action
