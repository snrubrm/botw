#include "Game/AI/AI/aiMasterSwordRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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

// NON_MATCHING: the original copies Vector3f::zero to a stack temporary before each addVec3 (two
// named `const sead::Vector3f` copies reproduce it exactly; not applied, see lane1 log s65).
void MasterSwordRoot::sub_71004A3AFC() {
    auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
    if (!weapon)
        return;
    sub_7100E1EE94(ksys::phys::MotionType(2));
    ksys::act::ai::InlineParamPack params;
    params.addString(weapon->m164(), "NodeName", -1);
    params.addVec3(sead::Vector3f::zero, "RotOffset", -1);
    params.addVec3(sead::Vector3f::zero, "TransOffset", -1);
    changeChild("マスターソードチャレンジ", &params);
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
