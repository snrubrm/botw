#include "Game/AI/Action/actionForkDisableContact.h"
#include <prim/seadFormatPrint.h>

namespace uking::action {

ForkDisableContact::ForkDisableContact(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkDisableContact::~ForkDisableContact() = default;

bool ForkDisableContact::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkDisableContact::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkDisableContact::leave_() {
    ksys::act::ai::Action::leave_();
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
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
