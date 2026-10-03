#include "Game/AI/AI/aiAnimalEscapeAfterDamage.h"
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

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

bool AnimalEscapeAfterDamage::m36() {
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        return sub_7100304854();
    return AnimalEscapeAI::m36();
}

// NON_MATCHING: the original leaves the return value unset on both paths (tail-calls setFailed and ends
// without setting w0); m36 returns this function's result
bool AnimalEscapeAfterDamage::sub_7100304854() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return false;
    }

    sead::Vector3f dir(controller->get64().x, 0.0f, controller->get64().z);
    const f32 length = dir.length();
    if (length > 0.0f)
        dir *= 5.0f / length;

    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f position;
    controller->sub_7100F5F6E0(&position);
    pack.addVec3(position + dir, "TargetPos", -1);
    changeChild("ダメージ後", &pack);
    return true;
}

bool AnimalEscapeAfterDamage::m37() {
    return AnimalEscapeAI::m37() || isCurrentChild("ダメージ後");
}

}  // namespace uking::ai
