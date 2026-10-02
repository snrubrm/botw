#include "Game/AI/Action/actionRemainsFireTailAttack.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

RemainsFireTailAttack::RemainsFireTailAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemainsFireTailAttack::~RemainsFireTailAttack() = default;

bool RemainsFireTailAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsFireTailAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    playAS(mASKeyName_s.cstr(), *mIsIgnoreSame_s, 0, 0, -1.0f);
}

void RemainsFireTailAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsFireTailAttack::loadParams_() {
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void RemainsFireTailAttack::calc_() {
    auto* actor = mActor;
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    if (auto* controller = actor->getCharacterController()) {
        sub_71007377D4(controller, 0.0f);
        sub_7100738660(controller, 0.0f);
    } else if (auto* body = actor->getMainBody()) {
        sub_71007379FC(body, 0.0f);
        sub_7100738898(body, 0.0f);
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
