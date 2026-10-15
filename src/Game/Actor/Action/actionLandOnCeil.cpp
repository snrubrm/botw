#include "Game/Actor/Action/actionLandOnCeil.h"
#include <prim/seadStringUtil.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace uking::action {

LandOnCeil::LandOnCeil(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LandOnCeil::~LandOnCeil() = default;

bool LandOnCeil::init_(sead::Heap* heap) {
    _80 = ksys::phys::System::instance()->getField48();
    return true;
}

void LandOnCeil::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LandOnCeil::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EE1C(_80);
        controller->sub_7100F5EEB8(_90);
        controller->sub_7100F5E754(true);
        controller->sub_7100F5EDE8(sead::Vector3f::ey);
    }
}

void LandOnCeil::loadParams_() {
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

bool LandOnCeil::isFinished() const {
    auto* actor = mActor;
    sead::Vector3f up;
    actor->getMtx().getBase(up, 1);
    up.normalize();

    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_8c != 2)
        return false;
    if (isLandedMaybe(actor, false) || isBgGroundHit(actor, false))
        return up.dot(_44) >= 0.99984771f;
    return false;
}

// NON_MATCHING: state blocks, parsed height lifetime and gravity temporary stores.
void LandOnCeil::calc_() {
    auto* actor = mActor;
    sub_710073FA94(&_5c, actor);
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (_8c == 3) {
        if (isBgGroundHit(actor, false)) {
            sub_71007377D4(controller, 0.0f);
            sub_7100738660(controller, 0.0f);
            sead::Vector3f front;
            actor->getMtx().getBase(front, 2);
            front.normalize();
            sub_710072C1B4(controller, front);
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1);
            setFinished();
        } else {
            sead::Vector3f front;
            actor->getMtx().getBase(front, 2);
            front.normalize();
            sead::Matrix34f transform;
            ksys::util::sub_71011F0260(&transform, front, _44, _38, false);
            controller->sub_7100F5F938(transform);
        }
        return;
    }
    auto* as_list = actor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    ksys::as::ASList::Unk4 query;
    if (_8c != 2 && as_list->x(68, &query, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        f32 height;
        if (!sead::StringUtil::tryParseF32(&height, query.name))
            height = 1.0f;
        _8c = 1;
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        sead::Vector3f gravity;
        sub_710072DC50(&gravity, mActor);
        gravity *= 1.0f / 900.0f;
        const f32 speed = sub_710072D068(&gravity, height);
        sub_7100737710(controller, {0.0f, speed, 0.0f});
    }
    if (sub_71005DD5B0(actor, 41, nullptr, 0, 0)) {
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        _8c = 2;
        controller->sub_7100F5EEB8(*mGravityScale_s);
    }
    if (_8c == 2)
        sub_71001CD210(actor, controller);
    if (_8c != 0) {
        sub_7100737C0C(controller, 0.2f, -sead::Vector3f::ey);
    } else {
        sub_71007377D4(controller, 0.2f);
        sub_7100738660(controller, 0.2f);
    }
}

}  // namespace uking::action
