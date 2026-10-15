#include "Game/Actor/Action/actionAnimMatrixDriven.h"
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <limits>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

AnimMatrixDriven::AnimMatrixDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimMatrixDriven::~AnimMatrixDriven() = default;

bool AnimMatrixDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimMatrixDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = false;
    if (*mIsChangeable_d)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    playAS(mASName_d.cstr(), *mIsIgnoreSame_d, *mASSlot_d, *mSequenceBank_d, -1.0f);
    if (*mStartFrame_d >= 0.0f) {
        mActor->getASList()->x_3(*mASSlot_d, *mSequenceBank_d,
                                 &ksys::as::ASList::Unk2::sub_7101163298, *mStartFrame_d);
    }

    sead::SafeString bone_name = "";
    const auto& key = as_list->_14;
    if (key.isValid()) {
        bone_name = mActor->getModel()
                        ->getUnits()
                        .unsafeAt(key.model_unit_index)
                        ->mModelUnit->getBoneName(key.bone_index);
    }
    if (bone_name != "Root") {
        as_list->sub_710115CE44("Root");
        _58 = true;
        if (!as_list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_710002E82C) ||
            !as_list->_14.isValid()) {
            setFailed();
            return;
        }
    }
    _59 = true;
}

void AnimMatrixDriven::leave_() {
    if (_58) {
        _58 = false;
        mActor->getASList()->sub_710115D0AC();
    }
}

void AnimMatrixDriven::loadParams_() {
    getDynamicParam(&mASSlot_d, "ASSlot");
    getDynamicParam(&mSequenceBank_d, "SequenceBank");
    getDynamicParam(&mStartFrame_d, "StartFrame");
    getDynamicParam(&mIsIgnoreSame_d, "IsIgnoreSame");
    getDynamicParam(&mIsChangeable_d, "IsChangeable");
    getDynamicParam(&mASName_d, "ASName");
}

// NON_MATCHING: world-cell offset arithmetic and actor/map position load scheduling.
void AnimMatrixDriven::calc_() {
    auto* as_list = mActor->getASList();
    if (!as_list || !as_list->_14.isValid()) {
        setFailed();
        return;
    }
    as_list->sub_710115C7A8(false);
    as_list->sub_710115C8D8(false, false);
    as_list->sub_710115C934();
    sead::Matrix34f transform = as_list->_80;
    auto* actor = mActor;
    const f32 x = actor->getMapObject() ? actor->getMapObject()->getTranslate().x :
                                       actor->getMtx().m[0][3];
    const f32 z = actor->getMapObject() ? actor->getMapObject()->getTranslate().z :
                                       actor->getMtx().m[2][3];
    const sead::Vector3f offset{
        (x >= 0.0f ? 1.0f : -1.0f) *
            (sead::Mathf::floor(sead::Mathf::abs(x) / 1000.0f) * 1000.0f + 500.0f),
        0.0f,
        (z >= 0.0f ? 1.0f : -1.0f) *
            (sead::Mathf::floor(sead::Mathf::abs(z) / 1000.0f) * 1000.0f + 500.0f)};
    transform.m[0][3] += offset.x;
    transform.m[1][3] += offset.y;
    transform.m[2][3] += offset.z;
    if (_59) {
        _59 = false;
        actor->actorPhysicsSetFlag2();
        if (auto* controller = mActor->getCharacterController())
            controller->sub_7100F60500(transform);
        else if (auto* body = mActor->getMainBody())
            body->setTransform(transform, ksys::phys::PropagateToLinkedMotions{true});
        else
            mActor->sub_71011C88C0(transform);
    } else {
        if (auto* controller = actor->getCharacterController())
            controller->sub_7100F5F938(transform);
        else if (auto* body = mActor->getMainBody())
            body->changePositionAndRotation(transform, std::numeric_limits<f32>::epsilon());
        else
            mActor->sub_71011C88C0(transform);
    }
    if (mASName_d == as_list->x_1(0, 0) && isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
