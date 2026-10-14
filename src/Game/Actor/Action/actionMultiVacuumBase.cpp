#include "Game/Actor/Action/actionMultiVacuumBase.h"
#include "Game/Actor/actEnemy.h"
#include <prim/seadFormatPrint.h>

namespace uking::action {

MultiVacuumBase::MultiVacuumBase(const InitArg& arg)
    : ksys::act::ai::Action(arg), _b8(sead::DynamicCast<uking::act::Enemy>(mActor)) {}

// NON_MATCHING: fixed-string and formatter stack slots are exchanged.
MultiVacuumBase::~MultiVacuumBase() {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
        sead::FixedSafeString<32> name;
        for (u32 i = 0; s32(i) < *mVacuumNum_s; ++i) {
            (sead::StringCutOffPrintFormatter(&name) << "Vacuum%d", i) << sead::flush;
            enemy->_1128.sub_7100D3CFEC(name);
        }
    }
}

bool MultiVacuumBase::handleAck_(const ksys::MessageAck* ack) {
    return _b8.sub_710073E5E0(ack);
}

// NON_MATCHING: fixed-string and formatter stack slots are exchanged.
bool MultiVacuumBase::init_(sead::Heap* heap) {
    _148.copy("Vacuum0");
    if (!_b8.sub_710073E45C(heap, _148))
        return false;
    if (!_118.sub_710073E730(heap, 30, mActor))
        return false;
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
        sead::FixedSafeString<32> name;
        for (u32 i = 0; s32(i) < *mVacuumNum_s; ++i) {
            (sead::StringCutOffPrintFormatter(&name) << "Vacuum%d", i) << sead::flush;
            if (!enemy->_1128.sub_7100D3CED8(name, heap))
                return false;
        }
    }
    return true;
}

// NON_MATCHING: parameter stores, flag registers and formatter scheduling differ.
void MultiVacuumBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mChangeableTiming_s != 0)
        mFlags.reset(Flag::Changeable);
    else
        mFlags.set(Flag::Changeable);
    _1b4 = false;
    _1b5 = false;
    _1b8 = *mTime_s;
    _118._c = *mTargetSpeed_s;
    _118._8 = *mTargetAccRate_s;
    _118._10 = *mBaseWeight_s;
    _b8._38.reset();
    _b8._58 = 0;
    for (_1a0 = 0; s32(_1a0) < *mVacuumNum_s; ++_1a0) {
        (sead::StringCutOffPrintFormatter(&_148) << "Vacuum%d", _1a0) << sead::flush;
        if (_b8.sub_710073E4C4())
            break;
    }
    _1a4 = 0;
    playAS(mStartAS_s.cstr(), false, 0, 0, -1.0f);
}

void MultiVacuumBase::leave_() {
    _148.copy("Vacuum0");
}

void MultiVacuumBase::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mAddTimeVacuuming_s, "AddTimeVacuuming");
    getStaticParam(&mAddTimeNearVacuuming_s, "AddTimeNearVacuuming");
    getStaticParam(&mVacuumNum_s, "VacuumNum");
    getStaticParam(&mChangeableTiming_s, "ChangeableTiming");
    getStaticParam(&mEndDist_s, "EndDist");
    getStaticParam(&mMaxDist_s, "MaxDist");
    getStaticParam(&mTargetAccRate_s, "TargetAccRate");
    getStaticParam(&mTargetSpeed_s, "TargetSpeed");
    getStaticParam(&mBaseWeight_s, "BaseWeight");
    getStaticParam(&mVacuumAngle_s, "VacuumAngle");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mEndAS_s, "EndAS");
    getStaticParam(&mVacuumPosOffset_s, "VacuumPosOffset");
}

// NON_MATCHING: the final changeable-flag masks use different registers.
void MultiVacuumBase::calc_() {
    switch (_1a4) {
    case 0:
        if (isFinishedAS(0, 0)) {
            playAS(mLoopAS_s.cstr(), false, 0, 0, -1.0f);
            _1a4 = 1;
            _1a8.reset(0.0f, 1.0f);
            mFlags.change(Flag::Changeable, *mChangeableTiming_s == 0 || *mChangeableTiming_s == 1);
        }
        break;
    case 1:
        sub_71001EE31C();
        if (s32(_1a0) >= *mVacuumNum_s ||
            (_1a8.value > static_cast<f32>(_1b8) &&
             (_b8.sub_710073E4C4() || _b8.sub_710073E50C()))) {
            if (mEndAS_s.isEmpty())
                setFinished();
            else
                playAS(mEndAS_s.cstr(), false, 0, 0, -1.0f);
            if (*mChangeableTiming_s != 0)
                mFlags.reset(Flag::Changeable);
            else
                mFlags.set(Flag::Changeable);
            _1a4 = 2;
        } else {
            _1a8.update();
        }
        break;
    case 2:
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }

}

}  // namespace uking::action
