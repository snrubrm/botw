#include "Game/AI/Action/actionGiantDownSwingAttack.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

GiantDownSwingAttack::GiantDownSwingAttack(const InitArg& arg) : GiantAttackWithAS(arg) {}

GiantDownSwingAttack::~GiantDownSwingAttack() = default;

bool GiantDownSwingAttack::init_(sead::Heap* heap) {
    return GiantAttackWithAS::init_(heap);
}

void GiantDownSwingAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantAttackWithAS::enter_(params);
}

void GiantDownSwingAttack::leave_() {
    GiantAttackWithAS::leave_();
}

void GiantDownSwingAttack::loadParams_() {
    GiantAttackWithAS::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

void GiantDownSwingAttack::calc_() {
    GiantAttackWithAS::calc_();
}

void GiantDownSwingAttack::m32(const sead::SafeString* name) {
    sub_71005D7ADC(mActor, *mWeaponIdx_s, 0xc, name, nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
}

void GiantDownSwingAttack::m33() {
    sub_71005D79AC(mActor, *mWeaponIdx_s, act::Unk_71002edaec(1));
}

}  // namespace uking::action
