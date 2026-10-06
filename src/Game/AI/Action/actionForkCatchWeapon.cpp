#include "Game/AI/Action/actionForkCatchWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

ForkCatchWeapon::ForkCatchWeapon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkCatchWeapon::~ForkCatchWeapon() = default;

bool ForkCatchWeapon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkCatchWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkCatchWeapon::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkCatchWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mIsNoGrabSuccess_s, "IsNoGrabSuccess");
}

void ForkCatchWeapon::calc_() {
    auto* list = mActor->getASList();
    if (!list)
        return;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(mTargetActor_d->getProc(nullptr, nullptr));
    if (!list->x(69, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        return;

    if (actor && !actor->isSleep()) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(actor);
        if (weapon && !sub_71005DEC08(mTargetActor_d, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
            if (sub_71005D8A30(mActor, weapon, *mWeaponIdx_s)) {
                setFinished();
                return;
            }
        }
    }

    if (*mIsNoGrabSuccess_s)
        setFinished();
    else
        setFailed();
}

}  // namespace uking::action
