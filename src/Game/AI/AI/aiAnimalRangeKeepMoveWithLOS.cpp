#include "Game/AI/AI/aiAnimalRangeKeepMoveWithLOS.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/System/Timer.h"

bool sub_7100742738(sead::Vector3f* out, uking::act::WolfLink* wolf, f32 value);

namespace uking::ai {

// inline-only in the original; name is a guess. Evidence: `state - 2 < 6 && state != 4` on the result of
// WolfLink::sub_71002F440C repeats six times in sub_7100309D40 / sub_710030A1E0 (each with a stack round trip).
static bool isTravellingState(u32 state) {
    return state >= 2 && state < 8 && state != 4;
}

AnimalRangeKeepMoveWithLOS::AnimalRangeKeepMoveWithLOS(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AnimalRangeKeepMoveWithLOS::~AnimalRangeKeepMoveWithLOS() = default;

bool AnimalRangeKeepMoveWithLOS::init_(sead::Heap* heap) {
    _a0 = sead::DynamicCast<act::WolfLink>(mActor);
    return _a0 != nullptr;
}

void AnimalRangeKeepMoveWithLOS::sub_7100309620() {
    if (!isFailed() && !isCurrentChild("パス検索")) {
        mFlags.reset(Flag::Changeable);
        _78 = _7c == _80 ? _7c : sead::GlobalRandom::instance()->getS32Range(_7c, _80);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_90, "TargetPos", -1);
        changeChild("パス検索", &pack);
    }
}

void AnimalRangeKeepMoveWithLOS::sub_7100309768() {
    if (!isFailed() && !isCurrentChild("接近")) {
        mFlags.reset(Flag::Changeable);
        _78 = _7c == _80 ? _7c : sead::GlobalRandom::instance()->getS32Range(_7c, _80);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_90, "TargetPos", -1);
        changeChild("接近", &pack);
    }
}

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

bool AnimalRangeKeepMoveWithLOS::sub_7100309A88() {
    if (auto* nav = _a0->m45()) {
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state != 3)
            return true;
        nav->inlineReset();
        nav->_1e0.lock();
        const u8 sub_state = nav->_296;
        nav->_1e0.unlock();
        if (sub_state != 3)
            return false;
        _a0->sub_71002F4008(&_a0->_c48._8, 3);
        _ac = true;
        _a0->sub_71002F493C();
    }
    setFailed();
    return false;
}

void AnimalRangeKeepMoveWithLOS::sub_7100309BAC() {
    getCurrentChild();
    if (isCurrentChild("パス検索") || isCurrentChild("接近")) {
        auto* nav = _a0->m45();
        if (!nav) {
            setFailed();
            return;
        }
        nav->_1e0.lock();
        const u8 state = nav->_294;
        nav->_1e0.unlock();
        if (state == 1) {
            if (!_ad) {
                _a0->sub_71002F4008(&_a0->_c48._8, 4);
                _ac = true;
            } else {
                _84 = _88 == _8c ? _88 : sead::GlobalRandom::instance()->getS32Range(_88, _8c);
                _78 = _7c == _80 ? _7c : sead::GlobalRandom::instance()->getS32Range(_7c, _80);
            }
        } else {
            nav->_1e0.lock();
            const u8 sub_state = nav->_296;
            nav->_1e0.unlock();
            if (sub_state == 2)
                _a0->sub_71002F4008(&_a0->_c48._8, 7);
            else
                _a0->sub_71002F4008(&_a0->_c48._8, 3);
            _ac = true;
            setFailed();
        }
    }
    sub_710030A1E0();
}

// NON_MATCHING: the original keeps the WolfLink state in an enum local (stack round trip, `(state - 2) < 6 &&
// ((state - 2) & 0x3f) != 2`)
void AnimalRangeKeepMoveWithLOS::sub_710030A1E0() {
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        _a8 <= *mLeaveEndDist_s * *mLeaveEndDist_s) {
        mFlags.set(Flag::Changeable);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_90, "TargetPos", -1);
        changeChild("離脱", &pack);
        return;
    }
    bool normal = false;
    if (_ac) {
        const u32 state = _a0->sub_71002F440C();
        if (state >= 2 && state < 8 && state != 4)
            normal = true;
    }
    if (!normal) {
        if (_a8 > *mCloseStartDist_s * *mCloseStartDist_s) {
            sub_7100309768();
            return;
        }
    }
    mFlags.set(Flag::Changeable);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_90, "TargetPos", -1);
    changeChild("通常行動", &pack);
}

// NON_MATCHING: the original keeps the WolfLink state in an enum local (stack round trip) and the branches are laid
// out differently
void AnimalRangeKeepMoveWithLOS::sub_7100309D40() {
    if (_84 <= 0.0f) {
        if (!_ac || !isTravellingState(_a0->sub_71002F440C())) {
            sub_7100309620();
            return;
        }
    }
    if (!_ac && _78 <= 0.0f) {
        _a0->sub_71002F4008(&_a0->_c48._8, 2);
        _ac = true;
        return;
    }
    if (!isCurrentChild("通常行動")) {
        if (isCurrentChild("離脱")) {
            if (sub_7100742738(nullptr, _a0, -1.0f)) {
                if (_a8 <= *mLeaveEndDist_s * *mLeaveEndDist_s)
                    return;
                mFlags.set(Flag::Changeable);
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_90, "TargetPos", -1);
                changeChild("通常行動", &pack);
                return;
            }
        } else if (isCurrentChild("接近")) {
            if (sub_7100742738(nullptr, _a0, -1.0f)) {
                if (!(_ac && isTravellingState(_a0->sub_71002F440C())) &&
                    *mCloseEndDist_s * *mCloseEndDist_s <= _a8)
                    return;
                mFlags.set(Flag::Changeable);
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_90, "TargetPos", -1);
                changeChild("通常行動", &pack);
                return;
            }
        } else if (isCurrentChild("パス検索")) {
            if (sub_7100742738(nullptr, _a0, -1.0f)) {
                if (!_ad || !_ac || !isTravellingState(_a0->sub_71002F440C()))
                    return;
                sub_710030A1E0();
                return;
            }
        } else {
            return;
        }
        mFlags.reset(Flag::Changeable);
        changeChild("崖である", nullptr);
        return;
    }
    if (!(_ac && isTravellingState(_a0->sub_71002F440C())) &&
        _a8 > *mCloseStartDist_s * *mCloseStartDist_s) {
        sub_7100309768();
        return;
    }
    if (_a8 < *mLeaveStartDist_s * *mLeaveStartDist_s) {
        mFlags.set(Flag::Changeable);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_90, "TargetPos", -1);
        changeChild("離脱", &pack);
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
