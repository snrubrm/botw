#include "Game/AI/Action/actionAnmToRagdollDie.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

AnmToRagdollDie::AnmToRagdollDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmToRagdollDie::~AnmToRagdollDie() = default;

bool AnmToRagdollDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: only the stores of _58 / _5c / _60 differ (the original pairs _58 / _5c with `stp` and stores _60
// alone; ours merges the zero stores of _5c / _60 into one 64-bit store).
void AnmToRagdollDie::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = 1.0f;
    _5c = 0.0f;
    _64 = false;
    _60 = 0.0f;
    _65 = true;
    auto* actor = mActor;
    auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor);
    if (!dynamic_actor || !dynamic_actor->_868) {
        setFailed();
        return;
    }
    auto* handler = dynamic_actor->_868;
    dynamic_actor->_a68 &= ~1;
    if (handler->sub_71006ED9EC()) {
        dynamic_actor->getRagdollInstance()->x_22(-1, _5c);
        auto* physics = dynamic_actor->getPhysics();
        const s32 index = physics->sub_7100FBDA2C("full_key_framed");
        physics->sub_7100FBC838(index);
        physics->sub_7100FBDC24(index, mPosBaseRagdollRbName_s, 0.0f);
        _58 = -1.0f;
        physics->sub_7100FBDB90(physics->get112(), -1.0f);
        if (auto* controller = mActor->getCharacterController()) {
            controller->sub_7100F5F458(ksys::act::MotionType::Hover);
            controller->sub_7100F605F0();
            sead::Matrix34f mtx;
            controller->physicsXXXGetMtx_1(&mtx);
            controller->sub_7100F5F938(mtx);
        }
        _64 = true;
    } else if (actor->sub_71011CEA90()) {
        handler->sub_71006EDCB8();
    }
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void AnmToRagdollDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmToRagdollDie::loadParams_() {
    getStaticParam(&mChangeRagdollFrame_s, "ChangeRagdollFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mRagdollControllerName_s, "RagdollControllerName");
}

void AnmToRagdollDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
