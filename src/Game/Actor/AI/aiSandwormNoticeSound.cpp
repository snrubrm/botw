#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/Actor/AI/aiSandwormNoticeSound.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SandwormNoticeSound::SandwormNoticeSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormNoticeSound::~SandwormNoticeSound() = default;

bool SandwormNoticeSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    _70.set(*mTargetPos_d);
    mActor->m93(2, 0.0f);
    _60 = ksys::Timer(-1.0f, -1.0f, 0.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("振り向き", &pack);
}

void SandwormNoticeSound::leave_() {
    _98.reset();
    mActor->m93(0, 0.0f);
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(4);
}

void SandwormNoticeSound::loadParams_() {
    getStaticParam(&mRetryDist_s, "RetryDist");
    getStaticParam(&mTargetActorLockOnDist_s, "TargetActorLockOnDist");
    getStaticParam(&mTargetPosLockOnDist_s, "TargetPosLockOnDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// 0x710055c464
void SandwormNoticeSound::sub_710055C464() {
    _6c = false;
    _6d = false;
    sub_710055C800();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &pack);
}

// 0x710055c714
void SandwormNoticeSound::sub_710055C714() {
    mActor->m93(0, 0.0f);
    _98.reset();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("見失い", &pack);
}

// NON_MATCHING: operand load order of the XZ distance test (the original loads both target components first)
// 0x710055c800
void SandwormNoticeSound::sub_710055C800() {
    if (!isCurrentChild("移動") || _6d)
        return;
    const auto& mtx = mActor->getMtx();
    const f32 dx = mtx.m[0][3] - mTargetPos_d->x;
    const f32 dz = mtx.m[2][3] - mTargetPos_d->z;
    if (!(dx * dx + dz * dz <= *mTargetActorLockOnDist_s * *mTargetActorLockOnDist_s))
        return;
    mActor->m93(4, 0.0f);
    _60 = ksys::Timer(15.0f, 15.0f);
    _6c = false;
    _6d = true;
    _7c = *mTargetPos_d;
    _98 = *mTargetActor_d;
}

// 0x710055c538
// NON_MATCHING: native matrix-vector scheduling and parameter-pack temporaries differ.
void SandwormNoticeSound::sub_710055C538() {
    const auto& mtx = mActor->getMtx();
    const sead::Vector3f target = mtx * sead::Vector3f(0.0f, 0.0f, 0.1f);
    _88 = mtx * sead::Vector3f::ez;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    changeChild("攻撃", &pack);
}

// 0x710055bdc0
// NON_MATCHING: native repeated navigation probes, child dispatch and float scheduling differ.
void SandwormNoticeSound::calc_() {
    if (!(_60.value <= sead::Mathf::epsilon())) {
        _60.update();
        if (_60.value <= sead::Mathf::epsilon())
            mActor->m93(0, 0.0f);
    }
    if (isFinished() || isFailed())
        return;
    auto* child = getCurrentChild();
    // Inline-only in the original; name is a guess. The same placement/navmesh probe
    // sequence occurs three times in the native calc body.
    const auto is_target_reachable = [&] {
        const auto* target = mTargetPos_d;
        auto* placement = AutoPlacementMgr::instance();
        if (placement && placement->isNonAutoPlacement(*target, true))
            return false;
        auto* nav = mActor->m45();
        if (!nav)
            return false;
        sead::Vector3f projected;
        return nav->sub_7100F76078(&projected, *target, 0.5f).sub_7100F7EB40();
    };
    if (!child->isFinished() && !child->isFailed()) {
        if (isCurrentChild("移動") && _6d) {
            if (!(_98 == *mTargetActor_d))
                return;
            if (!is_target_reachable()) {
                sub_710055C714();
                return;
            }
            const auto& mtx = mActor->getMtx();
            const sead::Vector2f old_delta(mtx.m[0][3] - _7c.x, mtx.m[2][3] - _7c.z);
            const sead::Vector2f new_delta(mtx.m[0][3] - mTargetPos_d->x,
                                         mtx.m[2][3] - mTargetPos_d->z);
            if (!(old_delta.squaredLength() > new_delta.squaredLength())) {
                if (!_6c) {
                    _7c = *mTargetPos_d;
                    if (new_delta.length() < *mTargetPosLockOnDist_s)
                        _6c = true;
                }
            } else {
                _7c = *mTargetPos_d;
            }
            child->setDynamicParam(_7c, "TargetPos");
            return;
        }
        if (isCurrentChild("攻撃") || isCurrentChild("攻撃後始末")) {
            if (_98 == *mTargetActor_d && ksys::act::isPlayerProfile(&_98) && is_target_reachable()) {
                const auto& mtx = mActor->getMtx();
                const sead::Vector2f delta(mtx.m[0][3] - mTargetPos_d->x,
                                           mtx.m[2][3] - mTargetPos_d->z);
                if (*mRetryDist_s < delta.length())
                    _88 = *mTargetPos_d;
            }
            if (isCurrentChild("攻撃後始末"))
                child->setDynamicParam(_88, "TargetPos");
            return;
        }
        sub_710055C800();
        if (is_target_reachable()) {
            if (isCurrentChild("見失い"))
                sub_710055C464();
            else
                child->setDynamicParam(*mTargetPos_d, "TargetPos");
        } else if (!isCurrentChild("見失い")) {
            sub_710055C714();
        }
        return;
    }
    if (isCurrentChild("振り向き")) {
        sub_710055C464();
    } else if (isCurrentChild("移動")) {
        if (child->isFinished())
            sub_710055C538();
        else
            setFailed();
    } else if (isCurrentChild("攻撃")) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_88, "TargetPos", -1);
        changeChild("攻撃後始末", &pack);
    } else if (isCurrentChild("攻撃後始末")) {
        auto* link = sub_71005D9050(mActor);
        if (!link || !link->hasProc()) {
            setFailed();
            return;
        }
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(link, &accessor)) {
            const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
            auto* placement = AutoPlacementMgr::instance();
            if (placement && placement->isNonAutoPlacement(pos, true)) {
                sub_71005D8E9C(mActor);
                setFailed();
                return;
            }
        }
        setFinished();
    } else {
        setFailed();
    }
}

}  // namespace uking::ai
