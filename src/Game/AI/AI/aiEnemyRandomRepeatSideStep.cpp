#include "Game/AI/AI/aiEnemyRandomRepeatSideStep.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRandomRepeatSideStep::EnemyRandomRepeatSideStep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRandomRepeatSideStep::~EnemyRandomRepeatSideStep() = default;

void EnemyRandomRepeatSideStep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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

}  // namespace uking::ai
