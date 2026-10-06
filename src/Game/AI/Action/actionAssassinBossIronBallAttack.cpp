#include "Game/AI/Action/actionAssassinBossIronBallAttack.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AssassinBossIronBallAttack::AssassinBossIronBallAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AssassinBossIronBallAttack::~AssassinBossIronBallAttack() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        sead::FixedSafeString<32> key;
        for (s32 i = 0; i < *mIronBallNum_s; ++i) {
            key.format("%s%d", mIronBallPartsName_s.cstr(), i);
            enemy->sub_7100D3CFEC(key);
        }
    }
    _40.freeBuffer();
    _50.freeBuffer();
}

bool AssassinBossIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AssassinBossIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _60 = 0;
    _50.fill(false);
}

void AssassinBossIronBallAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void AssassinBossIronBallAttack::loadParams_() {
    getStaticParam(&mIronBallNum_s, "IronBallNum");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIronBallPartsName_s, "IronBallPartsName");
}

void AssassinBossIronBallAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

void AssassinBossIronBallAttack::m32(sead::Vector3f* out) {
    *out = sead::Vector3f::zero;
}

void AssassinBossIronBallAttack::m33(sead::Vector3f* out) {
    mActor->getMtx().getTranslation(*out);
}

}  // namespace uking::action
