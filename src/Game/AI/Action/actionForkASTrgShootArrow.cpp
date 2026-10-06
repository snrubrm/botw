#include "Game/AI/Action/actionForkASTrgShootArrow.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"

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

// NON_MATCHING: stack layout only (the original puts `pos` below `dir` and the Unk_71002eda38 temporary shares the slot
// of `dir`; ours shares the temporary with `pos`)
void ForkASTrgShootArrow::calc_() {
    if (sub_71005DD780(mActor, 0x47, nullptr, *mTargetBone_s, *mSeqBank_s)) {
        sead::Vector3f pos;
        sead::Vector3f dir;
        if (sub_7100143C64(&dir, &pos))
            m33(pos, &dir);
        else
            m33(pos, nullptr);
        _70 = true;
        if (*mIsEndState_s == 2)
            setFinished();
        else if (*mIsEndState_s == 1)
            mFlags.set(Flag::Changeable);
    } else if (!_70) {
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
    }
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
