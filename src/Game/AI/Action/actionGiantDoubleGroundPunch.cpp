#include <prim/seadFormatPrint.h>
#include "Game/AI/Action/actionGiantDoubleGroundPunch.h"
#include "Game/Actor/actRideable.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

GiantDoubleGroundPunch::GiantDoubleGroundPunch(const InitArg& arg) : ForkSeqNoWeaponAttack(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GiantDoubleGroundPunch::~GiantDoubleGroundPunch() {
    ;
}

bool GiantDoubleGroundPunch::init_(sead::Heap* heap) {
    if (!ForkSeqNoWeaponAttack::init_(heap))
        return false;
    for (auto& entry : mCoBody) {
        entry._18 = mActor->findPhysicsBodyByName(sub_71007A250C()->cstr(), entry.mName_s.cstr());
        if (!entry._18)
            entry._18 = mActor->findPhysicsBodyByName(sub_71007A24E4()->cstr(), entry.mName_s.cstr());
    }
    return true;
}

void GiantDoubleGroundPunch::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkSeqNoWeaponAttack::enter_(params);
    mFlags.reset(Flag::Changeable);
    mCoBody[0]._10 = false;
    mCoBody[1]._10 = false;
    mCoBody[2]._10 = false;
    mCoBody[3]._10 = false;
    if (auto* rideable = mActor->m132()) {
        rideable->_18.sub_7100E770C4(false);
        rideable->_18.sub_7100E786F0(mASName_s);
    } else {
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    }
    _1cc = true;
    _1cd = false;
    _1c8 = 0;
    _1f4 = 0;
}

void GiantDoubleGroundPunch::leave_() {
    sub_710018823C();
    sub_71005DB3EC(mActor);
    ForkSeqNoWeaponAttack::leave_();
}

void GiantDoubleGroundPunch::loadParams_() {
    ForkSeqNoWeaponAttack::loadParams_();
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 4; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "CoBodyName%d", i) << sead::flush;
        getStaticParam(&mCoBody[i].mName_s, key);
    }
    getStaticParam(&mRotSpeedMax_s, "RotSpeedMax");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mASName2_s, "ASName2");
    for (u32 i = 0; i < 3; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "PunchAimPosL%d", i) << sead::flush;
        getStaticParam(&mPunchAimPosL_s[i], key);
        (sead::StringCutOffPrintFormatter(&key) << "PunchAimPosR%d", i) << sead::flush;
        getStaticParam(&mPunchAimPosR_s[i], key);
    }
    for (u32 i = 0; i < 3; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "RotOffset%d", i) << sead::flush;
        getStaticParam(&mRotOffset_s[i], key);
    }
    getDynamicParam_2(&mTargetPos_d, "TargetPos");
}

void GiantDoubleGroundPunch::calc_() {
    ForkSeqNoWeaponAttack::calc_();
}

}  // namespace uking::action
