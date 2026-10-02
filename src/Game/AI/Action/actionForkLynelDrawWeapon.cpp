#include "Game/AI/Action/actionForkLynelDrawWeapon.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkLynelDrawWeapon::ForkLynelDrawWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkLynelDrawWeapon::~ForkLynelDrawWeapon() = default;

bool ForkLynelDrawWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkLynelDrawWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* as_list = actor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    if (auto* weapon = sub_71005D83E8(actor, *mASWeaponIdx_s))
        as_list->goLimpFromHeadShotMaybe(0x2c, weapon->getProfile(), 0);
    playAS(mASName_s.cstr(), false, *mTargetBone_s, *mSeqBank_s, -1.0f);
}

void ForkLynelDrawWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkLynelDrawWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx0_s, "WeaponIdx0");
    getStaticParam(&mWeaponIdx1_s, "WeaponIdx1");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mASWeaponIdx_s, "ASWeaponIdx");
    getStaticParam(&mASName_s, "ASName");
}

void ForkLynelDrawWeapon::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
