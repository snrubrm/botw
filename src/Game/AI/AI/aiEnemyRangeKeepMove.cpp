#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include <cmath>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRangeKeepMove::EnemyRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepMove::~EnemyRangeKeepMove() = default;

bool EnemyRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original selects the Data base pointer of the re-cast with branches (null / +8); we get csel
// with the +8 computed up front (one extra mov per checker)
// Restarts the two shared vibrate checkers if they are in use.
void EnemyRangeKeepMove::sub_71003AB3FC() {
    if (_f0._0) {
        auto* checker = sead::DynamicCast<Unk_71025b0578>(*_f0._0);
        if (checker && checker->mRefCount >= 1)
            _f0.getData()->reset();
    }
    if (_f8._0) {
        auto* checker = sead::DynamicCast<Unk_71025b7688>(*_f8._0);
        if (checker && checker->mRefCount >= 1)
            _f8.getData()->sub_710071F47C();
    }
}

// NON_MATCHING: parameter-load and horizontal-distance arithmetic scheduling differ.
void EnemyRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _10d = false;
    const s32 leave_min = *mLeaveTimerMin_s;
    _d8 = _dc = leave_min;
    _d4 = leave_min;
    const s32 back_min = *mBackTimeMin_s;
    const s32 back_max = *mBackTimeMax_s;
    _cc = sead::Mathi::min(back_min, back_max);
    _d0 = sead::Mathi::max(back_min, back_max);
    _e4 = 10;
    _e8 = 30;
    _c8 = _cc == _d0 ? _cc : sead::GlobalRandom::instance()->getS32Range(_cc, _d0);
    _e0 = _e4 == _e8 ? _e4 : sead::GlobalRandom::instance()->getS32Range(_e4, _e8);
    sub_71003AB3FC();
    auto* actor = mActor;
    _10c = false;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 distance = diff.length();
    const f32 base = *mBaseDist_s;
    const f32 far = *mFarDist_s;
    if (distance > base + far + sub_71007320F0(actor, m35())) {
        changeToBattleWalk();
    } else if (sub_71003AB704()) {
        changeToBattleBackAway();
    } else {
        const s8 direction = sub_71003AB9B0();
        if (direction == 0) {
            changeToBattleWait();
        } else if (direction == -5) {
            _10d = true;
            changeToBattleBackAway();
        } else {
            changeToMoveSideways(direction);
        }
    }
}

bool EnemyRangeKeepMove::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the `force` test is an eor + tbnz in the original (tbz here) and two instructions are
// scheduled differently; same logic. The upper clamp of the first branch really is the angle limit.
void EnemyRangeKeepMove::sub_71003AD3EC(f32* angle, const sead::Vector3f& front,
                                        const sead::Matrix34f& mtx, bool force, f32 speed, f32 dist) {
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    const sead::Vector3f& target = sub_71005D9330(mActor);
    sead::Vector3f dir(target.x - pos.x, 0.0f, target.z - pos.z);
    const f32 len = dir.normalize();
    if (len > dist + 1.0f && !force)
        return;
    const f32 diff = std::acos(sead::Mathf::clamp(dir.dot(front), -0.999f, 0.999f));
    const f32 side = dir.cross(front).y;
    const f32 limit = *mSpaceAngle_s;
    if (side < 0.0f) {
        if (diff > limit)
            speed *= sead::Mathf::clamp((diff - limit) * -3.0f / limit + 1.0f, 0.0f, limit);
        *angle += speed;
    } else {
        if (diff > limit)
            speed *= sead::Mathf::clamp((diff - limit) * -3.0f / limit + 1.0f, 0.0f, 1.0f);
        *angle -= speed;
    }
}

void EnemyRangeKeepMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBackTimeMin_s, "BackTimeMin");
    getStaticParam(&mBackTimeMax_s, "BackTimeMax");
    getStaticParam(&mLeaveTimerMin_s, "LeaveTimerMin");
    getStaticParam(&mLeaveTimerMax_s, "LeaveTimerMax");
    getStaticParam(&mPosVibrateFrame_s, "PosVibrateFrame");
    getStaticParam(&mRotVelVibrateFrame_s, "RotVelVibrateFrame");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mSpaceAngle_s, "SpaceAngle");
    getStaticParam(&mNoMoveDist_s, "NoMoveDist");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mIsCheckReachable_s, "IsCheckReachable");
    getAITreeVariable(&mRefPosVibrateCheckerForAI_a, "RefPosVibrateCheckerForAI");
    getAITreeVariable(&mRefVelRotVibrateCheckerforAI_a, "RefVelRotVibrateCheckerforAI");
}

void EnemyRangeKeepMove::changeToBattleBackAway() {
    m38();
    _c8 = _cc == _d0 ? _cc : sead::GlobalRandom::instance()->getS32Range(_cc, _d0);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘後ずさり", &pack);
}

void EnemyRangeKeepMove::changeToBattleWait() {
    m36();
    sub_71003AB3FC();
    _e0 = _e4 == _e8 ? _e4 : sead::GlobalRandom::instance()->getS32Range(_e4, _e8);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘待機", &pack);
}

bool EnemyRangeKeepMove::sub_71003AD058() {
    if (!*mIsCheckBack_s)
        return false;
    sead::Vector3f dir = mActor->getMtx().getTranslation();
    dir -= sub_71005D9330(mActor);
    dir.normalize();
    return sub_710072FEC4(mActor, dir, 3.0f, nullptr, false, nullptr);
}

// NON_MATCHING: the zero for the y term is materialised before the first square (scheduling)
bool EnemyRangeKeepMove::sub_71003AD1F8() {
    auto* actor = mActor;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    return dist < *mBaseDist_s + sub_71007320F0(actor, m35());
}

// NON_MATCHING: the zero for the y term is materialised before the first square (scheduling)
bool EnemyRangeKeepMove::sub_71003AD298() {
    auto* actor = mActor;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    return dist < *mBaseDist_s + *mCloseDist_s + sub_71007320F0(actor, m35());
}

// NON_MATCHING: the zero for the y term is materialised before the first square (scheduling)
bool EnemyRangeKeepMove::m34() {
    auto* actor = mActor;
    const auto& target_pos = sub_71005D9330(actor);
    sead::Vector3f diff = target_pos - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    return dist > *mBaseDist_s + *mOutDist_s + sub_71007320F0(actor, m35());
}

bool EnemyRangeKeepMove::sub_71003AD160() {
    auto* actor = mActor;
    if (!actor)
        return false;
    f32 radius = 0;
    if (auto* nav = actor->m45())
        radius = nav->_2a8 * nav->_2ac;
    const sead::Vector3f target = sub_71005D9330(actor);
    return sub_710072CB78(actor, target, nullptr, radius, 3);
}

void EnemyRangeKeepMove::changeToBattleWalk() {
    m37();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘歩行", &pack);
}

void EnemyRangeKeepMove::changeToForcedRetreat() {
    m39();

    s32 value = _cc;
    if (_d0 != _cc)
        value = sead::GlobalRandom::instance()->getS32Range(_cc, _d0);
    _c8 = value;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("強制後退", &pack);
}

void EnemyRangeKeepMove::changeToMoveSideways(s8 dir) {
    sub_71003AB3FC();
    m40();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addInt(dir, "RotDir", -1);
    changeChild("横移動", &pack);
}

// NON_MATCHING: the horizontal-distance arithmetic is scheduled differently (same as enter_).
bool EnemyRangeKeepMove::sub_71003AB704() {
    auto* actor = mActor;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 distance = diff.length();
    const f32 limit = *mBaseDist_s + *mCloseDist_s + sub_71007320F0(actor, m35());
    if (!(distance < limit))
        return false;
    if (!*mIsCheckBack_s)
        return true;

    sead::Vector3f direction = mActor->getMtx().getTranslation();
    direction -= sub_71005D9330(mActor);
    direction.normalize();
    return !sub_710072FEC4(mActor, direction, 3.0f, nullptr, false, nullptr);
}

}  // namespace uking::ai
