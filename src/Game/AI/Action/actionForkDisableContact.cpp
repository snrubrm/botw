#include "Game/AI/Action/actionForkDisableContact.h"
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ForkDisableContact::ForkDisableContact(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDisableContact::~ForkDisableContact() = default;

// NON_MATCHING: loop-variable form only (the original walks a byte offset 0x20..0x70 over the names; ours a plain index)
bool ForkDisableContact::init_(sead::Heap* heap) {
    for (int i = 0; i < 5; ++i) {
        auto* body = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(),
                                                   mRigidBodyName_s[i].cstr());
        if (!body) {
            body = mActor->findPhysicsBodyByName(ksys::act::getStr_EntitySensor().cstr(),
                                                 mRigidBodyName_s[i].cstr());
        }
        mBodies[i].mBody = body;
        mBodies[i].mIsEnabled = true;
    }
    return true;
}

void ForkDisableContact::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkDisableContact::leave_() {
    sub_710014B0F0();
}

// NON_MATCHING: regalloc only (the original computes &mRigidBodyName_s[0] before the first getStaticParam call)
void ForkDisableContact::loadParams_() {
    getStaticParam(&mParams.mRecoverDelayTimeMin_s, "RecoverDelayTimeMin");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 5; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "RigidBodyName%d", i) << sead::flush;
        getStaticParam(&mRigidBodyName_s[i], key);
    }
}

void ForkDisableContact::calc_() {
    if (m32()) {
        sub_710014AED0();
        mRecoverTimer.reset(*mParams.mRecoverDelayTimeMin_s);
    } else if (!m33()) {
        if (mRecoverTimer.value <= sead::Mathf::epsilon())
            sub_710014B018();
        else
            mRecoverTimer.update();
    }
}

}  // namespace uking::action
