#include "Game/AI/AI/aiAnimalRangeKeepMoveWithLOS.h"
#include "Game/Actor/actWolfLink.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

AnimalRangeKeepMoveWithLOS::AnimalRangeKeepMoveWithLOS(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AnimalRangeKeepMoveWithLOS::~AnimalRangeKeepMoveWithLOS() = default;

bool AnimalRangeKeepMoveWithLOS::init_(sead::Heap* heap) {
    _a0 = sead::DynamicCast<act::WolfLink>(mActor);
    return _a0 != nullptr;
}

// NON_MATCHING: State range branching and load scheduling differ.
void AnimalRangeKeepMoveWithLOS::enter_(ksys::act::ai::InlineParamPack*) {
    _7c = _80 = *mNoPathTimer_s;
    _78 = f32(_7c);
    _88 = _8c = *mFindPathBeginTimer_s;
    _84 = f32(_88);
    _ac = _a0->sub_71002F420C();
    _90 = _a0->_c48._18;
    _a8 = sead::Vector2f(_a0->_c48._18.x - _a0->getMtx().getTranslation().x,
                         _a0->_c48._18.z - _a0->getMtx().getTranslation().z).squaredLength();
    _ad = (_a0->_1698 & (1 << 13)) != 0;
    if (_ad) {
        sub_7100309768();
    } else {
        if (_ac) {
            const u32 state = _a0->sub_71002F440C();
            if (state >= 2 && state < 8 && state != 4) {
                sub_7100309768();
                return;
            }
        }
        sub_7100309620();
    }
}

bool AnimalRangeKeepMoveWithLOS::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable();
}

void AnimalRangeKeepMoveWithLOS::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: load scheduling and timer-address register reuse differ.
void AnimalRangeKeepMoveWithLOS::calc_() {
    auto* child = getCurrentChild();
    if (!child)
        return;
    _90 = sub_71005D9330(mActor);
    child->setDynamicParam(_90, "TargetPos");
    _ac = _a0->sub_71002F420C();
    _a8 = sead::Vector2f(_a0->_c48._18.x - _a0->getMtx().getTranslation().x,
                        _a0->_c48._18.z - _a0->getMtx().getTranslation().z).squaredLength();
    _ad = (_a0->_1698 & 0x2000) != 0;
    if (_ac || !(_84 <= 0.0f))
        _78 = _7c == _80 ? _7c : sead::GlobalRandom::instance()->getS32Range(_7c, _80);
    else
        ksys::Timer::update(&_78, -1.0f);
    if (_ac || _ad)
        _84 = _88 == _8c ? _88 : sead::GlobalRandom::instance()->getS32Range(_88, _8c);
    else
        ksys::Timer::update(&_84, -1.0f);
    if (sub_7100309A88()) {
        if (child->isFinished() || child->isFailed())
            sub_7100309BAC();
        else
            sub_7100309D40();
    }
}

void AnimalRangeKeepMoveWithLOS::loadParams_() {
    getStaticParam(&mFindPathBeginTimer_s, "FindPathBeginTimer");
    getStaticParam(&mNoPathTimer_s, "NoPathTimer");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getStaticParam(&mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
    getStaticParam(&mDistFailOnUnreachablePath_s, "DistFailOnUnreachablePath");
}

}  // namespace uking::ai
