#include "Game/Actor/Action/actionAnimalASPlayCheckMoveDir.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnimalASPlayCheckMoveDir::AnimalASPlayCheckMoveDir(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalASPlayCheckMoveDir::~AnimalASPlayCheckMoveDir() = default;

bool AnimalASPlayCheckMoveDir::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalASPlayCheckMoveDir::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimalASPlay::enter_(params);
}

void AnimalASPlayCheckMoveDir::leave_() {
    ForkAnimalASPlay::leave_();
}

void AnimalASPlayCheckMoveDir::loadParams_() {
    ForkAnimalASPlay::loadParams_();
}

// NON_MATCHING: direction/matrix stack slots and vector/clamp scheduling.
void AnimalASPlayCheckMoveDir::calc_() {
    ForkAnimalASPlay::calc_();
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (!as_list || !controller || !rideable) {
        setFailed();
        return;
    }
    if (rideable->_8.load() & 4) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDE0(0.0f);
        return;
    }
    const sead::Vector3f motion = as_list->sub_710115D2D4();
    sead::Vector3f direction;
    direction.setRotated(mActor->getMtx(), motion);
    const f32 distance = direction.normalize();
    f32 x = motion.x;
    f32 z = motion.z;
    if (sub_710072FEC4(mActor, direction, distance, nullptr, true, nullptr)) {
        x = 0.0f;
        z = 0.0f;
    }
    sead::Vector3f front;
    sub_71000891C8(&front, mActor);
    controller->sub_7100F5EDBC(front);
    if (x == 0.0f && z == 0.0f) {
        controller->sub_7100F5E7F0(0.0f);
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDE0(0.0f);
    } else if (sead::Mathf::abs(z) >= sead::Mathf::abs(x)) {
        controller->sub_7100F5E7F0(z * 30.0f);
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDE0(sead::Mathf::clamp(x / z, -1.0f, 1.0f));
    } else {
        controller->sub_7100F5E7F0(x * 30.0f);
        controller->sub_7100F5EDD8(sead::Mathf::clamp(z / x, -1.0f, 1.0f));
        controller->sub_7100F5EDE0(1.0f);
    }
    const auto& rotation = as_list->sub_710115D3B8();
    sead::Matrix34f transform;
    ksys::util::sub_71011F0260(&transform, front, sead::Vector3f::ey, sead::Vector3f::zero, false);
    sead::Vector3f angular_velocity;
    angular_velocity.setRotated(transform, rotation);
    controller->sub_7100F5FB24(angular_velocity);
}

}  // namespace uking::action
