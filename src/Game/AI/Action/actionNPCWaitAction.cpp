#include "Game/AI/Action/actionNPCWaitAction.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

NPCWaitAction::NPCWaitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void NPCWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!m32().isEmpty())
        playAS(m32().cstr(), *mIsIgnoreSameKey_s, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5E7F0(0.0f);
    if (auto* nav = mActor->m45())
        nav->sub_7100F76778();
    mFlags.set(Flag::Changeable);
}

void NPCWaitAction::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76790();
}

void NPCWaitAction::loadParams_() {
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

const sead::SafeString& NPCWaitAction::m32() {
    return mASName_s;
}

void NPCWaitAction::calc_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    else
        setFailed();
}

}  // namespace uking::action
