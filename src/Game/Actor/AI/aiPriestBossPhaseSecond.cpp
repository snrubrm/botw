#include "Game/Actor/AI/aiPriestBossPhaseSecond.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::ai {

PriestBossPhaseSecond::PriestBossPhaseSecond(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseSecond::~PriestBossPhaseSecond() {
    mRecords.freeBuffer();
}

// NON_MATCHING: ours unrolls the record loop; the original keeps a loop over 0 .. 4 that skips 0.
bool PriestBossPhaseSecond::init_(sead::Heap* heap) {
    if (!PriestBossPhase::init_(heap))
        return false;

    mRecords.allocBuffer(4, heap);
    for (s32 i = 1; i < 5; ++i) {
        if (auto* record = mRecords.emplaceBack()) {
            record->id = i;
            record->value = 0.25f;
            record->data = nullptr;
        }
    }
    _6c0.sub_710071B37C(sub_7100525A88());
    _958.sub_710071B37C(sub_7100525A88());
    return true;
}

void PriestBossPhaseSecond::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);

    auto* unit = sub_7100525A88();
    const f32 space = *mRespawnBaseSpace_s;
    const f32 move_time = *mRespawnBaseMoveTime_s;
    const f32 interval = *mRespawnBaseInterval_s;
    unit->_44 = space;
    unit->_48 = move_time;
    unit->_4c = interval;
    _134.fill(0);

    const Unk_7102451070::InitArg init_arg{sub_7100525A88(), 0.5f, 10.0f, 15.0f, false};
    _158.sub_710071CB98(init_arg);
    for (s32 i = 2; i <= 10; ++i)
        _158.sub_710071CC4C(i);

    Unk_7102451050::InitArg arg;
    arg.unit = sub_7100525A88();
    arg._8 = *mRespawnSpan_s;
    arg._c = 1;
    const int* start_phase = nullptr;
    arg._e = !getMapUnitParam(&start_phase, "PriestBossStartPhase") || *start_phase != 0;
    _488.sub_710071BFE4(arg);

    _6c0._1d8 = *mCircleFormRange_s;
    _958._1dc = *mLineFormDistFromPlayer_s;
    _958._1d8 = *mLineFormSpace_s;

    ksys::act::ActorLinkConstDataAccess accessor;
    if (sub_7100525B18(2, &accessor)) {
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx;
            sead::Vector3f pos;
            _6c0.m7(&pos, 2);
            mtx = accessor.getActorMtx();
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
        }
        _134[0] = accessor.getMaxLife();
    }

    unit = sub_7100525A88();
    const s32 sim_atk_max = *mSimAtkMax_s;
    const s32 bow_equip_max = *mBowEquipMax_s;
    unit->_98 = sim_atk_max;
    unit->_198 = bow_equip_max;
    sub_710052B4D0(Mode::_0);
}

void PriestBossPhaseSecond::leave_() {
    PriestBossPhase::leave_();
    for (s32 i = 2; i <= 10; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (sub_7100525B18(i, &accessor))
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    sub_710052B4D0(Mode::_2);
    auto* unit = sub_7100525A88();
    unit->_98 = 0;
    unit->_198 = 0;
    sub_7100525A88()->sub_7100719ED0();
    sub_7100525A88()->resetFlag(Unk_7102450fa8::Flag::_3);
    sub_7100525A88()->resetFlag(Unk_7102450fa8::Flag::_16);
}

void PriestBossPhaseSecond::sub_710052B4D0(Mode mode) {
    auto* unit = sub_7100525A88();
    if (!unit)
        return;

    unit->resetFlag(Unk_7102450fa8::Flag::_0);
    if (!unit->isFlagOn(Unk_7102450fa8::Flag::_0)) {
        unit->_88 = nullptr;
        unit->_90 = &_158;
        _488.sub_710071C1B8();
        _6b8 = nullptr;
        _12c = 0;
        setStateFlag(StateFlag::_2);
        unit->setFlag(Unk_7102450fa8::Flag::_16);
    }

    switch (mode) {
    case Mode::_0:
        resetStateFlag(StateFlag::_2);
        _488.resetFlag(Unk_7102451050::Flag::_0);
        break;
    case Mode::_2:
        unit->_88 = nullptr;
        unit->_90 = nullptr;
        break;
    default:
        break;
    }
}

void PriestBossPhaseSecond::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mModeChangeLife_s, "ModeChangeLife");
    getStaticParam(&mSimAtkMax_s, "SimAtkMax");
    getStaticParam(&mBowEquipMax_s, "BowEquipMax");
    getStaticParam(&mSyncAtkMax_s, "SyncAtkMax");
    getStaticParam(&mModeChangeBlockTime_s, "ModeChangeBlockTime");
    getStaticParam(&mRespawnSpan_s, "RespawnSpan");
    getStaticParam(&mRespawnBaseSpace_s, "RespawnBaseSpace");
    getStaticParam(&mRespawnBaseMoveTime_s, "RespawnBaseMoveTime");
    getStaticParam(&mRespawnBaseInterval_s, "RespawnBaseInterval");
    getStaticParam(&mCircleFormRange_s, "CircleFormRange");
    getStaticParam(&mCircleFormRushWait_s, "CircleFormRushWait");
    getStaticParam(&mCircleFormRushInterval_s, "CircleFormRushInterval");
    getStaticParam(&mCircleFormShootWait_s, "CircleFormShootWait");
    getStaticParam(&mCircleFormShootInterval_s, "CircleFormShootInterval");
    getStaticParam(&mLineFormDistFromPlayer_s, "LineFormDistFromPlayer");
    getStaticParam(&mLineFormSpace_s, "LineFormSpace");
    getStaticParam(&mLineFormRushWait_s, "LineFormRushWait");
    getStaticParam(&mLineFormRushInterval_s, "LineFormRushInterval");
    getStaticParam(&mLineFormFallWait_s, "LineFormFallWait");
    getStaticParam(&mLineFormFallInterval_s, "LineFormFallInterval");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
}

void PriestBossPhaseSecond::m39() {
    ksys::act::ActorLinkConstDataAccess accessor;
    for (int i = 2; i <= 10; ++i) {
        if (sub_7100525B18(i, &accessor))
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

// NON_MATCHING: the original flag-index wrapper emits temporary index stores.
void PriestBossPhaseSecond::m41() {
    _158._10 = getPlayerPosition();
    _158._328.setBit(0);
    _158.sub_710071CE44();
    _488.sub_710071C034();
}

void PriestBossPhaseSecond::m40() {
    if (sub_7100525A88()->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_0)))
        return;
    PriestBossPhase::m40();
}

bool PriestBossPhaseSecond::handleMessage_(const ksys::Message* message) {
    if (_6b8 && _6b8->m9(*message))
        return true;
    if (_488.sub_710071C550(*message))
        return true;
    if (!_b58.m2(*message))
        return false;
    if (!isStateFlagOn(StateFlag::_2))
        return true;

    if ((_b58._38._0 == 1 && !sub_7100525A88()->isFlagOn(Unk_7102450fa8::Flag::_0)) ||
        (_b58._38._0 == 2 && sub_7100525A88()->isFlagOn(Unk_7102450fa8::Flag::_0))) {
        _130 = 0;
        resetStateFlag(StateFlag::_2);
        sub_7100525A88()->resetFlag(Unk_7102450fa8::Flag::_16);
    }
    return true;
}

bool PriestBossPhaseSecond::m37(f32* ratio) {
    ksys::act::BaseProcLink link;
    if (!sub_7100525BC0(2, &link))
        return false;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    if (!actor || !actor->isAwakeMaybe())
        return false;

    auto* life = actor->getLife();
    const f32 life_value = life ? f32(*life) : 1.0f;
    *ratio = life_value / f32(actor->getMaxLife());
    return true;
}

}  // namespace uking::ai
