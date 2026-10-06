#include "Game/AI/Action/actionFadeInOutWithOptions.h"
#include "Game/Actor/actRideable.h"
#include <gsys/gsysModel.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

FadeInOutWithOptions::FadeInOutWithOptions(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FadeInOutWithOptions::~FadeInOutWithOptions() = default;

bool FadeInOutWithOptions::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: only the first lines differ (the original loads the start frame through an integer register
// (`ldr w9; fmov s1, w9; str w9`) and builds the 2 / 1 state selection earlier); the rest is identical.
void FadeInOutWithOptions::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 start = *mFadeStartFrame_s;
    _68 = start;
    const f32 finish = *mFadeFinishFrame_s;
    _6c = finish < start ? start + 1.0f : finish;
    _64 = 1.0f / (_6c - _68);
    _70 = 0.0f;
    _74 = start == 0.0f ? 2 : 1;

    if (*mFadeType_s == 0) {
        auto* actor = mActor;
        auto* model = actor->getModel();
        if (!model) {
            setFailed();
            return;
        }
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        model->sub_7100BF8C58(true, -1);
        if (*mToggleCollision_s) {
            auto* body_set = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
            auto* controller = mActor->getCharacterController();
            if (body_set && controller) {
                body_set->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
                body_set->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
                body_set->disableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
                body_set->disableContactLayer(ksys::phys::ContactLayer::EntityObject);
                body_set->disableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
                controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
                controller->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
                controller->disableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
                controller->disableContactLayer(ksys::phys::ContactLayer::EntityObject);
                controller->disableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
                sub_71007A3540(mActor);
            }
        }
        if (*mToggleEffects_s) {
            mActor->getXLink()->toggle(true);
            mActor->getXLink()->_cc.set(4);
        }
    }

    if (*mToggleHorseOptions_s) {
        if (auto* rideable = mActor->getHorseOptionsMaybe())
            rideable->Unk_7100e8b2b8::_8 = 0x200;
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D8EEE0();
    }
}

void FadeInOutWithOptions::leave_() {
    if (*mFadeType_s != 0 || !*mToggleHorseOptions_s)
        return;
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->Unk_7100e8b2b8::_8 &= ~0x200;
}

void FadeInOutWithOptions::loadParams_() {
    getStaticParam(&mFadeType_s, "FadeType");
    getStaticParam(&mFadeStartFrame_s, "FadeStartFrame");
    getStaticParam(&mFadeFinishFrame_s, "FadeFinishFrame");
    getStaticParam(&mToggleAttention_s, "ToggleAttention");
    getStaticParam(&mToggleAwareness_s, "ToggleAwareness");
    getStaticParam(&mToggleEffects_s, "ToggleEffects");
    getStaticParam(&mToggleCollision_s, "ToggleCollision");
    getStaticParam(&mToggleHorseOptions_s, "ToggleHorseOptions");
}

void FadeInOutWithOptions::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
