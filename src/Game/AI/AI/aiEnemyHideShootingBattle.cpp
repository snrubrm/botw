#include "Game/AI/AI/aiEnemyHideShootingBattle.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyHideShootingBattle::EnemyHideShootingBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHideShootingBattle::~EnemyHideShootingBattle() = default;

void EnemyHideShootingBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    const sead::Vector3f target_pos = *mTargetPos_d;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("隠れる", &pack);
}

// inline-only in the original (the same sequence appears twice in calc_); name is a guess.
inline void EnemyHideShootingBattle::changeToBattle() {
    _40 = false;
    _44 = ksys::Timer(15.0f, 15.0f);
    ksys::act::ai::InlineParamPack pack;
    const sead::Vector3f target_pos = *mTargetPos_d;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("戦闘", &pack);
}

void EnemyHideShootingBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("隠れる")) {
            if (getCurrentChild()->isFinished())
                changeToBattle();
            else
                setFailed();
        } else if (isCurrentChild("戦闘")) {
            if (_40) {
                if (getCurrentChild()->isFinished()) {
                    changeToBattle();
                } else {
                    setFailed();
                }
            } else {
                sub_71005D8E9C(mActor);
                setFailed();
            }
        }
    } else if (isCurrentChild("戦闘")) {
        if (sub_710072E1B4(mActor, true)) {
            _40 = true;
            if (getCurrentChild()->isChangeable()) {
                _44.update();
                if (_44.value <= sead::Mathf::epsilon())
                    setFinished();
            }
        } else {
            _44 = ksys::Timer(15.0f, 15.0f);
        }
    }
}

bool EnemyHideShootingBattle::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyHideShootingBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyHideShootingBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHideShootingBattle::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
