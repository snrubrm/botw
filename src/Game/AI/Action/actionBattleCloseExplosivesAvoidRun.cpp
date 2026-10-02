#include "Game/AI/Action/actionBattleCloseExplosivesAvoidRun.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

BattleCloseExplosivesAvoidRun::BattleCloseExplosivesAvoidRun(const InitArg& arg)
    : BattleCloseMoveAction(arg) {}

BattleCloseExplosivesAvoidRun::~BattleCloseExplosivesAvoidRun() = default;

void BattleCloseExplosivesAvoidRun::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseMoveAction::enter_(params);
    playAS("Run", true, 0, 0, -1.0f);
}

void BattleCloseExplosivesAvoidRun::leave_() {
    BattleCloseMoveAction::leave_();
    auto* mgr = mActor->getDamageMgr();
    if (mgr && _b0.mDamageManager)
        mgr->removeDamageCallback(&_b0);
}

void BattleCloseExplosivesAvoidRun::loadParams_() {
    BattleCloseMoveActionBase::loadParams_();
    getStaticParam(&mDamageIgnoreDist_s, "DamageIgnoreDist");
}

// NON_MATCHING: register allocation / load pairing of the entry position vectors
void BattleCloseExplosivesAvoidRun::m32(sead::Vector3f* target_pos) {
    BattleCloseAction::m32(target_pos);

    auto* actor = mActor;
    if (!actor)
        return;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return;

    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f to_target = *mTargetPos_d - pos;
    to_target.normalize();

    sead::Vector3f up;
    {
        sead::Vector3f gravity;
        sub_710072DC50(&gravity, actor);
        up = -(gravity * (1.0f / 900.0f));
        if (up.normalize() < sead::Mathf::epsilon())
            up.set(sead::Vector3f::ey);
    }

    bool in_danger = false;
    bool avoiding = false;
    Unk_7102451538 filter;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&entry->_0.mLink, &accessor);
            if (accessor.sub_7100D10E6C(30))
                continue;
        }

        sead::Vector3f entry_pos;
        entry->_58.getTranslation(entry_pos);
        const sead::Vector3f diff = entry_pos - pos;
        if (std::sqrt(diff.x * diff.x + diff.z * diff.z) > 10.0f)
            continue;
        if (sead::Mathf::abs(diff.y) > 3.0f)
            continue;

        sub_71005DB068(mActor, entry_pos);

        sead::Vector3f from_entry = pos - entry_pos;
        from_entry.normalize();
        sead::Vector3f target_from_entry = *mTargetPos_d - entry_pos;
        target_from_entry.normalize();
        if (from_entry.dot(target_from_entry) > 0.0f) {
            in_danger = true;
            continue;
        }

        sead::Vector3f to_entry = entry_pos - pos;
        to_entry.normalize();
        sead::Vector3f side;
        side.setCross(to_entry, up);
        side.normalize();

        sead::Vector3f front;
        actor->getMtx().getBase(front, 2);
        front.normalize();
        sead::Vector3f dir = entry_pos - pos;
        dir.normalize();
        if (dir.z * front.x - dir.x * front.z > 0.0f)
            side = -side;

        in_danger = true;
        *target_pos = side * 5.0f;
        *target_pos *= *mSpeed_s;
        avoiding = true;
    }

    if (avoiding) {
        const f32 len = target_pos->length();
        const f32 max_len = *mSpeed_s * 2.0f;
        if (len > max_len) {
            const f32 cur_len = target_pos->length();
            if (cur_len > 0.0f)
                *target_pos *= max_len / cur_len;
        }
        *target_pos -= to_target * *mSpeed_s;
    }

    auto* mgr = mActor->getDamageMgr();
    if (in_danger) {
        if (mgr && !_b0.mDamageManager)
            mgr->addDamageCallback(4, &_b0);
    } else {
        if (mgr && _b0.mDamageManager)
            mgr->removeDamageCallback(&_b0);
    }
}

}  // namespace uking::action

void Unk_710236b490::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 != 4)
        return;

    auto* mgr = sead::DynamicCast<uking::dmg::DamageManager>(mDamageManager);
    if (!mgr)
        return;

    const sead::Vector3f pos = mgr->mActor->getMtx().getTranslation();
    auto* attacker = mgr->m37();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(attacker, &accessor);
    const sead::Vector3f diff = pos - accessor.getActorMtx().getTranslation();
    if (diff.length() >= *mOwner->mDamageIgnoreDist_s) {
        *a1 = 0;
        *a2 = 0;
        *a3 = 0;
        *a4 = 0;
        *a5 = 0;
    }
}
