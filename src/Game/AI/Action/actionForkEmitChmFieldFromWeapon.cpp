#include "Game/AI/Action/actionForkEmitChmFieldFromWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkEmitChmFieldFromWeapon::ForkEmitChmFieldFromWeapon(const InitArg& arg)
    : ForkEmitChmField(arg) {}

ForkEmitChmFieldFromWeapon::~ForkEmitChmFieldFromWeapon() = default;

bool ForkEmitChmFieldFromWeapon::init_(sead::Heap* heap) {
    return ForkEmitChmField::init_(heap);
}

void ForkEmitChmFieldFromWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitChmField::enter_(params);
}

void ForkEmitChmFieldFromWeapon::leave_() {
    ForkEmitChmField::leave_();
}

void ForkEmitChmFieldFromWeapon::loadParams_() {
    ForkEmitChmField::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
}

void ForkEmitChmFieldFromWeapon::calc_() {
    ForkEmitChmField::calc_();
}

bool ForkEmitChmFieldFromWeapon::m34(sead::Matrix34f* mtx) {
    if (mActor->getASList()->x(0x47, nullptr, *mTargetBone_s, *mSeqBank_s,
                               &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        sub_710014DFB0(mtx);
        return true;
    }
    return false;
}

// NON_MATCHING: the original reads the translation through the (null) weapon pointer in the no-weapon
// path (absolute loads at 0x3a4 / 0x3b4 / 0x3c4) and schedules the matrix products differently.
void ForkEmitChmFieldFromWeapon::sub_710014DFB0(sead::Matrix34f* mtx) {
    auto* weapon = sub_71005D83E8(mActor, 0);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    if (weapon) {
        sead::Vector3f dir;
        weapon->sub_71002E5DDC(&dir);
        pos.setMul(weapon->getMtx(), dir);
    }
    *mtx = mActor->getMtx();
    const sead::Vector3f from(pos.x, pos.y + 1.0f, pos.z);
    const sead::Vector3f to(pos.x, pos.y - 1.0f, pos.z);
    sead::Vector3f hit;
    if (sub_710072EB10(from, to, ksys::phys::RayCast::NormalCheckingMode::_0, mActor, &hit, nullptr,
                       nullptr, 0.0f)) {
        mtx->m[0][3] = hit.x;
        mtx->m[1][3] = hit.y;
        mtx->m[2][3] = hit.z;
    } else {
        mtx->m[0][3] = to.x;
        mtx->m[1][3] = to.y;
        mtx->m[2][3] = to.z;
    }
}

}  // namespace uking::action
