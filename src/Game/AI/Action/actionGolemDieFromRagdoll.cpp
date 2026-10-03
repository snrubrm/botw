#include "Game/AI/Action/actionGolemDieFromRagdoll.h"
#include <prim/seadFormatPrint.h>

namespace uking::action {

GolemDieFromRagdoll::GolemDieFromRagdoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GolemDieFromRagdoll::~GolemDieFromRagdoll() = default;

bool GolemDieFromRagdoll::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GolemDieFromRagdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GolemDieFromRagdoll::leave_() {
    ksys::act::ai::Action::leave_();
}

void GolemDieFromRagdoll::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRagdollMoveLimitDist_s, "RagdollMoveLimitDist");
    getStaticParam(&mBlownHeight_s, "BlownHeight");
    getStaticParam(&mBlownSpeed_s, "BlownSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mRagdollControllerKey_s, "RagdollControllerKey");
    sead::FixedSafeString<64> key;
    for (u32 i = 1; i <= 4; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "RagdollBodyName%d", i) << sead::flush;
        getStaticParam(&mRagdollBodies_s[i - 1].mRagdollBodyName_s, key);
        (sead::StringCutOffPrintFormatter(&key) << "MaterialName%d", i) << sead::flush;
        getStaticParam(&mRagdollBodies_s[i - 1].mMaterialName_s, key);
    }
    getStaticParam(&mXLinkKey_s, "XLinkKey");
    getStaticParam(&mImpulseXLinkKey_s, "ImpulseXLinkKey");
}

void GolemDieFromRagdoll::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
