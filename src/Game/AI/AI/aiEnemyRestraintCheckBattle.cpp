#include "Game/AI/AI/aiEnemyRestraintCheckBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
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

// NON_MATCHING: the original keeps the DynamicCast<Enemy> result as a `tst; csel` value that is tested after the
// IsResetInterval load (ours branches on the isDerived result directly), loads the epsilon after the Timer value and
// stores the Timer's value / previous value with two `str` (ours one `stp`)
void EnemyRestraintCheckBattle::calc_() {
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("牽制")) {
        const s32 interval = *mCheckInterval_s;
        _70 = ksys::Timer(f32(interval), f32(interval));
        const s32 rand_time = *mCheckRandTime_s;
        _7c = ksys::Timer(f32(rand_time), f32(rand_time));
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘", &pack);
        return;
    }

    if (getCurrentChild()->isChangeable() && isCurrentChild("戦闘")) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
            if (*mIsResetInterval_s) {
                if (enemy->_e68.value <= sead::Mathf::epsilon()) {
                    const s32 interval = *mCheckInterval_s;
                    _70 = ksys::Timer(f32(interval), f32(interval));
                }
            }
        }
        if (sub_71003B1988()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("牽制", &pack);
            return;
        }
    }

    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
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

// NON_MATCHING: the original loads the actor's y and the other vector components in a different order and ends the
// vmax test with `b.le` to a `return true` block (ours: `cset ls`)
bool EnemyRestraintCheckBattle::sub_71003B2030() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return false;
    if (!sub_710072E1B4(enemy, false))
        return false;

    const sead::Vector3f target = sub_71005D9330(enemy);
    if (!sub_710072DDB8(target, enemy->getMtx(), *mCheckAngle_s))
        return false;

    const auto& mtx = enemy->getMtx();
    const f32 dy = target.y - mtx.m[1][3];
    const f32 dx = target.x - mtx.m[0][3];
    const f32 dz = target.z - mtx.m[2][3];
    if (sead::Mathf::sqrt(dx * dx + dz * dz) > *mCheckDist_s)
        return false;
    if (dy < *mCheckVmin_s)
        return false;
    if (dy <= *mCheckVmax_s)
        return true;
    return false;
}

bool EnemyRestraintCheckBattle::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("戦闘") && getCurrentChild()->isFinished());
}

bool EnemyRestraintCheckBattle::isFailed() const {
    return ActionBase::isFailed() || (isCurrentChild("戦闘") && getCurrentChild()->isFailed());
}

}  // namespace uking::ai
