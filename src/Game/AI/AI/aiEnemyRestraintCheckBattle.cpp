#include "Game/AI/AI/aiEnemyRestraintCheckBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRestraintCheckBattle::EnemyRestraintCheckBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRestraintCheckBattle::~EnemyRestraintCheckBattle() = default;

void EnemyRestraintCheckBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        _70 = ksys::Timer(0.0f, 0.0f);
        _7c = ksys::Timer(0.0f, 0.0f);
    }

    if (sub_71003B1988()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("牽制", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘", &pack);
    }
}

void EnemyRestraintCheckBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRestraintCheckBattle::loadParams_() {
    getStaticParam(&mCheckInterval_s, "CheckInterval");
    getStaticParam(&mCheckRandTime_s, "CheckRandTime");
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mCheckVmin_s, "CheckVmin");
    getStaticParam(&mCheckVmax_s, "CheckVmax");
    getStaticParam(&mCheckAngle_s, "CheckAngle");
    getStaticParam(&mIsResetInterval_s, "IsResetInterval");
}

// NON_MATCHING: the original adds 0x7c explicitly before the `_7c` loads and stores value / previous value with one
// stp; ours uses a pre-indexed ldr and two str
bool EnemyRestraintCheckBattle::sub_71003B1988() {
    if (!(_70.value <= sead::Mathf::epsilon())) {
        _70.update();
        return false;
    }

    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;

    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&enemy->_c48._8, &accessor);
    if (accessor.hasProc() && accessor.x_13())
        return false;

    f32 value;
    if (sub_71003B2030()) {
        if (!(_7c.value <= sead::Mathf::epsilon()))
            _7c.update();
        value = _7c.value;
    } else {
        const s32 time = *mCheckRandTime_s;
        _7c = ksys::Timer(f32(time), f32(time));
        value = f32(time);
    }
    return value <= sead::Mathf::epsilon();
}

bool EnemyRestraintCheckBattle::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("戦闘") && getCurrentChild()->isFinished());
}

bool EnemyRestraintCheckBattle::isFailed() const {
    return ActionBase::isFailed() || (isCurrentChild("戦闘") && getCurrentChild()->isFailed());
}

}  // namespace uking::ai
