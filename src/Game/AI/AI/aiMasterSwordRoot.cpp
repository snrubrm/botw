#include "Game/AI/AI/aiMasterSwordRoot.h"

namespace uking::ai {

MasterSwordRoot::MasterSwordRoot(const InitArg& arg) : WeaponRootAI(arg) {}

MasterSwordRoot::~MasterSwordRoot() = default;

bool MasterSwordRoot::init_(sead::Heap* heap) {
    *static_cast<Unk_71025afb58**>(mMagicCreateUnit_a) = &_f8;
    return WeaponRootAI::init_(heap);
}

void MasterSwordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004A3410();
    if (_e8) {
        sub_7100E21228();
        _e8 = false;
        return;
    }
    WeaponRootAI::enter_(params);
}

void MasterSwordRoot::leave_() {
    if (_f8._8.isAllocatedOrFailed())
        _f8._8.deleteProc();
    WeaponRootAI::leave_();
}

void MasterSwordRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

}  // namespace uking::ai
