#include "Game/AI/Action/actionForkDropWeaponWithSpeed.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkDropWeaponWithSpeed::ForkDropWeaponWithSpeed(const InitArg& arg) : ForkDropWeapon(arg) {}

ForkDropWeaponWithSpeed::~ForkDropWeaponWithSpeed() = default;

void ForkDropWeaponWithSpeed::calc_() {
    ForkDropWeapon::calc_();
    if (mActor->getASList()->sub_710115FBC8(70, nullptr, &ksys::as::ASList::Unk2::sub_71011637EC,
                                            true)) {
        sub_710014CE28();
    }
}

}  // namespace uking::action
