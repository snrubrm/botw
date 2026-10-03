#include "Game/AI/AI/aiAnimalEscapeAfterDamage.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

AnimalEscapeAfterDamage::AnimalEscapeAfterDamage(const InitArg& arg) : AnimalEscapeAI(arg) {}

AnimalEscapeAfterDamage::~AnimalEscapeAfterDamage() = default;

bool AnimalEscapeAfterDamage::init_(sead::Heap* heap) {
    return AnimalEscapeAI::init_(heap);
}

void AnimalEscapeAfterDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalEscapeAI::enter_(params);
}

void AnimalEscapeAfterDamage::calc_() {
    AnimalEscapeAI::calc_();
}

void AnimalEscapeAfterDamage::leave_() {
    AnimalEscapeAI::leave_();
}

void AnimalEscapeAfterDamage::loadParams_() {
    AnimalEscapeAI::loadParams_();
}

void AnimalEscapeAfterDamage::m36() {
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        sub_7100304854();
    else
        AnimalEscapeAI::m36();
}

void AnimalEscapeAfterDamage::sub_7100304854() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f dir(controller->get64().x, 0.0f, controller->get64().z);
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= 5.0f / length;
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f target;
    {
        sead::Vector3f pos;
        controller->sub_7100F5F6E0(&pos);
        target = pos + dir;
    }
    params.addVec3(target, "TargetPos", -1);
    changeChild("ダメージ後", &params);
}

bool AnimalEscapeAfterDamage::m37() {
    return AnimalEscapeAI::m37() || isCurrentChild("ダメージ後");
}

}  // namespace uking::ai
