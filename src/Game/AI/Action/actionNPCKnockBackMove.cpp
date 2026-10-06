#include "Game/AI/Action/actionNPCKnockBackMove.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

NPCKnockBackMove::NPCKnockBackMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCKnockBackMove::~NPCKnockBackMove() = default;

void NPCKnockBackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _38 = controller->get64();
    sead::Vector3f dir = *mMoveDir_d;
    dir.normalize();
    sub_710072C1B4(controller, dir);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
    controller->sub_7100F5EDD8(1.0f);
    playAS(mASKeyName_s.cstr(), false, 0, 0, -1.0f);
}

void NPCKnockBackMove::loadParams_() {
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mMoveDir_d, "MoveDir");
}

void NPCKnockBackMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    auto* navmesh = mActor->m45();
    if (!navmesh) {
        setFailed();
        return;
    }
    if (isFinishedAS(0, 0)) {
        setFinished();
        return;
    }
    sead::Vector3f anim_move = mActor->getASList()->sub_710115D2D4();
    sead::Matrix34f mtx;
    controller->physicsXXXGetMtx_1(&mtx);
    anim_move.rotate(mtx);
    sead::Vector3f back;
    mActor->getMtx().getBase(back, 2);
    back = -back;
    f32 speed = sead::Vector2f(anim_move.x, anim_move.z).length();
    const f32 distance = speed + navmesh->_2a8 * navmesh->_2ac;
    if (mActor->sub_71011C7A98())
        speed *= mActor->get830();
    const bool blocked = sub_710072FEC4(mActor, back, distance, nullptr, true, nullptr);
    sub_7100737708(controller, blocked ? 0.0f : speed);
    controller->sub_7100F5FB24(sead::Vector3f::zero);
}

}  // namespace uking::action
