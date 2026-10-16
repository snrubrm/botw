#include "Game/Actor/Action/actionLastBossStun.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

LastBossStun::LastBossStun(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossStun::~LastBossStun() = default;

bool LastBossStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling around the flag updates and an inverted csel for the down time.
void LastBossStun::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* boss = sead::DynamicCast<act::LastBoss>(mActor);
    if (!boss) {
        setFailed();
        return;
    }

    if (boss->_14f8._30.isOnBit(10)) {
        boss->_14f8._30.resetBit(10);
        xlinkSearchAndEmit(mActor, "BlownWithPile", 1, nullptr);
    }

    if (!mActor->getCharacterController())
        return;

    _39 = false;
    _3a = false;
    sub_710073FA90(&_60, mActor);
    if (boss->_14e8.isOnBit(2))
        boss->_14e8.resetBit(2);
    boss->_14e8.resetBit(18);
    boss->_14e8.setBit(3);
    const u32 stun_type = boss->_14e4;
    boss->_14f8._30.resetBit(0);
    boss->_14f8._30.setBit(4);

    f32 time;
    if (stun_type == 1) {
        time = *mStunTime_s;
        _38 = true;
        playAS("Damage_Big_Up", false, 0, 0, -1.0f);
    } else {
        _38 = false;
        if (auto* life = mActor->getLife(); life && *life == 0) {
            setFinished();
            return;
        }
        const f32* const* base_time = &mStunTime_s;
        playAS("Down_Start", false, 0, 0, -1.0f);
        _48 = sead::Vector3f::ey;
        if (!boss->_14f8._30.isOnBit(9))
            base_time = &mShockWaveDownTime_s;
        time = **base_time;
        _3a = true;
    }

    time += getNumberOfClearedRemains() * *mAddStunTime_s;
    _3c = ksys::Timer(time, time);

    if (!boss->_14e8.isOnBit(1)) {
        playAS("DownWaitMaterial", false, 1, 0, -1.0f);
    } else {
        boss->_14e8.setBit(10);
        if (boss->_14e8.isOnBit(2))
            boss->_14e8.resetBit(2);
        boss->_14f8._30.resetBit(0);
        boss->update();
    }

    _3b = false;
    boss->_14f8._30.resetBit(8);
    boss->_14f8._30.resetBit(9);
}

void LastBossStun::leave_() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->_14e8.resetBit(3);
        boss->stunEnd();
    }
}

void LastBossStun::loadParams_() {
    getStaticParam(&mStunTime_s, "StunTime");
    getStaticParam(&mAddStunTime_s, "AddStunTime");
    getStaticParam(&mShockWaveDownTime_s, "ShockWaveDownTime");
}

void LastBossStun::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
