#include "Game/AI/AI/aiEnemyMoveToGround.h"
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71005E11AC.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyMoveToGround::EnemyMoveToGround(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyMoveToGround::~EnemyMoveToGround() = default;

bool EnemyMoveToGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyMoveToGround::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.mTimer.reset(*mRetryTime_s);
    _50 = 2;
    if (sub_710039A2B8()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_70, "TargetPos", -1);
        changeChild("発見", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("未発見", &pack);
    }
}

bool EnemyMoveToGround::sub_710039A2B8() {
    auto* info = sub_71005E2BCC(mActor);
    if (!info)
        return false;

    sead::Vector3f target{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                          std::numeric_limits<f32>::quiet_NaN()};
    if (_50 == 2 && sub_71005D8F28(mActor)) {
        target = sub_71005D9330(mActor);
        _50 = 0;
    } else {
        _50 = 2;
    }
    if (!sub_71005E11AC(&_70, mActor, &target, *mSearchRadius_s, *mAreaThreshold_s))
        return false;
    if (sub_710072E154(mActor, _70, nullptr, -1))
        return true;

    _50 = _50 != 0 ? 3 : 1;
    if (info->_0) {
        info->_0->sub_7100F75F8C(_70);
        info->_8 = 0;
    }
    return false;
}

// NON_MATCHING: the original loads the child's vtable in the predecessors of the second `child->isFailed()` call
// (hoisted above the `isFinished() ||` branch); ours loads it in the join block. Everything else matches.
void EnemyMoveToGround::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!child->isFailed()) {
            if (!isCurrentChild("発見")) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("未発見", &pack);
            } else {
                if (auto* info = sub_71005E2BCC(mActor)) {
                    if (auto* nav = info->_0)
                        nav->inlineReset();
                }
                setFinished();
            }
        } else {
            if (auto* info = sub_71005E2BCC(mActor)) {
                if (auto* nav = info->_0)
                    nav->inlineReset();
            }
            setFailed();
        }
        return;
    }

    if (child->isChangeable() && isCurrentChild("未発見")) {
        if (auto* info = sub_71005E2BCC(mActor)) {
            if (_50 == 1) {
                if ((info->_8 | 2) == 3) {
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(_70, "TargetPos", -1);
                    changeChild("発見", &pack);
                } else if (info->_8 != 0) {
                    _50 = 0;
                    _58.mTimer.reset(*mRetryTime_s);
                }
            } else if (_50 == 3) {
                if ((info->_8 | 2) == 3) {
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(_70, "TargetPos", -1);
                    changeChild("発見", &pack);
                } else if (info->_8 != 0) {
                    _50 = 2;
                    _58.mTimer.reset(*mRetryTime_s);
                }
            } else {
                if (_58.mTimer.value <= sead::Mathf::epsilon() && sub_710039A2B8()) {
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(_70, "TargetPos", -1);
                    changeChild("発見", &pack);
                    return;
                }
            }
        }
    }

    if (!isCurrentChild("未発見"))
        return;
    if ((_50 | 2) == 2)
        _58.sub_7100D3BCE4();
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void EnemyMoveToGround::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyMoveToGround::loadParams_() {
    getStaticParam(&mRetryTime_s, "RetryTime");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mSearchRadius_s, "SearchRadius");
}

}  // namespace uking::ai
