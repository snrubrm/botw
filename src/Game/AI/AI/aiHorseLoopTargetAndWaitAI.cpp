#include "Game/AI/AI/aiHorseLoopTargetAndWaitAI.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "Game/gameWildHorseMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

HorseLoopTargetAndWaitAI::HorseLoopTargetAndWaitAI(const InitArg& arg) : HorseLoopTarget(arg) {}

HorseLoopTargetAndWaitAI::~HorseLoopTargetAndWaitAI() = default;

bool HorseLoopTargetAndWaitAI::init_(sead::Heap* heap) {
    return HorseLoopTarget::init_(heap);
}

// NON_MATCHING: only the operand order of the BitFlag8 {and,or} differs (original: `flags op mask`, ours: `mask op flags`)
void HorseLoopTargetAndWaitAI::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseLoopTarget::enter_(params);
    _18c.makeAllZero();
    if (auto* mgr = WildHorseMgr::instance()) {
        if (!mgr->mBusy.compareExchange(0, 1)) {
            changeChild("待機", nullptr);
            return;
        }
        _18c.setBit(Flag(Flag::_0));
    }
    sub_7100E5CA78(true);
}

// NON_MATCHING: the BitFlag8 {and,or} operand order (original: `flags op mask`, ours: `mask op flags`) and the stack slots of
// the three SEAD_ENUM temporaries (the original's setBit temporary sits above the isOnBit one)
void HorseLoopTargetAndWaitAI::calc_() {
    auto* child = getCurrentChild();
    const char* name = child->getName();
    auto* mgr = WildHorseMgr::instance();
    if (sead::SafeString(name) == "待機") {
        ksys::Timer::update(&_188, -1.0f);
        if (child->isFinished() || child->isFailed() || (child->isChangeable() && _188 < 0.0f)) {
            if (mgr && !_18c.isOnBit(Flag(Flag::_0))) {
                if (!mgr->mBusy.compareExchange(0, 1)) {
                    if (child->isFinished() || child->isFailed()) {
                        changeChild("待機", nullptr);
                    } else {
                        const f32 min = *mMinWaitTime_s;
                        const f32 max = *mMaxWaitTime_s;
                        _188 = sead::GlobalRandom::instance()->getF32Range(min, max);
                    }
                    return;
                }
                _18c.setBit(Flag(Flag::_0));
            }
            sub_7100E5CA78(false);
        }
    } else if (child->isFinished() || child->isFailed()) {
        if (sead::GlobalRandom::instance()->getF32() < *mChangeWaitRate_s) {
            if (mgr) {
                _18c.resetBit(Flag(Flag::_0));
                mgr->mBusy = 0;
            }
            changeChild("待機", nullptr);
            const f32 min = *mMinWaitTime_s;
            const f32 max = *mMaxWaitTime_s;
            _188 = sead::GlobalRandom::instance()->getF32Range(min, max);
            return;
        }
        sub_7100E5CA78(false);
    }
}

void HorseLoopTargetAndWaitAI::sub_7100E5CA78(bool enter) {
    ksys::act::ai::InlineParamPack pack;
    sub_710127FF2C();
    if (enter) {
        if (auto* rideable = mActor->getHorseOptionsMaybe())
            rideable->sub_7100E63224(0, 0);
        if (auto* nav = mActor->m45())
            nav->inlineReset();
    }
    pack.addVec3(sub_710127FFD8(), "TargetPos", -1);
    changeChild("指定位置に移動", &pack);
}

ksys::map::Rail* HorseLoopTargetAndWaitAI::m34() {
    if (auto* horse = sead::DynamicCast<uking::act::HorseBase>(mActor))
        return horse->_b40;
    return HorseLoopTarget::m34();
}

bool HorseLoopTargetAndWaitAI::handleMessage_(const ksys::Message* message) {
    return false;
}

// NON_MATCHING: only the operand order of the BitFlag8 {and,or} differs (original: `flags op mask`, ours: `mask op flags`)
void HorseLoopTargetAndWaitAI::leave_() {
    if (_18c.isOnBit(Flag(Flag::_0))) {
        if (auto* mgr = WildHorseMgr::instance())
            mgr->mBusy = 0;
    }
}

void HorseLoopTargetAndWaitAI::loadParams_() {
    HorseLoopTarget::loadParams_();
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mMaxWaitTime_s, "MaxWaitTime");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
}

}  // namespace uking::ai
