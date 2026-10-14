#include "Game/Actor/AI/aiEnemyRoam.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::ai {

EnemyRoam::EnemyRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void EnemyRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _60 = false;
    changeChild("徘徊待機");
}

void EnemyRoam::loadParams_() {
    getStaticParam(&mSearchPer_s, "SearchPer");
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mMinMoveDist_s, "MinMoveDist");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

// NON_MATCHING: the compiler merges the two identical movement branches and their pack cleanup.
void EnemyRoam::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;
    if (isCurrentChild("徘徊歩行")) {
        if (getCurrentChild()->isFailed())
            _60 = true;
        changeChild("徘徊待機");
        return;
    }
    if (isCurrentChild("徘徊待機")) {
        const s32 search_per = *mSearchPer_s;
        const s32 roll = sead::GlobalRandom::instance()->getU32(100);
        if (search_per > roll) {
            changeToRoamSearch();
            return;
        }
    }
    auto* nav = mActor->m45();
    if (nav && (nav->_2a4 & 0xffff) != 0x17) {
        sead::Vector3f position;
        if (sub_71003B2C0C(&position)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(position, "TargetPos", -1);
            changeChild("徘徊歩行", &pack);
            return;
        }
    }
    changeChild("徘徊待機");
}

// NON_MATCHING: only the operand order of the three final fadds (the original adds `forward * 3` first, ours the translation first; load schedule and registers match)
void EnemyRoam::changeToRoamSearch() {
    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const sead::Vector3f trans = mtx.getTranslation();
    const sead::Vector3f pos = mtx.getBase(2) * 3.0f + trans;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("徘徊探索", &pack);
}

// NON_MATCHING: scheduling and stack copies of the position / direction (logic and calls match).
// Picks the next roam position: around the front direction inside the territory (back towards the centre when outside
// it), StepDist away, pulled back into the territory when it ends up too far; false if it is closer than MinMoveDist.
bool EnemyRoam::sub_71003B2C0C(sead::Vector3f* position) {
    const f32 radius = *mTerritoryRadius_s + *mTerritoryRadiusRnd_s;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir = mActor->getMtx().getBase(2);
    const sead::Vector3f& center = *mCentralPos_d;

    bool rotate = true;
    f32 angle;
    if (!_60) {
        const f32 dx = pos.x - center.x;
        const f32 dz = pos.z - center.z;
        const f32 distance = sead::Vector2f(dx, dz).length();
        if (distance > radius) {
            dir = center - pos;
            dir.normalize();
            rotate = false;
        } else if (distance <= radius * 0.5f) {
            angle = ksys::util::sub_71011EF0CC(sead::GlobalRandom::instance()->getF32()) / 6.0f;
        } else {
            const f32 offset =
                ksys::util::sub_71011EF0CC(sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi()) / 6.0f;
            if (dir.x * dz - dir.z * dx <= 0.0f)
                angle = offset + -0.43633232f;
            else
                angle = offset + 0.43633232f;
        }
    } else {
        angle = sead::Mathf::piHalf();
    }
    if (rotate)
        ksys::util::sub_71011EF010(&dir, angle);

    sead::Vector3f target = pos + dir;
    if (!sub_710072F99C(mActor, pos, target, nullptr, -1, -1.0f, -1.0f))
        dir = -dir;

    target = pos;
    const f32 step = (*mTerritoryRadius_s +
                      sead::GlobalRandom::instance()->getF32Range(0.0f, *mTerritoryRadiusRnd_s)) *
                     0.9f;
    target += dir * step;
    sead::Vector3f hit;
    if (!sub_710072F99C(mActor, pos, target, &hit, -1, -1.0f, -1.0f))
        target = hit;

    sead::Vector3f diff = target - center;
    const f32 distance = sead::Vector2f(diff.x, diff.z).length();
    diff.normalize();
    if (distance > radius) {
        const f32 back = radius * (sead::GlobalRandom::instance()->getF32() * 0.39999998f + 0.5f);
        sead::Vector3f candidate = diff * back;
        candidate += center;
        sead::Vector3f candidate_hit;
        if (sub_710072F99C(mActor, pos, candidate, &candidate_hit, -1, -1.0f, -1.0f)) {
            target = candidate;
        } else if (distance > radius * 1.2f &&
                   sead::Vector2f(candidate_hit.x - center.x, candidate_hit.z - center.z).length() <
                       radius * 0.9f) {
            target = candidate_hit;
        }
    }
    *position = target;
    return (pos - target).length() >= *mMinMoveDist_s;
}

}  // namespace uking::ai
