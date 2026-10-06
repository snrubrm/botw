#include "Game/AI/Action/actionForkASTrgWeaponDrop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actUnk_7102376d50.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
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

// NON_MATCHING: the original keeps the address of `info` in a callee-saved register and lays out the
// "all weapon slots are -1" fallback after the function (same extra register as ForkDropWeapon::sub_710014CE28).
void ForkASTrgWeaponDrop::sub_7100146880() {
    const sead::Vector3f velocity{0.0f, -0.1f, 0.0f};
    uking::act::Unk_7102376d50 info;
    info.mFlags.setDirect(*mIsKeepRemind_s);
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor)
        return;
    if (*mWeaponIdx_s[0] >= 0) {
        actor->dropWeapon(0, velocity, false, false, &info, false);
    } else if (*mWeaponIdx_s[1] < 0 && *mWeaponIdx_s[2] < 0 && *mWeaponIdx_s[3] < 0) {
        actor->sub_7100007A1C(sead::Vector3f::zero, false, false, &info, false);
        return;
    }
    if (*mWeaponIdx_s[1] >= 0)
        actor->dropWeapon(1, velocity, false, false, &info, false);
    if (*mWeaponIdx_s[2] >= 0)
        actor->dropWeapon(2, velocity, false, false, &info, false);
    if (*mWeaponIdx_s[3] >= 0)
        actor->dropWeapon(3, velocity, false, false, &info, false);
}

void ForkASTrgWeaponDrop::calc_() {
    if (sub_71005DD780(mActor, 70, nullptr, 0, 0))
        sub_7100146880();
}

}  // namespace uking::action
