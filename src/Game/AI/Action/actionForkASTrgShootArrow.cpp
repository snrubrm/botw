#include "Game/AI/Action/actionForkASTrgShootArrow.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

ForkASTrgShootArrow::ForkASTrgShootArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgShootArrow::~ForkASTrgShootArrow() = default;

bool ForkASTrgShootArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = false;
}

void ForkASTrgShootArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgShootArrow::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsEndState_s, "IsEndState");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mOffsetRangeMin_s, "OffsetRangeMin");
    getStaticParam(&mOffsetRangeMax_s, "OffsetRangeMax");
    getStaticParam(&mOffsetRateByDist_s, "OffsetRateByDist");
    getStaticParam(&mOffsetRangeMinOutOfScreen_s, "OffsetRangeMinOutOfScreen");
    getStaticParam(&mOffsetRangeMaxOutOfScreen_s, "OffsetRangeMaxOutOfScreen");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkASTrgShootArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

void ForkASTrgShootArrow::m32(sead::Vector3f* dir) {
    mActor->getMtx().getBase(*dir, 2);
}

void ForkASTrgShootArrow::m33(const sead::Vector3f& pos, const sead::Vector3f* dir) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->sub_7100016494();
    sub_71005D80FC(mActor, *mWeaponIdx_s, pos, 0, 1.0f, dir, nullptr);
}

}  // namespace uking::action
