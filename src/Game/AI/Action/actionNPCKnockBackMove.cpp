#include "Game/AI/Action/actionNPCKnockBackMove.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

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
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
