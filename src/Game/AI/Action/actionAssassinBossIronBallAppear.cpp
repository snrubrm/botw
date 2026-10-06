#include "Game/AI/Action/actionAssassinBossIronBallAppear.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AssassinBossIronBallAppear::AssassinBossIronBallAppear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AssassinBossIronBallAppear::~AssassinBossIronBallAppear() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mIronBallNum_s; ++i) {
            key.format("%s%d", mIronBallPartsName_s.cstr(), i);
            enemy->sub_7100D3CFEC(key);
        }
    }
    _60.freeBuffer();
    _70.freeBuffer();
}

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
