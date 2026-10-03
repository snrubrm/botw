#include "Game/AI/Action/actionForkASTrgWeaponDrop.h"
#include <prim/seadFormatPrint.h>

namespace uking::action {

ForkASTrgWeaponDrop::ForkASTrgWeaponDrop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgWeaponDrop::~ForkASTrgWeaponDrop() = default;

bool ForkASTrgWeaponDrop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgWeaponDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkASTrgWeaponDrop::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgWeaponDrop::loadParams_() {
    sead::FixedSafeString<32> key;
    for (u32 i = 1; i <= 4; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "WeaponIdx%d", i) << sead::flush;
        getStaticParam(&mWeaponIdx_s[i - 1], key);
    }
    getStaticParam(&mIsKeepRemind_s, "IsKeepRemind");
}

void ForkASTrgWeaponDrop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
