#include "Game/AI/AI/aiMiniGolemSleep.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102450410.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

MiniGolemSleep::MiniGolemSleep(const InitArg& arg) : SpecialEnemySleep(arg) {}

MiniGolemSleep::~MiniGolemSleep() = default;

bool MiniGolemSleep::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void MiniGolemSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e90 = 1;
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(0xc00);
    ksys::act::disableAllAttClients(mActor);
    _68.x();
    if (auto* controller = sead::DynamicCast<Unk_7102450410>(
            *static_cast<Unk_71025afb58**>(mGolemChemicalController_a))) {
        for (auto& entry : controller->_8)
            entry.sub_7100708B64();
    }
}

void MiniGolemSleep::calc_() {
    SpecialEnemySleep::calc_();
}

void MiniGolemSleep::leave_() {
    SpecialEnemySleep::leave_();
}

void MiniGolemSleep::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

bool MiniGolemSleep::handleMessage_(const ksys::Message* message) {
    return _68.m2(*message);
}

bool MiniGolemSleep::m36() {
    return _68._30;
}

}  // namespace uking::ai
