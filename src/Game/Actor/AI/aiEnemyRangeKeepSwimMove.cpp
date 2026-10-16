#include "Game/Actor/AI/aiEnemyRangeKeepSwimMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRangeKeepSwimMove::EnemyRangeKeepSwimMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepSwimMove::~EnemyRangeKeepSwimMove() = default;

bool EnemyRangeKeepSwimMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original loads both target components before the two subtractions (scheduling only).
void EnemyRangeKeepSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 time = sead::GlobalRandom::instance()->getS32Range(8, 20);
    _84 = ksys::Timer(time, time);

    sead::Vector3f diff = sub_71005D9330(mActor) - mActor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 distance = diff.length();
    if (!(distance > *mBaseDist_s + *mFarDist_s + sub_71007320F0(mActor, *mWeaponIdx_s))) {
        sead::Vector3f diff2 = sub_71005D9330(mActor) - mActor->getMtx().getTranslation();
        diff2.y = 0.0f;
        const f32 distance2 = diff2.length();
        if (!(distance2 < *mBaseDist_s + *mCloseDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)) ||
            sub_71003ADEE4()) {
            const s8 dir = sub_71003AE028();
            if (dir == 0) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("戦闘待機", &pack);
            } else {
                changeToMoveSideways(dir);
            }
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("戦闘後ずさり", &pack);
        }
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("戦闘歩行", &pack);
    }

    const s32 limit = *mTime_s;
    _90 = ksys::Timer(limit, limit);
}

// NON_MATCHING: register numbering of the XZ offset (x/z swap the roles of s11/s12 after the normalisation)
bool EnemyRangeKeepSwimMove::sub_71003ADEE4() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& player = sub_71005D9330(mActor);
    sead::Vector3f dir = pos - player;
    dir.y = 0;
    dir.normalize();
    sead::Vector3f target;
    target.setScaleAdd(5.0f, dir, pos);
    if (!sub_710072F8E4(mActor, target, nullptr, 3.0f))
        return true;
    auto result = ksys::phys::HavokAI::instance()->sub_7100F87ED0(nullptr, target, 3.0f);
    if (result.sub_7100F7EB40() && result.sub_7100F7EEE4() != 6)
        return true;
    return false;
}

// NON_MATCHING: the original loads both actor and player XZ before the first fsub
// NON_MATCHING: scheduling of the two subtractions in the distance checks (as in sub_71003AED8C)
void EnemyRangeKeepSwimMove::calc_() {
    _90.update();
    sub_71003AED8C();
    if (_84.value <= sead::Mathf::epsilon()) {
        setFailed();
        return;
    }
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");

    const auto isFar = [this] {
        const sead::Vector3f& player = sub_71005D9330(mActor);
        const f32 x = mActor->getMtx().m[0][3];
        const f32 z = mActor->getMtx().m[2][3];
        const sead::Vector3f diff(player.x - x, 0, player.z - z);
        const f32 dist = diff.length();
        return dist > *mBaseDist_s + *mFarDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
    };
    const auto changeTo = [this](const char* name) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild(name, &pack);
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘歩行")) {
            if (getCurrentChild()->isFailed()) {
                setFailed();
                return;
            }
            sub_71003AEE84();
            if (_78.value <= sead::Mathf::epsilon()) {
                changeTo("戦闘後ずさり");
            } else {
                const s8 dir = sub_71003AE028();
                if (dir != 0)
                    changeToMoveSideways(dir);
                else
                    changeTo("戦闘待機");
            }
        } else if (isCurrentChild("戦闘後ずさり")) {
            if (isFar())
                changeTo("戦闘歩行");
            else
                changeTo("戦闘待機");
        } else {
            changeTo("戦闘待機");
        }
        return;
    }

    if (isCurrentChild("戦闘待機")) {
        sub_71003AEE84();
    } else if (isCurrentChild("戦闘歩行")) {
        sub_71003AED8C();
        sub_71003AEE84();
    } else if (isCurrentChild("横移動")) {
        getCurrentChild()->setDynamicParam(s32(sub_71003AE028()), "RotDir");
    }

    if (!getCurrentChild()->isChangeable())
        return;

    if (*mTime_s >= 0 && _90.value <= sead::Mathf::epsilon())
        setFinished();

    if (isCurrentChild("戦闘待機")) {
        if (isFar()) {
            changeTo("戦闘歩行");
        } else if (_78.value <= sead::Mathf::epsilon()) {
            changeTo("戦闘後ずさり");
        } else {
            const s8 dir = sub_71003AE028();
            if (dir != 0)
                changeToMoveSideways(dir);
        }
    } else if (isCurrentChild("戦闘歩行")) {
        if (_84.value <= sead::Mathf::epsilon())
            setFailed();
    } else if (isCurrentChild("横移動")) {
        if (sub_71003AE028() == 0)
            changeTo("戦闘待機");
    }
}

void EnemyRangeKeepSwimMove::sub_71003AED8C() {
    const sead::Vector3f& player = sub_71005D9330(mActor);
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    const sead::Vector3f diff(player.x - x, 0, player.z - z);
    const f32 dist = diff.length();
    if (dist > *mBaseDist_s + *mOutDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)) {
        if (_84.value > sead::Mathf::epsilon())
            _84.update();
    } else {
        _84.reset(s32(sead::GlobalRandom::instance()->getU32(7)) + 4);
    }
}

// NON_MATCHING: same load order as sub_71003AED8C
void EnemyRangeKeepSwimMove::sub_71003AEE84() {
    const sead::Vector3f& player = sub_71005D9330(mActor);
    const sead::Vector3f diff(player.x - mActor->getMtx().m[0][3], 0, player.z - mActor->getMtx().m[2][3]);
    const f32 dist = diff.length();
    if (!(dist < *mBaseDist_s + *mCloseDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)) || sub_71003ADEE4()) {
        _78.reset(s32(sead::GlobalRandom::instance()->getU32(15)) + 15);
    } else if (_78.value > sead::Mathf::epsilon()) {
        _78.update();
    }
}

void EnemyRangeKeepSwimMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRangeKeepSwimMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
}

// NON_MATCHING: vector copies, gravity normalization scheduling and loop comparison order differ.
s8 EnemyRangeKeepSwimMove::sub_71003AE028() {
    auto gravity = getGravity(mActor);
    const auto origin = mActor->getMtx().getTranslation();
    auto target_direction = sub_71005D9330(mActor) - origin;
    target_direction.normalize();
    gravity *= 1.0f / 900.0f;
    const auto& entries = mActor->getAwareness()->_8;
    s8 balance = 0;
    for (s32 i = 0; i < 5 && i < entries.size(); ++i) {
        auto* entry = ksys::act::sub_7100D78E30(&entries, i);
        if (!entry)
            break;
        if (!ksys::act::isEnemyProfile(&entry->_0.mLink))
            continue;
        if (entry->_a8 > *mSpaceDist_s)
            break;
        auto offset = entry->_58.getTranslation() - origin;
        const auto up = getUpDir(gravity);
        ksys::util::sub_71011EFA00(&offset, offset, up);
        const f32 cross = target_direction.x * offset.z - target_direction.z * offset.x;
        balance = s8(f32(balance) + (cross > 0.0f ? entry->_a8 : -entry->_a8));
    }
    if (balance == 0)
        return 0;
    const s8 side = balance > 0 ? -1 : 1;
    const auto& target = sub_71005D9330(mActor);
    sead::Vector3f direction(-(target.z - origin.z), 0.0f, target.x - origin.x);
    direction.normalize();
    direction *= f32(side);
    const auto destination = direction * *mSpaceDist_s + origin;
    if (*mIsCheckCliff_s && sub_710072FEC4(mActor, destination, 2.0f, nullptr, true, nullptr))
        return 0;
    if (sub_710072EA18(origin, destination, 0, nullptr, nullptr, nullptr, 0.1f))
        return 0;
    return side;
}

void EnemyRangeKeepSwimMove::changeToMoveSideways(s8 dir) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addInt(dir, "RotDir", -1);
    changeChild("横移動", &pack);
}

}  // namespace uking::ai
