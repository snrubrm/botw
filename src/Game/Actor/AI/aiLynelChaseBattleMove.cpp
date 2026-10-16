#include "Game/Actor/AI/aiLynelChaseBattleMove.h"
#include <algorithm>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelChaseBattleMove::LynelChaseBattleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelChaseBattleMove::~LynelChaseBattleMove() = default;

bool LynelChaseBattleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelChaseBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _60.mTimer = ksys::Timer(20.0f, 20.0f);
    const f32 x = mActor->getMtx()(0, 3);
    const f32 z = mActor->getMtx()(2, 3);
    const sead::Vector3f& target = sub_71005D9330(mActor);
    const f32 dx = x - target.x;
    const f32 dz = z - target.z;
    const f32 dist = sead::Mathf::sqrt(dx * dx + dz * dz);
    if (*mBaseDist_s + *mCloseStartDist_s < dist) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("近づき", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("追跡", &pack);
    }
}

// NON_MATCHING: the original keeps the gear and row enum temporaries of the speed lookups on the stack (and a dead
// lookup for the current gear).
void LynelChaseBattleMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("近づき")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("追跡", &pack);
        } else {
            setFinished();
        }
        return;
    }

    if (child->isChangeable()) {
        const f32 x = mActor->getMtx()(0, 3);
        const f32 z = mActor->getMtx()(2, 3);
        const sead::Vector3f& target = sub_71005D9330(mActor);
        const f32 dx = x - target.x;
        const f32 dz = z - target.z;
        const f32 dist = sead::Mathf::sqrt(dx * dx + dz * dz);
        if (*mBaseDist_s + *mOutDist_s < dist) {
            setFailed();
            return;
        }
        if (isCurrentChild("追跡") && *mBaseDist_s + *mCloseStartDist_s < dist) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("近づき", &pack);
            return;
        }
    }

    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    _60.sub_7100D3BCE4();
    if (!(_60.mTimer.value <= sead::Mathf::epsilon()))
        return;

    const s32 decision = sub_710048F5A0();
    auto* rideable = mActor->m132();
    if (!rideable)
        return;

    const auto& velocity = sub_71005D9548(mActor);
    const f32 speed = sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z);
    const auto getSpeed = [rideable](s32 gear, s32 row) {
        const auto* entry = &act::sUnk_7102603058;
        if (gear != 0 && rideable->_170) {
            if (row >= rideable->_178)
                row = 0;
            entry = &rideable->_170->mGears[row][gear - 1];
        }
        return entry->mSpeed * rideable->_164;
    };

    const s32 min_gear = 2;
    const s32 gear = rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b;
    s32 new_gear = gear;
    switch (decision) {
    case 0:
        new_gear = s32(std::min(f32(gear + 1), 4.0f));
        break;
    case 2:
        new_gear = s32(std::max(f32(gear - 1), f32(min_gear)));
        break;
    case 1: {
        const s32 up = s32(std::min(f32(gear + 1), 4.0f));
        const s32 down = s32(std::max(f32(gear - 1), f32(min_gear)));
        const f32 current = speed * 30.0f;
        if (current >= getSpeed(up, 1))
            new_gear = up;
        else if (current <= getSpeed(down, 1))
            new_gear = down;
        break;
    }
    default:
        break;
    }
    rideable->_130 = 0;
    rideable->_134 = new_gear;
}

// NON_MATCHING: register allocation (the target and own translations swap registers).
s32 LynelChaseBattleMove::sub_710048F5A0() {
    auto* link = sub_71005D9050(mActor);
    if (!link)
        return 3;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const auto& target_mtx = accessor.getActorMtx();
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    sead::Vector3f target;
    target_mtx.getTranslation(target);
    front.normalize();
    const f32 dist = (target - pos).dot(front);
    if (*mSpeedUpDist_s < dist)
        return 0;
    if (*mSlowDownDist_s > dist)
        return 2;
    return 1;
}

void LynelChaseBattleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelChaseBattleMove::loadParams_() {
    getStaticParam(&mSlowDownDist_s, "SlowDownDist");
    getStaticParam(&mSpeedUpDist_s, "SpeedUpDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
}

}  // namespace uking::ai
