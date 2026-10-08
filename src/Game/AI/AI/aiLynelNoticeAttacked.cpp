#include "Game/AI/AI/aiLynelNoticeAttacked.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

LynelNoticeAttacked::LynelNoticeAttacked(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelNoticeAttacked::~LynelNoticeAttacked() = default;

bool LynelNoticeAttacked::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: backend scheduling only — the original loads the actor-x/z components
// before the home-x/z components and keeps home_pos at sp+0x8; ours loads home first
// and spills home_pos at the frame top. Actor-first temporaries reproduce the load
// order (tested, reverted as register-steering); no lever found for the home_pos slot.
void LynelNoticeAttacked::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 reset_time = *mRepeatResetTime_s;
    const f32 time = reset_time > 0 ? reset_time : 1.0f;
    const f32 rate = reset_time > 0 ? -1.0f : 0.0f;
    _6c.value = time;
    _6c.previous_value = time;
    _6c.rate = rate;
    mActor->getMtx().getTranslation(_60);
    ++*mLynelNoticeAttackRepeatNum_a;
    if (*mLynelNoticeAttackRepeatNum_a > *mRepeatMax_s) {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        const f32 dx = home.x - mActor->getMtx().m[0][3];
        const f32 dz = home.z - mActor->getMtx().m[2][3];
        if (dx * dx + dz * dz >= *mForceReturnDistFromHomePos_s * *mForceReturnDistFromHomePos_s) {
            *mLynelNoticeAttackRepeatNum_a = 0;
            sead::Vector3f home_pos;
            mActor->getHomePos(&home_pos);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(home_pos, "TargetPos", -1);
            changeChild("強制帰還", &pack);
            return;
        }
    }
    auto& link = sub_71005D94AC(mActor);
    if (!link.hasProc()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("未発見", &pack);
    } else {
        auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
        if (enemy && enemy->_e08._0 == link) {
            sub_7100494D04();
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("未発見", &pack);
        }
    }
}

bool LynelNoticeAttacked::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool LynelNoticeAttacked::isFinished() const {
    return getCurrentChild()->isFinished();
}

void LynelNoticeAttacked::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelNoticeAttacked::loadParams_() {
    getStaticParam(&mRepeatMax_s, "RepeatMax");
    getStaticParam(&mRepeatResetTime_s, "RepeatResetTime");
    getStaticParam(&mForceReturnDistFromHomePos_s, "ForceReturnDistFromHomePos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getAITreeVariable(&mLynelNoticeAttackRepeatNum_a, "LynelNoticeAttackRepeatNum");
}

void LynelNoticeAttacked::sub_7100494D04() {
    sead::Vector3f target;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e08._10.getTranslation(target);
    else
        target = getPlayerPosition();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("発見", &pack);
}

void LynelNoticeAttacked::calc_() {
    if (_6c.value <= sead::Mathf::epsilon()) {
        *mLynelNoticeAttackRepeatNum_a = 0;
        _6c = ksys::Timer(1.0f, 1.0f, 0.0f);
    } else {
        _6c.update();
    }

    if (*mLynelNoticeAttackRepeatNum_a >= 1) {
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - _60;
        if (diff.x * diff.x + diff.z * diff.z > 16.0f)
            *mLynelNoticeAttackRepeatNum_a = 0;
    }
}

}  // namespace uking::ai
