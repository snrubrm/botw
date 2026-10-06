#include "Game/AI/Action/actionPlayerCaught.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

// 0x7100eeb19c (declared only; 416 B): finds the contact point of `body` in its contact list (a3: its position, a4:
// its normal-like vector; the null pointers are optional outputs).
bool sub_7100EEB19C(ksys::phys::RigidBody* body, sead::Vector3f* a2, sead::Vector3f* a3,
                    sead::Vector3f* a4, void* a5, void* a6, void* a7);

PlayerCaught::PlayerCaught(const InitArg& arg) : PlayerAction(arg) {}

PlayerCaught::~PlayerCaught() = default;

void PlayerCaught::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(26);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("SwimWait", true, -1.0f);
    auto* actor = mActor;
    _20.x(sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent()));
    _20._28 = sub_71005DC5AC(actor).cstr();
    _20._30 = "Skl_Root";
    _20._38 = -1;
    _20._40 = sub_71005DC57C(actor);
    mActor->sub_71011DA824(&_20);
    mActor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC01B0();
}

void PlayerCaught::leave_() {
    mActor->resetConnectedCalcParent(false);
    mActor->sub_71011DA834(&_20);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FC012C(nullptr);
    static_cast<ksys::act::Player*>(mActor)->someFloatCalc(2.0f, sead::Vector3f(0.0f, 1.0f, 0.0f));
}

void PlayerCaught::calc_() {
    auto* actor = mActor;
    if (actor->getConnectedCalcParent()) {
        if (auto* parent = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcParent())) {
            if (parent->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40))
                actor->resetConnectedCalcParent(false);
        }
    } else {
        setFinished();
    }
    if (auto* controller = actor->getCharacterController()) {
        sead::Vector3f contact;
        if (sub_7100EEB19C(controller->sub_7100F61A34(), &contact, nullptr, nullptr, nullptr, nullptr,
                           nullptr)) {
            const sead::Vector3f position = actor->getMtx().getTranslation();
            sead::Vector3f center;
            controller->sub_7100F5F6E0(&center);
            if ((position - center).length() > 3.0f) {
                mActor->resetConnectedCalcParent(false);
                setFailed();
            }
        }
    }
}

bool PlayerCaught::isChangeable() const {
    return false;
}

}  // namespace uking::action
