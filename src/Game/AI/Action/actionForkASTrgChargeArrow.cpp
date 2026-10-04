#include "Game/AI/Action/actionForkASTrgChargeArrow.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgChargeArrow::ForkASTrgChargeArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgChargeArrow::~ForkASTrgChargeArrow() = default;

bool ForkASTrgChargeArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgChargeArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
}

void ForkASTrgChargeArrow::leave_() {
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(5));
}

void ForkASTrgChargeArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsEndState_s, "IsEndState");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkASTrgChargeArrow::calc_() {
    if (sub_71005DD780(mActor, 55, nullptr, *mTargetBone_s, *mSeqBank_s)) {
        _40 = 1;
        switch (*mIsEndState_s) {
        case 1:
            mFlags.set(Flag::Changeable);
            break;
        case 2:
            setFinished();
            break;
        }
    }
    if (_40 == 1)
        sub_71005D787C(mActor, *mWeaponIdx_s, uking::act::Unk_71002eda38(4));
}

}  // namespace uking::action
