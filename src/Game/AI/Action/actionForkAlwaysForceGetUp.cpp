#include "Game/AI/Action/actionForkAlwaysForceGetUp.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAlwaysForceGetUp::ForkAlwaysForceGetUp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysForceGetUp::~ForkAlwaysForceGetUp() = default;

bool ForkAlwaysForceGetUp::init_(sead::Heap* heap) {
    if (*mIsUseCRBOffsetUnit_s) {
        _78.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
        if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_78._0)) {
            if (!(unit->_b0 & 1)) {
                unit->_8.setName("Skl_Root");
                unit->_8._68 = sead::Matrix34f::ident;
                unit->_b4 = 0;
                unit->_b0 |= 1;
            }
        }
        _78.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
        _78.x();
    }
    return true;
}

void ForkAlwaysForceGetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsUseCRBOffsetUnit_s) {
        if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_78.mSlot))
            unit->_8.sub_attach(mActor);
    }
    m32(&_48);
    mFlags.set(Flag::Changeable);
    _80 = false;
}

void ForkAlwaysForceGetUp::leave_() {
    if (*mIsUseCRBOffsetUnit_s) {
        if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_78.mSlot))
            unit->_8.sub_detach(mActor);
    }
}

void ForkAlwaysForceGetUp::loadParams_() {
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRotSpdMin_s, "RotSpdMin");
    getStaticParam(&mRotSpdMax_s, "RotSpdMax");
    getStaticParam(&mIsUseCRBOffsetUnit_s, "IsUseCRBOffsetUnit");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkAlwaysForceGetUp::calc_() {
    if (_80) {
        sub_7100738AA8(mActor, 0.0f);
        if (*mIsUseCRBOffsetUnit_s) {
            if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_78.mSlot))
                unit->_8.mHandle._68 = sead::Matrix34f::ident;
        }
        return;
    }

    sub_710073FA94(&_54, mActor);
    _80 = sub_710074006C(&_54, _48, sead::Vector3f::ey, true, *mRotRatio_s, *mRotSpdMax_s,
                         *mRotSpdMin_s);
    sub_7100740F1C(_54, mActor);
    if (*mIsUseCRBOffsetUnit_s) {
        if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_78.mSlot))
            sub_71007448C0(&unit->_8.mHandle, sead::Matrix34f::ident, *mRotRatio_s);
    }
}

void ForkAlwaysForceGetUp::m32(sead::Vector3f* dir) {
    mActor->getMtx().getBase(*dir, 2);
    const f32 front_y = dir->y;
    dir->y = 0;
    const f32 len = dir->normalize();
    if (len <= sead::Mathf::epsilon() && len >= -sead::Mathf::epsilon()) {
        mActor->getMtx().getBase(*dir, 1);
        if (front_y >= 0)
            dir->negate();
    } else if (mActor->getMtx()(1, 1) < 0) {
        dir->negate();
    }
}

}  // namespace uking::action
