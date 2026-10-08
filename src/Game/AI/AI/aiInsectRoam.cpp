#include "Game/AI/AI/aiInsectRoam.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

InsectRoam::InsectRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InsectRoam::~InsectRoam() = default;

bool InsectRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InsectRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = *mTerritoryRadius_s + *mTerritoryRadiusRnd_s * sead::GlobalRandom::instance()->getF32();
    _60 = false;
    mActor->getMtx().getBase(_68, 2);
    _68.normalize();
    mActor->getMtx().getTranslation(_74);
    _80 = mActor->getMtx().getBase(2);
    _8c = _74;
    _98 = ksys::Timer(0, 0, 1);
    _a4 = ksys::Timer(0, 0);
    changeChild("徘徊待機");
}

void InsectRoam::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("徘徊歩行")) {
            _60 = child->isFailed();
            changeChild("徘徊待機");
        } else {
            isCurrentChild("徘徊待機");
            changeToRoamWalk();
        }
    }
    if (isCurrentChild("徘徊歩行") && *mMoveSpeed_s > 0) {
        _a4.update();
        if (_a4.value <= sead::Mathf::epsilon() && child->isChangeable()) {
            _98 = ksys::Timer(0, 0);
            _60 = true;
            changeChild("徘徊待機");
        }
    }
}

// NON_MATCHING: backend register allocation only (same values, branches and calls) — the original keeps
// _68 and the actor-pos components in float regs across the calls (ours uses int regs / reloads), spills
// m03/m13, and pairs the out-pos x/y stores; also the join angle has a dead +0.0f add
void InsectRoam::sub_710044ACE4(sead::Vector3f* pos, sead::Vector3f* dir) {
    if (!pos && !dir)
        return;
    auto* actor = mActor;
    const sead::Matrix34f& actor_mtx = actor->getMtx();
    bool flag = false;
    if (isLandedMaybe(actor, false)) {
        auto* unk = sub_71007A471C(actor, 0);
        sead::Vector3f front(unk->_c.x, 0.0f, unk->_c.z);
        front.normalize();
        flag = _68.dot(front) < -0.25881904f;
    }
    sead::Vector3f to_target(mTargetPos_d->x - actor_mtx.m[0][3], 0.0f,
                             mTargetPos_d->z - actor_mtx.m[2][3]);
    const f32 len = to_target.normalize();
    f32 angle;
    if ((s32(flag) | (_60 != 0)) == 1) {
        angle = ksys::util::sub_71011EF0CC(sead::GlobalRandom::instance()->getF32() * 40.0f -
                                           20.0f + 3.14159274f);
    } else if (len > _64) {
        const f32 base_angle = sead::Mathf::atan2(to_target.x, to_target.z);
        angle = sead::GlobalRandom::instance()->getF32() * 0.17453292f - 0.08726646f + base_angle;
    } else {
        const f32 half = _64 * 0.5f;
        if (len > half) {
            const f32 t = sead::GlobalRandom::instance()->getF32() * 30.0f + 20.0f;
            const f32 cross = _68.z * to_target.x - _68.x * to_target.z;
            angle = cross > 0.0f ? t * 0.017453292f : -(t * 0.017453292f);
        } else {
            angle = sead::GlobalRandom::instance()->getF32() * 60.0f - 30.0f;
        }
    }
    sead::Vector3f vec;
    vec.x = _68.x;
    vec.y = _68.y;
    vec.z = _68.z;
    ksys::util::sub_71011EF010(&vec, angle);
    vec.normalize();
    if (pos) {
        const f32 dist = *mMoveDist_s;
        const f32 x = actor_mtx.m[0][3] + dist * vec.x;
        const f32 y = actor_mtx.m[1][3] + dist * vec.y;
        const f32 z = actor_mtx.m[2][3] + dist * vec.z;
        pos->z = z;
        pos->x = x;
        pos->y = y;
    }
    if (dir)
        dir->set(vec);
}

void InsectRoam::changeToRoamWalk() {
    sub_710044ACE4(&_74, &_68);
    if (*mMoveSpeed_s > 0) {
        const f32 time = *mMoveDist_s / *mMoveSpeed_s + 30.0f;
        _a4 = ksys::Timer(time, time);
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_74, "TargetPos", -1);
    changeChild("徘徊歩行", &params);
}

void InsectRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InsectRoam::loadParams_() {
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
