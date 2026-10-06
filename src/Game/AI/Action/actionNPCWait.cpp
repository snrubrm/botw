#include "Game/AI/Action/actionNPCWait.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actNPC.h"

namespace uking::action {

NPCWait::NPCWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCWait::~NPCWait() = default;

bool NPCWait::init_(sead::Heap* heap) {
    _38 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!m32().isEmpty())
        playAS(m32().cstr(), *mIsIgnoreSameKey_s, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5E7F0(0.0f);
    if (auto* nav = mActor->m45())
        nav->sub_7100F76778();
    mFlags.set(Flag::Changeable);
}

void NPCWait::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76790();
}

void NPCWait::loadParams_() {
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

const sead::SafeString& NPCWait::m32() {
    return mASName_s;
}

// NON_MATCHING: the original also copies x and z of the velocity through registers before storing y.
void NPCWait::calc_() {
    if (!mActor->getCharacterController()) {
        setFailed();
        return;
    }
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (act::NPC::isZora(mActor)) {
        auto* controller = mActor->getCharacterController();
        if (controller && _38 && (_38->_fe8 & 0x8000000)) {
            sead::Vector3f velocity;
            controller->sub_7100F5F598(&velocity);
            velocity.y = _38->_10a8;
            controller->sub_7100F5F6FC(velocity);
        }
    }
}

}  // namespace uking::action
