#include "Game/AI/Action/actionMoveByAnimeDrivenCheckNavMesh.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

MoveByAnimeDrivenCheckNavMesh::MoveByAnimeDrivenCheckNavMesh(const InitArg& arg)
    : MoveByAnimeDriven(arg) {}

MoveByAnimeDrivenCheckNavMesh::~MoveByAnimeDrivenCheckNavMesh() = default;

bool MoveByAnimeDrivenCheckNavMesh::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void MoveByAnimeDrivenCheckNavMesh::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
}

void MoveByAnimeDrivenCheckNavMesh::leave_() {
    MoveByAnimeDriven::leave_();
}

void MoveByAnimeDrivenCheckNavMesh::loadParams_() {
    MoveByAnimeDriven::loadParams_();
}

void MoveByAnimeDrivenCheckNavMesh::calc_() {
    MoveByAnimeDriven::calc_();
}

// NON_MATCHING: zero-vector equality loads the constant object and uses conditional compares.
void MoveByAnimeDrivenCheckNavMesh::m33() {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    if (!as_list || !controller)
        return;
    auto movement = as_list->sub_710115D2D4();
    auto angular_velocity = as_list->sub_710115D3B8();
    movement.rotate(mActor->getMtx());
    const f32 distance = movement.normalize();
    if (movement == sead::Vector3f::zero)
        movement = controller->get64();
    if (sub_710072FEC4(mActor, movement, distance, nullptr, true, nullptr)) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDE0(0.0f);
        controller->sub_7100F5EDBC(controller->get64());
        controller->sub_7100F5E7F0(0.0f);
        angular_velocity *= 30.0f;
        controller->sub_7100F5FB24(angular_velocity);
    } else {
        MoveByAnimeDriven::m33();
    }
}

}  // namespace uking::action
