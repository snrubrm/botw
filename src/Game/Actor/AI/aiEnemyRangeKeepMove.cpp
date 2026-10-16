#include "Game/Actor/AI/aiEnemyRangeKeepMove.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include <cmath>
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRangeKeepMove::EnemyRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepMove::~EnemyRangeKeepMove() = default;

// NON_MATCHING: same as NavMoveTarget::init_ (the Data pointer of the re-cast is selected with branches in the
// original).
bool EnemyRangeKeepMove::init_(sead::Heap* heap) {
    if (*mPosVibrateFrame_s >= 1) {
        if (!_f0.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateCheckerForAI_a)))
            return false;
        _f0.getData()->_84 = 3.0f;
        if (*mPosVibrateFrame_s >= 1)
            _f0.getData()->_88 = *mPosVibrateFrame_s;
    }
    if (*mRotVelVibrateFrame_s >= 1) {
        if (!_f8.acquire(heap, static_cast<Unk_71025afb58**>(mRefVelRotVibrateCheckerforAI_a)))
            return false;
        _f8.getData()->sub_710071F494(*mRotVelVibrateFrame_s, 3.0f);
    }
    return true;
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

// The side to move to (-1 / 1) to keep space from the other chemicals / awareness targets / enemies near the
// line to the target, 0 if there is none (or the side point is unreachable), -5 if the burning chemical and the
// others push to opposite sides.
// NON_MATCHING: stack layout of the vector copies and the sign test codegen; same logic.
s8 EnemyRangeKeepMove::sub_71003AB9B0() {
    if (*mSpaceAngle_s <= 0.0f)
        return 0;

    f32 angle = 0.0f;
    auto* actor = mActor;
    const sead::Vector3f pos = actor->getMtx().getTranslation();
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    const sead::Vector3f target = sub_71005D9330(actor);
    sead::Vector3f front = target;
    front -= pos;
    front.y = 0.0f;
    const f32 dist = front.normalize();

    f32 chemical_angle = 0.0f;
    if (auto* chemical = actor->getChemicalStuff()) {
        const auto* damage_param = mActor->getParam()->getRes().mDamageParam;
        if (damage_param && damage_param->mBurnable.ref()) {
            if (auto* holder = chemical->_90->_0) {
                sead::Matrix34f mtx;
                mtx.setTranslation(holder->sub_7100D8D1E0());
                sub_71003AD3EC(&angle, front, mtx, true, 6.0f, dist);
                chemical_angle = angle;
            }
        }
    }

    auto* awareness = actor->getAwareness();
    for (s32 i = 0; i < 5; ++i) {
        auto* sensor = awareness->_260[2];
        if (!sensor || sensor->_8.size() <= i)
            break;
        auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, i);
        if (!entry)
            break;
        sub_71003AD3EC(&angle, front, entry->_58, false, 4.0f, dist);
    }
    for (s32 i = 0; i < 10; ++i) {
        if (awareness->_8.size() <= i)
            break;
        auto* entry = ksys::act::sub_7100D78E30(&awareness->_8, i);
        if (!entry)
            break;
        if (ksys::act::isEnemyProfile(&entry->_0.mLink))
            sub_71003AD3EC(&angle, front, entry->_58, false, 2.0f, dist);
    }

    if (!sead::Mathf::equalsEpsilon(chemical_angle, 0.0f) && !(chemical_angle * angle >= 0.0f))
        return -5;
    if (!(sead::Mathf::abs(angle) >= 0.7f))
        return 0;

    const s8 side = angle <= 0.0f ? 1 : -1;
    sead::Vector3f dir = target;
    dir -= pos;
    dir.set(-dir.z, 0.0f, dir.x);
    dir.normalize();
    const sead::Vector3f dest = pos + dir * (*mSpaceDist_s * side);
    if (!sub_710072FAB0(actor, dest, nullptr, -1, -1.0f, -1.0f))
        return 0;
    return side;
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

// NON_MATCHING: getData() selects +8 / null with csel; the original branches (as in sub_71003AB3FC)
void EnemyRangeKeepMove::sub_71003ACB14() {
    if (_f0._0) {
        auto* checker = sead::DynamicCast<Unk_71025b0578>(*_f0._0);
        if (checker && checker->mRefCount >= 1) {
            sead::Vector3f pos;
            mActor->getMtx().getTranslation(pos);
            _f0.getData()->sub_7100716408(pos);
        }
    }
    if (_f8._0) {
        auto* checker = sead::DynamicCast<Unk_71025b7688>(*_f8._0);
        if (checker && checker->mRefCount >= 1)
            _f8.getData()->sub_710071F374(mActor);
    }
}

// NON_MATCHING: same getData() difference as sub_71003AB3FC (the original drops the null check of the re-cast and
// uses the object directly; ours selects +8 / null with csel)
bool EnemyRangeKeepMove::sub_71003ACE4C() {
    if (_f0._0) {
        auto* checker = sead::DynamicCast<Unk_71025b0578>(*_f0._0);
        if (checker && checker->mRefCount >= 1) {
            auto* data = _f0.getData();
            if (data->_78 <= 0.0f || data->sub_71007169CC(0.05f))
                return true;
        }
    }
    if (_f8._0) {
        auto* checker = sead::DynamicCast<Unk_71025b7688>(*_f8._0);
        if (checker && checker->mRefCount >= 1 && _f8.getData()->_c < 1)
            return true;
    }
    return false;
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
