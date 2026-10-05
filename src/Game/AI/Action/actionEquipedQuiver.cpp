#include "Game/AI/Action/actionEquipedQuiver.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EquipedQuiver::EquipedQuiver(const InitArg& arg) : EquipedOptionalWeaponAction(arg) {}

EquipedQuiver::~EquipedQuiver() = default;

// NON_MATCHING: The original branches on the arrow count; the natural conditional uses a float select.
void EquipedQuiver::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    playAS("Equiped", false, 0, 0, -1.0f);
    s32 count;
    sub_710010FD20(&count);
    mActor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298,
                           count < 4 ? f32(4 - count) : 0.0f);
}

void EquipedQuiver::calc_() {
    EquipedOptionalWeaponAction::calc_();
}

}  // namespace uking::action
