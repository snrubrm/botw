#include "Game/AI/Action/actionNPCTurnToObject.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

NPCTurnToObject::NPCTurnToObject(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTurnToObject::~NPCTurnToObject() = default;

void NPCTurnToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTurnToObject::sub_710020A5E4() {
    if (_61)
        return;
    switch (_40) {
    case 6:
    case 1:
        if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
            npc->sub_7100022D44(true, 1, sead::Vector3f::zero, nullptr, sead::Vector3f::zero);
        break;
    case 4:
        if (!_60) {
            if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
                npc->sub_7100022D44(true, 2, sead::Vector3f::zero, &_50, sead::Vector3f::zero);
        }
        break;
    }
    _61 = true;
}

void NPCTurnToObject::leave_() {
    sub_710020A5E4();
}

void NPCTurnToObject::loadParams_() {
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mTurnDirection_d, "TurnDirection");
    getDynamicParam(&mActorName_d, "ActorName");
}

// NON_MATCHING: register allocation / load order only (the original loads the z component of the front vector as an int
// before the x multiply, like PlayerTurnAndLookToObject::m40; `angle < abs_y` reproduces the branch).
void NPCTurnToObject::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    if (isFinished()) {
        sub_7100738AA8(mActor, 0.0f);
        return;
    }
    if (isFailed()) {
        sub_7100738AA8(mActor, 0.0f);
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    sead::Vector3f front(mActor->getMtx().m[0][2], 0.0f, mActor->getMtx().m[2][2]);
    front.normalize();
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, _44, sead::Vector3f::ey);
    const auto& anim_driven = mActor->getASList()->sub_710115D3B8();
    const f32 y = anim_driven.y;
    const f32 abs_y = y > 0.0f ? y : -y;
    if (angle < abs_y) {
        if (mActor->getName() == "Npc_MamonoShop")
            return;
        const sead::Vector3f velocity(0.0f, angle * axis.y * 30.0f, 0.0f);
        controller->sub_7100F5FB24(velocity);
    } else {
        const f32 x = anim_driven.x;
        const f32 z = anim_driven.z;
        if (!isFinishedAS(0, 0)) {
            const sead::Vector3f velocity(x * 30.0f, y * 30.0f, z * 30.0f);
            controller->sub_7100F5FB24(velocity);
            return;
        }
    }
    sub_710020A5E4();
    setFinished();
}

}  // namespace uking::action
