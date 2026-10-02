#include "Game/AI/AI/aiAssassinMiddleAzitoRootAccept.h"

namespace uking::ai {

AssassinMiddleAzitoRootAccept::AssassinMiddleAzitoRootAccept(const InitArg& arg)
    : AssassinMiddleRoot(arg) {}

// NON_MATCHING: the original inlines the listener _360's destructor (see AssassinMiddleAzitoRoot)
AssassinMiddleAzitoRootAccept::~AssassinMiddleAzitoRootAccept() = default;

bool AssassinMiddleAzitoRootAccept::init_(sead::Heap* heap) {
    return AssassinMiddleRoot::init_(heap);
}

void AssassinMiddleAzitoRootAccept::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinMiddleRoot::enter_(params);
}

void AssassinMiddleAzitoRootAccept::calc_() {
    AssassinMiddleRoot::calc_();
}

void AssassinMiddleAzitoRootAccept::leave_() {
    AssassinMiddleRoot::leave_();
}

void AssassinMiddleAzitoRootAccept::loadParams_() {
    AssassinMiddleRoot::loadParams_();
    getStaticParam(&mEntryPoint_s, "EntryPoint");
    getStaticParam(&mDemoName_s, "DemoName");
}

}  // namespace uking::ai
