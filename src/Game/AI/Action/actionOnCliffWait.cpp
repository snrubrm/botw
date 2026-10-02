#include "Game/AI/Action/actionOnCliffWait.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

OnCliffWait::OnCliffWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnCliffWait::~OnCliffWait() = default;

bool OnCliffWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OnCliffWait::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (auto* cc = mActor->getCharacterController()) {
        _40 = cc->sub_7100F5F0E4();
        cc->sub_7100F5F458(ksys::act::MotionType::Hover);
    }
    mFlags.set(Flag::Changeable);
}

void OnCliffWait::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5F458(_40);
}

void OnCliffWait::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void OnCliffWait::calc_() {
    auto* actor = mActor;
    if (auto* controller = actor->getCharacterController()) {
        sub_71007377D4(controller, *mPosReduceRatio_s);
        sub_7100738660(controller, *mAngReduceRatio_s);
    } else if (auto* body = actor->getMainBody()) {
        sub_71007379FC(body, *mPosReduceRatio_s);
        sub_7100738898(body, *mAngReduceRatio_s);
    }
}

}  // namespace uking::action
