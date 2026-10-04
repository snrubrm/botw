#include "Game/AI/AI/aiHorseMoveToPlayer.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

HorseMoveToPlayer::HorseMoveToPlayer(const InitArg& arg) : HorseFollow(arg) {}

HorseMoveToPlayer::~HorseMoveToPlayer() = default;

bool HorseMoveToPlayer::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

// NON_MATCHING: only the accessor address for its destructor (the original rematerialises `sp + 0x18` at the
// destructor call; ours keeps it in x22 from the end of the nav block)
void HorseMoveToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _f0.makeAllZero();
    HorseFollow::enter_(params);

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    if (auto* loader = ksys::phys::HavokAI::instance()->_48) {
        if (loader->x_1(&pos)) {
            loader->sub_7100F8B334(&pos);
            _f0.setBit(Flag(Flag::_0));
        }
    }

    if (auto* nav = mActor->m45()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(mTargetActor_d, &accessor)) {
            sead::Vector3f target;
            accessor.getActorMtx().getTranslation(target);
            nav->_2d4 = 100.0f;
            nav->_220 |= 0x4000000;
            nav->_220 |= 0x8000000;
            nav->sub_7100F7606C(3000);
            nav->sub_7100F7604C(0.0f);
            nav->inlineReset();
            nav->sub_7100F75F8C(target);
        } else {
            setFailed();
        }
    } else {
        setFailed();
    }

    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
        horse->_b70 |= 1;
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->_134 = 0;
    changeChild("うろうろする", nullptr);
}

void HorseMoveToPlayer::leave_() {
    HorseFollow::leave_();

    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
        horse->_b70 &= ~1u;
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->_134 = 0;
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F7606C(0);
        nav->_220 &= ~0x4000000u;
        nav->_220 &= ~0x8000000u;
        nav->_2d4 = 0;
    }

    if (_f0.isOnBit(Flag(Flag::_0))) {
        if (auto* loader = ksys::phys::HavokAI::instance()->_48)
            loader->x_2();
    }
}

void HorseMoveToPlayer::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mDistanceSuccessEndIfInterrupted_s, "DistanceSuccessEndIfInterrupted");
    getStaticParam(&mDistanceResetGearInput_s, "DistanceResetGearInput");
}

void HorseMoveToPlayer::m34(sead::Vector3f* out, const sead::Vector3f& pos,
                            const sead::Vector3f& target_pos, const sead::Vector3f& target_velocity,
                            const sead::Vector3f& up) {
    HorseFollow::m34(out, pos, target_pos, target_velocity, up);

    const f32 sec = *mTargetVelocityDistanceSec_s;
    if (sec > 0.0f) {
        ksys::act::ActorConstDataAccess acc;
        if (ksys::act::acquireActor(mTargetActor_d, &acc) && acc.sub_7100D12E64())
            out->setScaleAdd(sec * -30.0f, target_velocity, *out);
    }
}

}  // namespace uking::ai
