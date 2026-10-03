#include "Game/AI/AI/aiEnemyNoticeLimit.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyNoticeLimit::EnemyNoticeLimit(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyNoticeLimit::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyNoticeLimit::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sub_71005D8F28(mActor)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("定員オーバー", &pack);
        setFailed();
        return;
    }

    dmg::Unk_7100671794_Entry entry;
    entry.mLink.acquire(mActor, false);
    const f32 x = mActor->getMtx().m[0][3];
    const f32 y = mActor->getMtx().m[1][3];
    const f32 z = mActor->getMtx().m[2][3];
    const auto& target = sub_71005D9330(mActor);
    const sead::Vector3f diff(x - target.x, y - target.y, z - target.z);
    entry.mDistance = diff.length();
    if (dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A74(&entry, *mOverNum_s)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("定員内", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("定員オーバー", &pack);
    }
}

void EnemyNoticeLimit::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed() && child->isChangeable()) {
        if (!isCurrentChild("定員オーバー")) {
            if (!dmg::DamageInfoMgr::instance()->get4f8().sub_7100671ED8(mActor)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("定員オーバー", &pack);
            }
        } else if (!sub_71005D8F28(mActor)) {
            setFailed();
        } else {
            dmg::Unk_7100671794_Entry entry;
            entry.mLink.acquire(mActor, false);
            const f32 x = mActor->getMtx().m[0][3];
            const f32 y = mActor->getMtx().m[1][3];
            const f32 z = mActor->getMtx().m[2][3];
            const auto& target = sub_71005D9330(mActor);
            const sead::Vector3f diff(x - target.x, y - target.y, z - target.z);
            entry.mDistance = diff.length();
            if (dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A74(&entry, *mOverNum_s)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("定員内", &pack);
            }
        }
    }
    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

bool EnemyNoticeLimit::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyNoticeLimit::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void EnemyNoticeLimit::leave_() {
    dmg::DamageInfoMgr::instance()->get4f8().sub_7100671F78(mActor);
}

void EnemyNoticeLimit::loadParams_() {
    getStaticParam(&mOverNum_s, "OverNum");
}

bool EnemyNoticeLimit::isChangeable() const {
    if (ksys::act::ai::Ai::isChangeable())
        return true;
    return getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
