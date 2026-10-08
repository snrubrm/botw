#include "Game/AI/AI/aiEnemyEscapeMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

void* Unk_NavMeshCallback::m1() {
    return nullptr;
}

bool Unk_NavMeshCallback::m2() {
    return true;
}

namespace uking::ai {

EnemyEscapeMove::EnemyEscapeMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _58.clear();
}

EnemyEscapeMove::~EnemyEscapeMove() = default;

bool EnemyEscapeMove::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void EnemyEscapeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _d28 = sub_71005E2BCC(actor);
    auto* nav = actor->m45();
    if (!nav) {
        changeChild("見まわす", nullptr);
        setFailed();
        return;
    }
    if (!nav->_18)
        ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
    if (_d28 && _d28->_0)
        _d28->_0->sub_7100F7604C(0.2f);
    _d24 = false;
    _58.clear();
    _d08 = -1;
    _d0c = ksys::Timer(0, 0);
    sub_7100389D34();
}

bool EnemyEscapeMove::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyEscapeMove::leave_() {
    if (_d28 && _d28->_0)
        _d28->_0->inlineReset();
}

void EnemyEscapeMove::loadParams_() {
    if (mActor->getParam()) {
        getDynamicParam(&mTargetPos_d, "TargetPos");
        getStaticParam(&mBehindCheckDist_s, "BehindCheckDist");
    }
}

// NON_MATCHING: stack layout (the original keeps the `target` vector below the InlineParamPack and shares one slot
// between the pack, the SafeString temporaries and the `out` vector) and the order of the loads of nav->_194
void EnemyEscapeMove::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("ジャンプ")) {
            sub_7100389D34();
            return;
        }
        if (isCurrentChild("見まわす")) {
            setFailed();
            return;
        }
        if (isCurrentChild("直進逃走") || isCurrentChild("探索逃走")) {
            setFinished();
            return;
        }
    }

    if (!isCurrentChild("直進逃走") && !isCurrentChild("探索逃走")) {
        if (!isCurrentChild("見まわす"))
            return;
        if (!_d28 || _d28->_8 != 1)
            return;
        auto* nav = mActor->m45();
        if (!nav)
            return;
        sead::Vector3f target;
        target = nav->_194;
        if (target.isNan())
            return;
        _d28->_8 = -1;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("探索逃走", &pack);
        return;
    }

    if (_d28) {
        if (_d28->_8 == 1) {
            if (auto* nav = mActor->m45()) {
                sead::Vector3f target;
                target = nav->_194;
                if (!target.isNan()) {
                    _d28->_8 = -1;
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(target, "TargetPos", -1);
                    changeChild("探索逃走", &pack);
                    return;
                }
            }
        }
        if (_d28) {
            const s32 state = _d28->_8;
            if (state == 3) {
                setFinished();
                return;
            }
            if (state == 2) {
                changeChild("見まわす", nullptr);
                return;
            }
        }
    }

    sead::Vector3f dir(mTargetPos_d->x - mActor->getMtx().getTranslation().x, 0.0f,
                       mTargetPos_d->z - mActor->getMtx().getTranslation().z);
    dir.normalize();
    const f32 dot = dir.dot(mActor->getMtx().getBase(2));
    const f32 dx = mTargetPos_d->x - mActor->getMtx().getTranslation().x;
    const f32 dz = mTargetPos_d->z - mActor->getMtx().getTranslation().z;
    if (!(sead::Mathf::sqrt(dx * dx + dz * dz) > 5.0f))
        _d0c.update();

    if (dot < 0.0f || _d0c.value > sead::Mathf::epsilon()) {
        sead::Vector3f out;
        if (isCurrentChild("探索逃走") && sub_710038A5B0(&out)) {
            _48 = out;
            sub_710038A78C();
            return;
        }
        if (!_d24)
            return;
        sub_710038A8EC();
        return;
    }
    sub_7100389D34();
}

// NON_MATCHING: register allocation / scheduling of the direction math, the original builds the end iterator of
// `points` before the begin iterator
void EnemyEscapeMove::sub_7100389D34() {
    _d0c = ksys::Timer(60.0f, 60.0f);
    auto* actor = mActor;
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    sead::Vector3f dir(pos.x - mTargetPos_d->x, 0.0f, pos.z - mTargetPos_d->z);
    dir.normalize();
    _48 = pos;
    _48 = pos + dir * *mBehindCheckDist_s;
    if (sub_710072FAB0(actor, _48, nullptr, -1, -1.0f, -1.0f)) {
        sub_710038A78C();
        return;
    }

    sead::FixedObjList<sead::Vector3f, 16> points;
    if (!sub_710038AB40()) {
        changeChild("見まわす", nullptr);
        return;
    }
    bool copied = false;
    for (auto& point : _58) {
        if (points.isFull())
            break;
        points.emplaceBack(point);
        copied = true;
    }
    if (!copied) {
        changeChild("見まわす", nullptr);
        return;
    }
    if (!isCurrentChild("探索逃走") && !isCurrentChild("直進逃走"))
        changeChild("見まわす", nullptr);
    if (auto* move = _d28; move && move->_0) {
        move->_0->sub_710038AE34(points.begin(), points.end());
        move->_8 = 0;
    }
}

bool EnemyEscapeMove::sub_710038A5B0(sead::Vector3f* out) {
    auto* actor = mActor;
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);
    front.normalize();
    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    sead::Vector3f dir(pos.x - mTargetPos_d->x, 0.0f, pos.z - mTargetPos_d->z);
    dir.normalize();
    if (!(front.dot(dir) < 0.49999997f)) {
        *out = pos;
        *out += front * *mBehindCheckDist_s;
        return sub_710072FAB0(actor, *out, nullptr, -1, -1.0f, -1.0f);
    }
    return false;
}

void EnemyEscapeMove::sub_710038A78C() {
    if (_d28) {
        _d28->_8 = -1;
        if (_d28->_0)
            _d28->_0->inlineReset();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_48, "TargetPos", -1);
    changeChild("直進逃走", &pack);
}

// NON_MATCHING: the load of _d18.z is scheduled before the first fsub in the original
void EnemyEscapeMove::sub_710038A8EC() {
    _d24 = false;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f dir(_d18.x - pos.x, 0.0f, _d18.z - pos.z);
    dir.normalize();
    _d18 += dir * 3.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_d18, "TargetPos", -1);
    changeChild("ジャンプ", &pack);
}

}  // namespace uking::ai
