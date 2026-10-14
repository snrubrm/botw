#include "Game/Actor/AI/aiEnemyRandomRepeatSideStep.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRandomRepeatSideStep::EnemyRandomRepeatSideStep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRandomRepeatSideStep::~EnemyRandomRepeatSideStep() = default;

// NON_MATCHING: the output position and parameter pack have different stack placement.
void EnemyRandomRepeatSideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    _7c.reset(5.0f);
    const s32 max = *mMaxRepeatNum_s;
    if (max >= 1) {
        const s32 min = *mMinRepeatNum_s;
        if (max > min)
            _78 = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        else
            _78 = 0;
    } else {
        _78 = 0;
    }

    sead::Vector3f pos;
    if (_78 > 0 && sub_71003AA3E0(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("サイドステップ", &pack);
    } else {
        changeChild("待機");
        setFailed();
    }
}

// NON_MATCHING: only the stack slot order (the original has `pos` at the bottom, then the "TargetPos" SafeString,
// then the pack / isCurrentChild string group; ours puts `pos` above the pack) and the load order of the XZ
// distance (actor x before target x)
void EnemyRandomRepeatSideStep::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("サイドステップ")) {
            if (auto* actor = mActor) {
                const sead::Matrix34f& mtx = actor->getMtx();
                const f32 dist =
                    sead::Vector2f(mTargetPos_d->x - mtx(0, 3), mTargetPos_d->z - mtx(2, 3)).length();
                if (dist >= *mBaseDist_s + *mOutDist_s + sub_71007320F0(actor, *mWeaponIdx_s)) {
                    setFailed();
                    return;
                }
            }

            if (--_78 <= 0) {
                setFinished();
                return;
            }

            sead::Vector3f pos;
            if (sub_71003AA3E0(&pos)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(pos, "TargetPos", -1);
                changeChild("サイドステップ", &pack);
            } else {
                setFailed();
            }
        }
    }
}

bool EnemyRandomRepeatSideStep::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyRandomRepeatSideStep::loadParams_() {
    getStaticParam(&mMinRepeatNum_s, "MinRepeatNum");
    getStaticParam(&mMaxRepeatNum_s, "MaxRepeatNum");
    getStaticParam(&mStepDist_s, "StepDist");
    getStaticParam(&mStepAngle_s, "StepAngle");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool EnemyRandomRepeatSideStep::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (_78 <= 1 && isCurrentChild("サイドステップ"))
        return getCurrentChild()->isFinished();
    return false;
}

// NON_MATCHING: operand order of the axis scale (ours: angle * ey via sead::Vector3CalcCommon<f32>::multScalar) and the
// resulting scheduling / register allocation.
bool EnemyRandomRepeatSideStep::sub_71003AA3E0(sead::Vector3f* out) {
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    front.y = 0.0f;
    front.normalize();

    sead::Vector3f dirs[2];
    const sead::Vector3f axis = sead::Vector3f::ey * *mStepAngle_s;
    sead::Matrix34f rot;
    rot.makeR(axis);
    dirs[0].setRotated(rot, front);
    dirs[0].normalize();
    rot.makeR(-axis);
    dirs[1].setRotated(rot, front);
    dirs[1].normalize();

    bool ok[2] = {true, true};
    sead::Vector3f targets[2];
    for (s32 i = 0; i < 2; ++i) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        targets[i] = pos + dirs[i] * *mStepDist_s;
        if (!sub_710072F99C(mActor, mActor->getMtx().getTranslation(), targets[i], nullptr, -1, -1.0f,
                            -1.0f)) {
            ok[i] = false;
            continue;
        }
        auto* awareness = mActor->getAwareness();
        if (!awareness)
            continue;
        Unk_7102451448 filter;
        while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
            const sead::Vector3f diff = entry->_58.getTranslation() - pos;
            sead::Vector3f dir(diff.x, 0.0f, diff.z);
            dir.normalize();
            if (!(sead::Mathf::abs(diff.y) <= 3.0f))
                continue;
            const f32 dot = dir.dot(dirs[i]);
            const f32 distance = sead::Vector2f(diff.x, diff.z).length();
            if (dot >= 0.0f && distance <= *mStepDist_s + *mStepDist_s) {
                ok[i] = false;
                break;
            }
        }
    }

    if (ok[0]) {
        *out = targets[0];
        if (!ok[1] || s32(sead::GlobalRandom::instance()->getU32()) >= 0)
            return true;
    } else if (!ok[1]) {
        return false;
    }
    *out = targets[1];
    return true;
}

}  // namespace uking::ai
