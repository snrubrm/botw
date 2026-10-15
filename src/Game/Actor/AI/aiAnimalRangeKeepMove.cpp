#include "Game/Actor/AI/aiAnimalRangeKeepMove.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"

namespace uking::ai {

AnimalRangeKeepMove::AnimalRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRangeKeepMove::~AnimalRangeKeepMove() = default;

bool AnimalRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: register numbering of the target z load in the two distance computations (s3 in the original).
void AnimalRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 min_time = *mBattleEndTimerMin_s;
    const s32 max_time = *mBattleEndTimerMax_s;
    _74 = sead::Mathi::min(min_time, max_time);
    _78 = sead::Mathi::max(min_time, max_time);
    _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);
    _7c = sub_71005D9330(mActor);

    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_7c, "TargetPos", -1);
        changeChild("離脱", &pack);
        return;
    }

    const auto getDistance = [this] {
        auto* actor = mActor;
        const auto& target = sub_71005D9330(actor);
        const sead::Vector3f& pos = actor->getMtx().getTranslation();
        return sead::Vector3f(target.x - pos.x, 0.0f, target.z - pos.z).length();
    };
    if (!(getDistance() > *mCloseStartDist_s)) {
        if (!(getDistance() < *mLeaveEndDist_s)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_7c, "TargetPos", -1);
            changeChild("通常行動", &pack);
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_7c, "TargetPos", -1);
            changeChild("離脱", &pack);
        }
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_7c, "TargetPos", -1);
        changeChild("接近", &pack);
    }
}

// NON_MATCHING: source shares the native transition parameter-pack construction and cleanup.
void AnimalRangeKeepMove::calc_() {
    auto* child = getCurrentChild();
    const auto getDistance = [this] {
        auto* actor = mActor;
        const auto& target = sub_71005D9330(actor);
        const auto position = actor->getMtx().getTranslation();
        return sead::Vector3f(target.x - position.x, 0.0f, target.z - position.z).length();
    };
    // An unordered distance also refreshes the battle-end timer.
    if (!(getDistance() > *mBattleEndDist_s))
        _70 = _74 == _78 ? _74 : sead::GlobalRandom::instance()->getS32Range(_74, _78);
    else
        ksys::Timer::update(&_70, -1.0f);
    if (_70 <= 0.0f) {
        setFailed();
        return;
    }
    _7c = sub_71005D9330(mActor);
    child->setDynamicParam(_7c, "TargetPos");
    const char* next_child = nullptr;
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("旋回")) {
            next_child = "離脱";
        } else if (isCurrentChild("接近")) {
            next_child = "通常行動";
        } else if (isCurrentChild("離脱")) {
            next_child = getDistance() > *mCloseStartDist_s ? "接近" : "通常行動";
        } else if (child->isFinished()) {
            setFinished();
            return;
        } else {
            next_child = "通常行動";
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("通常行動")) {
            if (_70 <= 0.0f) {
                setFailed();
                return;
            }
            if (getDistance() > *mCloseStartDist_s)
                next_child = "接近";
            else if (getDistance() < *mLeaveStartDist_s)
                next_child = "離脱";
        } else if (isCurrentChild("接近")) {
            if (_70 <= 0.0f) {
                setFailed();
                return;
            }
            if (getDistance() < *mCloseEndDist_s)
                next_child = "通常行動";
        } else if (isCurrentChild("離脱")) {
            if (getDistance() > *mLeaveEndDist_s)
                next_child = "通常行動";
        }
    }
    if (next_child) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_7c, "TargetPos", -1);
        changeChild(next_child, &pack);
    }
}

bool AnimalRangeKeepMove::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable();
}

void AnimalRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRangeKeepMove::loadParams_() {
    getStaticParam(&mBattleEndTimerMin_s, "BattleEndTimerMin");
    getStaticParam(&mBattleEndTimerMax_s, "BattleEndTimerMax");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getStaticParam(&mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
}

}  // namespace uking::ai
