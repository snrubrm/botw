#include "Game/AI/Action/actionMimicFreeze.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

MimicFreeze::MimicFreeze(const InitArg& arg) : Freeze(arg) {}

MimicFreeze::~MimicFreeze() = default;

void MimicFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_e84.isOnBit(16)) {
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F62BB0();
        }
    }
}

void MimicFreeze::leave_() {
    Freeze::leave_();
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.reset(0x10000);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62BB8();
}

void MimicFreeze::loadParams_() {
    Freeze::loadParams_();
}

}  // namespace uking::action
