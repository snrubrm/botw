#include "Game/AI/Action/actionEquipedQuiver.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actOptionalWeapon.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EquipedQuiver::EquipedQuiver(const InitArg& arg) : EquipedOptionalWeaponAction(arg) {}

EquipedQuiver::~EquipedQuiver() = default;

void EquipedQuiver::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
    playAS("Equiped", false, 0, 0, -1.0f);
    s32 count;
    sub_710010FD20(&count);
    if (count >= 4)
        mActor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
    else
        mActor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, f32(4 - count));
}

bool EquipedQuiver::sub_710010FD20(s32* count) {
    if (auto* optional = sead::DynamicCast<uking::act::OptionalWeapon>(mActor)) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(optional->_840.getProc(nullptr, nullptr));
        if (auto* player = sead::DynamicCast<ksys::act::PlayerOrEnemy>(actor)) {
            const bool has_bow = optional->sub_7100EF1EA4();
            sead::FixedSafeString<32> name;
            if (player->m165(&name)) {
                *count = uking::ui::getPorchNum(name);
                if (*count > 0) {
                    *count = sead::Mathi::clampMin(*count - (has_bow ? 1 : 0), 0);
                    return true;
                }
            }
        }
    }
    *count = 0;
    return false;
}

void EquipedQuiver::calc_() {
    EquipedOptionalWeaponAction::calc_();
}

}  // namespace uking::action
