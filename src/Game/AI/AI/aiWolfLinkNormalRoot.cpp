#include "Game/AI/AI/aiWolfLinkNormalRoot.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_7100742478.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

namespace {
// Inline-only in the original: NavMeshCharacter's state byte (+0x294) read under its lock.
u8 getNavState(ksys::phys::NavMeshCharacter* nav) {
    nav->_1e0.lock();
    const u8 state = nav->_294;
    nav->_1e0.unlock();
    return state;
}

// Inline-only in the original: the by-value index parameter gives the enum temporaries lifetime markers
// (they share one stack slot).
void setTimerRate(act::WolfLink* wolf, act::WolfLink::Idx14f8 idx, f32 rate) {
    wolf->_14f8[idx].rate = rate;
}

bool isFinishedOrFailed(ksys::act::ai::ActionBase* child) {
    return child->isFinished() || child->isFailed();
}

// Same for reading a timer's current value.
f32 getTimerValue(act::WolfLink* wolf, act::WolfLink::Idx14f8 idx) {
    return wolf->_14f8[idx].value;
}
}  // namespace

WolfLinkNormalRoot::WolfLinkNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkNormalRoot::~WolfLinkNormalRoot() = default;

bool WolfLinkNormalRoot::init_(sead::Heap* heap) {
    _1b8 = 0;
    _1b9 = 0;
    _70 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_70)
        return false;

    const auto* param = _70->getParam();
    if (!param)
        return false;
    const auto* gparams = param->getRes().mGParamList;
    if (!gparams)
        return false;
    _78 = gparams->getWolfLink();
    if (!_78)
        return false;

    _80 = mActor->getAwareness();
    return _80 != nullptr;
}

// NON_MATCHING: the player-position z store is scheduled after the actor-matrix loads in the original, and
// `_184` is copied after `_190` is written (store/load pairing differs by one instruction)
void WolfLinkNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    using Idx = act::WolfLink::Idx14f8;
    setTimerRate(_70, Idx(Idx::_2), -1.0f);
    setTimerRate(_70, Idx(Idx::_1), -1.0f);
    setTimerRate(_70, Idx(Idx::_0), -1.0f);
    setTimerRate(_70, Idx(Idx::_3), -1.0f);
    setTimerRate(_70, Idx(Idx::_14), -1.0f);

    _19c = getPlayerPosition();
    _190 = _70->getMtx().getTranslation();
    _184.set(_190);

    bool entered;
    if (!testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) && _1b0 != 10) {
        _1b0 = 0;
        entered = sub_7100606BB4(sub_7100607140(), false);
    } else {
        _1b0 = 2;
        entered = sub_7100606BB4(10, true);
    }
    if (!entered)
        sub_7100606FCC();

    _70->sub_71002F2E78(Idx(Idx::_1));
    _70->sub_71002F2E78(Idx(Idx::_3));
    _70->sub_71002F2E78(Idx(Idx::_0));
}

bool WolfLinkNormalRoot::sub_7100609190() {
    auto& leader = ksys::act::PlayerInfo::getSomeProcLink();
    if (!leader.hasProc())
        return false;
    ksys::act::disableAllAttClients(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addActor(leader, "LeaderActor", -1);
    changeChild("待機命令", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_71006090A0() {
    auto& leader = ksys::act::PlayerInfo::getSomeProcLink();
    if (!leader.hasProc())
        return false;
    ksys::act::ai::InlineParamPack params;
    params.addActor(leader, "LeaderActor", -1);
    changeChild("待機命令", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100609288() {
    auto& leader = ksys::act::PlayerInfo::getSomeProcLink();
    if (!leader.hasProc())
        return false;
    ksys::act::ai::InlineParamPack params;
    params.addActor(leader, "LeaderActor", -1);
    changeChild("プレイヤーパス待機", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100609378(State state) {
    ksys::act::ai::InlineParamPack params;
    if (state == State::_14) {
        params.addInt(WarpType::_2, "WarpType", -1);
    } else if (state == State::_13) {
        _108.x();
        params.addInt(WarpType(_108._34), "WarpType", -1);
    } else if (state == State::_15) {
        params.addInt(4, "WarpType", -1);
    } else {
        return false;
    }
    changeChild("ワープ", &params);
    ksys::act::disableAllAttClients(mActor);
    return true;
}

bool WolfLinkNormalRoot::sub_71006088AC() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    if (_1ac == State::_7)
        pos.set(_178);
    else if (_1ac == State::_4)
        pos.set(_19c);
    else
        pos.set(_70->_c48._18);
    params.addVec3(pos, "TargetPos", -1);
    if (_1ac == State::_10)
        changeChild("気づき戦闘", &params);
    else
        changeChild("気づき", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100608B6C(bool force) {
    if (!force) {
        if (!_70 || !_70->_c48._8.hasProc())
            return false;
        auto* target = sub_71005D9050(mActor);
        if (!target)
            return false;
        if (!target->hasProc())
            return false;
    }
    ksys::act::disableAllAttClients(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addFloat(_78->mBattleRange.ref(), "KeepTargetRange", -1);
    changeChild("戦闘", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100608C84() {
    if (!_70 || !_70->_c48._8.hasProc())
        return false;
    auto* target = sub_71005D9050(mActor);
    if (!target)
        return false;
    if (!target->hasProc())
        return false;

    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(target, &accessor))
        return false;
    const auto& mtx = accessor.getActorMtx();
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    ksys::act::ai::InlineParamPack params;
    params.addActor(ksys::act::PlayerInfo::getSomeProcLink(), "LeaderActor", -1);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("狩り", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100608DFC() {
    if (!_70 || !_70->_c48._8.hasProc())
        return false;
    auto* target = sub_71005D9050(mActor);
    if (!target || !target->hasProc())
        return false;
    ksys::act::ai::InlineParamPack params;
    params.addActor(*target, "TargetActor", -1);
    changeChild("回復", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100606FCC() {
    auto& leader = ksys::act::PlayerInfo::getSomeProcLink();
    if (!leader.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&leader, &accessor))
        return false;
    ksys::act::ai::InlineParamPack params;
    params.addFloat(0.0f, "DistanceKept", -1);
    if (accessor.sub_7100D12E64())
        params.addActor(ksys::act::PlayerInfo::instance()->getHorseLink(), "TargetActor", -1);
    else
        params.addActor(leader, "TargetActor", -1);
    changeChild("追従", &params);
    return true;
}

bool WolfLinkNormalRoot::sub_7100609738() {
    auto* nav = mActor->m45();
    if (!nav)
        return false;
    sead::Vector3f diff;
    diff.setSub(nav->_194, _178);
    if (diff.squaredLength() > *mShiekSensorGoalTolerance_s * *mShiekSensorGoalTolerance_s)
        return false;
    if (getNavState(nav) == 1)
        return true;
    return getNavState(nav) == 2;
}

// NON_MATCHING: load scheduling of the _19c/_190 components in the else branch
bool WolfLinkNormalRoot::sub_710060980C() {
    auto& link = ksys::act::PlayerInfo::getSomeProcLink();
    ksys::act::ActorConstDataAccess accessor;
    bool result = false;
    if (ksys::act::acquireActor(&link, &accessor)) {
        if (!(_70->_1698 >> 4 & 1)) {
            const f32 dx = _19c.x - _184.x;
            const f32 dz = _19c.z - _184.z;
            result = 6.76f < dx * dx + dz * dz;
        } else {
            sead::Vector3f dir{_19c.x - _190.x, _19c.y - _190.y, _19c.z - _190.z};
            dir.normalize();
            _184.setScaleAdd(2.7f, dir, _190);
            result = false;
        }
    }
    return result;
}

bool WolfLinkNormalRoot::sub_71006094FC() {
    if (!_70->sub_71002F3234(_78->mHealRange.ref(), 0, 2, 3))
        return false;
    _70->_1698 &= ~0x400;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_70->_c48._8, &accessor) && accessor.hasTag(0x8c06fd5cu) &&
        sub_710073697C(&_70->_c48._8, "IsPlayerPut")) {
        _70->_1698 |= 0x400;
        return true;
    }
    const s32* life = mActor->getLife();
    const s32 cur = life ? *life : 1;
    if (cur < mActor->getMaxLife())
        return true;
    _70->sub_71002F493C();
    return false;
}

// NON_MATCHING: the ten `return State::_4` paths share one block in the original (here three), and
// the flag test has an extra `and w8, w8, #0xff` there
WolfLinkNormalRoot::State WolfLinkNormalRoot::sub_7100607140() {
    using Idx = act::WolfLink::Idx14f8;
    if (cannotUseWolfLinkAmiibo()) {
        if (getTimerValue(_70, Idx(Idx::_18)) <= sead::Mathf::epsilon())
            return State::_15;
        return State::_3;
    }
    if (_108._30)
        return State::_13;
    const u32 prev_state = _1b4;
    if (prev_state == 3)
        return State::_14;
    if (1 < u32(int(_1a8) - 13)) {
        const f32 dx = _19c.x - _190.x;
        const f32 dy = _19c.y - _190.y;
        const f32 dz = _19c.z - _190.z;
        if (dx * dx + dy * dy + dz * dz > *mWarpToPlayerDistance_s * *mWarpToPlayerDistance_s)
            return State::_14;
    }
    if (prev_state == 4)
        return State::_5;
    if (prev_state == 5)
        return State::_4;
    if (_88._30)
        return State::_4;
    if (_140._30 && getTimerValue(_70, Idx(Idx::_11)) <= sead::Mathf::epsilon())
        return State::_4;
    if (_c8._30)
        return State::_12;
    if (_70->_1698 >> 11 & 1)
        return State::_8;
    if (int(_1a8) == 4) {
        auto* nav = mActor->m45();
        if (!nav)
            return State::_6;
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor) ||
            (!accessor.sub_7100D12E64() &&
             !sub_7100742278(_78->mCanReachPlayerNavMeshSearchRadius.ref(), nullptr, nav, &_19c))) {
            return State::_6;
        }
    }
    if (get1bc(Idx1bc::_0) >= get1bc(Idx1bc::_2)) {
        if (!isState(State::_11) ||
            (getCurrentChild() && isFinishedOrFailed(getCurrentChild()))) {
            if (getTimerValue(_70, Idx(Idx::_1)) <= sead::Mathf::epsilon() && sub_71006094FC())
                return State::_11;
        }
    }
    if (!isState(State::_10) ||
        (getCurrentChild() && isFinishedOrFailed(getCurrentChild()))) {
        if (_70->sub_71002F3234(_78->mBattleRange.ref(), 0x539, 1, 3))
            return State::_10;
    }
    if (!isState(State::_9) ||
        (getCurrentChild() && isFinishedOrFailed(getCurrentChild()))) {
        if (int(_1a8) != 10 && _70->sub_71002F3234(_78->mHuntRange.ref(), 0, 3, 3))
            return State::_9;
    }
    if (isFlag1b8(Flag1b8::_1))
        return State::_7;
    if (sub_710060980C())
        return State::_4;
    if (!sub_7100742278(2.0f, nullptr, mActor->m45(), &_190))
        return State::_4;
    if (_70->_1698 >> 7 & 1)
        return State::_4;
    if (!(_70->_1698 >> 4 & 1)) {
        if (isState(State::_4)) {
            if (!getCurrentChild())
                return State::_4;
            if (!isFinishedOrFailed(getCurrentChild()))
                return State::_4;
        }
        if (_1b4 == 5)
            return State::_4;
    }
    return State::_1;
}

// NON_MATCHING: stack slot layout (the by-value `state` object sits at the bottom of the frame in the
// original, the enum temporary shares the accessor's slot) and the _1a8 == 4 / == 1 branch layout
bool WolfLinkNormalRoot::sub_71006085C8(State state) {
    using Idx = act::WolfLink::Idx14f8;
    auto* child = getCurrentChild();
    if (!child)
        return true;
    if (isCurrentChild("気づき") || isCurrentChild("気づき戦闘"))
        return false;
    if (state == State::_3)
        return int(_1a8) != 3;

    if (_88._30 || _c8._30 ||
        (_140._30 && getTimerValue(_70, Idx(Idx::_11)) <= sead::Mathf::epsilon()) || _108._30) {
        return true;
    }

    if (u32(state.value() - 13) < 3) {
        if (int(_1a8) == 14)
            return false;
        if (int(_1a8) != 13)
            return int(_1a8) != 15;
        return false;
    }
    if (_70->_1698 >> 6 & 1)
        return false;

    const s32 current = _1a8;
    if (current == 4) {
        if (state == State::_1)
            return true;
    } else if (current == 1 && state == State::_4) {
        return true;
    }
    if (!(getTimerValue(_70, Idx(Idx::_12)) <= sead::Mathf::epsilon()))
        return false;
    if (current == 12)
        return false;
    if (child->isFinished())
        return true;
    if (child->isFailed())
        return true;
    if (int(_1a8) == 11 && state == State::_10 && get1bc(Idx1bc::_2) > get1bc(Idx1bc::_0))
        return true;
    if (int(state) == int(_1a8))
        return false;
    if (int(state) > int(_1a8))
        return true;
    if (int(_1a8) == 6) {
        if (auto* nav = mActor->m45()) {
            auto& leader = ksys::act::PlayerInfo::getSomeProcLink();
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(&leader, &accessor) &&
                (accessor.sub_7100D12E64() ||
                 sub_7100742278(_78->mCanReachPlayerNavMeshSearchRadius.ref(), nullptr, nav,
                                &_19c))) {
                return true;
            }
        }
    }
    return int(_1a8) == 4;
}

// NON_MATCHING: `state`'s spill slot is at the bottom of the frame in the original (here: the top), the
// first `_1a8` switch has its `_1b0 = 0` store scheduled after the volatile load, and `_1b4 & ~1` uses w8
bool WolfLinkNormalRoot::sub_7100606BB4(State state, bool force) {
    using Idx = act::WolfLink::Idx14f8;
    switch (state) {
    case State::_1:
        changeChild("待機", nullptr);
        break;
    default:
        return false;
    case State::_3:
        if (!sub_7100609190())
            return false;
        break;
    case State::_4:
        if (!sub_7100606FCC())
            return false;
        break;
    case State::_5: {
        ksys::act::ai::InlineParamPack params;
        params.addVec3(getPlayerPosition(), "TargetPos", -1);
        changeChild("追従リトライ", &params);
        break;
    }
    case State::_6:
        if (!sub_7100609288())
            return false;
        break;
    case State::_7:
        if (!sub_7100608F0C())
            return false;
        break;
    case State::_8:
        changeChild("遠吠え", nullptr);
        break;
    case State::_9:
        if (!sub_7100608C84())
            return false;
        break;
    case State::_10:
        if (!sub_7100608B6C(force))
            return false;
        break;
    case State::_11:
        if (!sub_7100608DFC())
            return false;
        break;
    case State::_12:
        if (!sub_71006090A0())
            return false;
        break;
    case State::_13:
    case State::_14:
    case State::_15:
        if (!sub_7100609378(state))
            return false;
        break;
    }

    _1b0 = 0;
    switch (_1a8) {
    case State::_7:
        _1b8 = 0;
        break;
    case State::_3:
        setTimerRate(_70, Idx(Idx::_18), 0.0f);
        break;
    default:
        break;
    }
    if ((_1b4 & ~1u) == 2) {
        _1c8 = 0;
        _1b4 = 0;
    }

    if (state == State::_4) {
        if (_1b4 != 5 && _1b4 != 4)
            _1b4 = 1;
        if (_140._30) {
            setTimerRate(_70, Idx(Idx::_11), 0.0f);
            if (int(_1a8) != 4 && int(_1a8) != 3) {
                _70->sub_71002F2E78(Idx(Idx::_14));
                _70->_1698 |= 0x20;
                _70->_1698 &= ~0x800;
                _70->_1698 &= ~0x400;
                const f32 time = s32(_78->mCallOverrideCounterLength.ref());
                auto& timer = _70->_14f8[Idx(Idx::_12)];
                timer.value = time;
                timer.previous_value = time;
                setTimerRate(_70, Idx(Idx::_12), -1.0f);
            }
        }
        _140.x();
        _88.x();
    } else if (state == State::_12) {
        _c8.x();
        _70->_1698 &= ~0x800;
        _70->_1698 &= ~0x400;
    } else if (state == State::_3) {
        _70->sub_71002F2E78(Idx(Idx::_18));
        setTimerRate(_70, Idx(Idx::_18), -1.0f);
    }
    _1a8 = state;
    return true;
}

void WolfLinkNormalRoot::sub_7100607910() {
    auto* info = ksys::act::PlayerInfo::instance();
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&info->getPlayerLink(), &accessor) && accessor.sub_7100D12E64()) {
        ksys::act::disableAllAttClients(mActor);
        return;
    }
    switch (_1a8) {
    case State::_3:
    case State::_10:
    case State::_13:
    case State::_14:
    case State::_15:
        return;
    default:
        break;
    }
    auto* client0 = mActor->getAttention()->getClientByIdx(0);
    auto* client1 = mActor->getAttention()->getClientByIdx(1);
    if (client0 && client1) {
        if (int(_1a8) == 12 || _c8._30) {
            client0->disable();
            client1->enable();
        } else if (int(_1a8) != 12 || _88._30 || _140._30) {
            client0->enable();
            client1->disable();
        }
    }
}

// NON_MATCHING: register assignment (this/leader in x19/x20 swapped)
void WolfLinkNormalRoot::sub_7100608200() {
    if (int(_1a8) == 4) {
        auto* info = ksys::act::PlayerInfo::instance();
        auto& leader = info->getPlayerLink();
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(&leader, &accessor) || !accessor.sub_7100D12E64())
            getCurrentChild()->setDynamicParam(leader, "TargetActor");
        else
            getCurrentChild()->setDynamicParam(info->getHorseLink(), "TargetActor");
    }
}

void WolfLinkNormalRoot::sub_7100609DFC() {
    using Idx = act::WolfLink::Idx14f8;
    _70->sub_71002F2E78(Idx(Idx::_2));
    auto* nav = mActor->m45();
    nav->inlineClearTargets();
    nav->inlineReset();
    _1b8 |= 1 << Flag1b8(Flag1b8::_0);
    _1b8 &= ~(1 << Flag1b8(Flag1b8::_2));
}

// NON_MATCHING: block layout of the state-change tail (the original places the pending-state block
// before the direct-enter block); everything else matches
void WolfLinkNormalRoot::calc_() {
    _190 = _70->getMtx().getTranslation();
    _19c.set(getPlayerPosition());
    sub_7100607910();
    sub_7100607A2C();

    auto* actor = mActor;
    const s32* life_ptr = actor->getLife();
    const f32 life = life_ptr ? f32(*life_ptr) : 1.0f;
    const f32 max_life = actor->getMaxLife();
    const f32 ratio = sead::Mathf::clamp(life, 0.0f, max_life) / max_life;
    _1bc[0] = sead::Mathf::clamp(sead::Mathf::pow(0.09f, ratio) - ratio * 0.09f, 0.0f, 1.0f);
    _1bc[2] = sub_7100609954();
    sub_7100607D00();
    sub_7100608200();

    auto* child = getCurrentChild();
    if (!child)
        return;
    if (child->isFinished() || child->isFailed()) {
        sub_71006082FC(child->isFinished());
        if (isCurrentChild("気づき") || isCurrentChild("気づき戦闘")) {
            if (!sub_7100606BB4(_1ac, false))
                sub_7100606FCC();
        }
    }
    if (isCurrentChild("気づき") || isCurrentChild("気づき戦闘"))
        return;

    const State changed = sub_7100607140();
    if (!sub_71006085C8(changed))
        return;

    const State next = changed;
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) || _1b0 == 2 ||
        entersDirectly(next, _1a8)) {
        if (!sub_7100606BB4(changed, false))
            sub_7100606FCC();
    } else {
        _1ac = changed;
        sub_71006088AC();
    }
}

void WolfLinkNormalRoot::leave_() {
    using Idx = act::WolfLink::Idx14f8;
    _70->_14f8[Idx(Idx::_1)].rate = 0;
    _70->_14f8[Idx(Idx::_0)].rate = 0;
    _70->_14f8[Idx(Idx::_3)].rate = 0;
    _1b0 = _1a8;
    _70->_1698 &= ~0x400;
    _70->_1698 &= ~0x800;
}

// NON_MATCHING: regalloc (w8/w9 swapped around the timer index computation)
bool WolfLinkNormalRoot::handleMessage_(const ksys::Message& message) {
    bool reset;
    switch (_1a8) {
    case 0:
    case 3:
    case 5:
    case 6:
    case 13:
    case 14:
    case 15:
        reset = true;
        break;
    default:
        reset = false;
        break;
    }

    if (_88.m2(message)) {
        if (reset)
            _88.x();
        return true;
    }
    if (_c8.m2(message)) {
        if (reset)
            _c8.x();
        return true;
    }
    if (_108.m2(message)) {
        if (reset)
            _108.x();
        return true;
    }
    if (!_140.m2(message))
        return false;

    if (reset) {
        _140.x();
        return true;
    }

    const s32 delay = _78->mCallDelayMinLength.ref() +
                      sead::Mathf::sqrt(ksys::util::sqXZDistance(_19c, _190)) / 11.0f;
    using Idx = act::WolfLink::Idx14f8;
    auto& timer = _70->_14f8[Idx(Idx::_11)];
    timer.value = delay;
    timer.previous_value = delay;
    _70->_14f8[Idx(Idx::_11)].rate = -1.0f;
    _70->_1698 |= 0x4000;
    return true;
}

void WolfLinkNormalRoot::loadParams_() {
    getStaticParam(&mShiekSensorLeadDistance_s, "ShiekSensorLeadDistance");
    getStaticParam(&mShiekSensorGoalTolerance_s, "ShiekSensorGoalTolerance");
    getStaticParam(&mShiekSensorTargetFowardOffset_s, "ShiekSensorTargetFowardOffset");
    getStaticParam(&mBattleAggressionRange_s, "BattleAggressionRange");
    getStaticParam(&mHowlAtEnemyRange_s, "HowlAtEnemyRange");
    getStaticParam(&mUtilityWantsToHunt_s, "UtilityWantsToHunt");
    getStaticParam(&mWarpToPlayerDistance_s, "WarpToPlayerDistance");
}

}  // namespace uking::ai
