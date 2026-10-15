#include "Game/Actor/Action/actionAssassinBossIronBallAppear.h"
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

// NON_MATCHING: final sender-loop registers and increment scheduling differ.
bool AssassinBossIronBallAppear::init_(sead::Heap* heap) {
    _60.tryAllocBuffer(*mIronBallNum_s, heap);
    if (!_60.isBufferReady())
        return false;
    _70.tryAllocBuffer(*mIronBallNum_s, heap);
    if (!_70.isBufferReady())
        return false;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mIronBallNum_s; ++i) {
            key.format("%s%d", mIronBallPartsName_s.cstr(), i);
            enemy->sub_7100D3CED8(key, heap);
        }
    }
    for (s32 i = 0; i < *mIronBallNum_s; ++i)
        _60[i]._8 = &mActor->getMessageTransceiver();
    return true;
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
