#include "Game/Actor/Action/actionWaterUpDownAnmDrivenMove.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include <prim/seadStringUtil.h>
#include <limits>
#include <cmath>
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::action {

WaterUpDownAnmDrivenMove::WaterUpDownAnmDrivenMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaterUpDownAnmDrivenMove::~WaterUpDownAnmDrivenMove() = default;

bool WaterUpDownAnmDrivenMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterUpDownAnmDrivenMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _54.changeMotionType(_54.sub_710072ACF8(mActor), ksys::act::MotionType::Hover);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _5c._0 = -1.0f;
    _5c._4 = 0.5f;
    _5c.sub_7100700634(mActor);
}

f32 WaterUpDownAnmDrivenMove::sub_71002B7EEC() {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    sead::Vector3f start;
    mActor->getMtx().getTranslation(start);
    sead::Vector3f end = start;
    end.y -= 10.0f;
    query.setStart(start);
    query.setEnd(end);
    query.enableLayer(ksys::phys::ContactLayer::EntityWater);
    f32 y;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        sead::Vector3f hit;
        query.getHitPosition(&hit);
        y = hit.y;
    } else {
        y = end.y - 1.0f;
    }
    return y;
}

void WaterUpDownAnmDrivenMove::leave_() {
    _54.resetMotionType(_54.sub_710072ACF8(mActor));
}

void WaterUpDownAnmDrivenMove::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mTargetDepth_s, "TargetDepth");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: query and velocity temporaries have different stack slots; clamp lowering and
// parse-fallback blocks differ. The redundant native velocity reload/store is omitted.
void WaterUpDownAnmDrivenMove::calc_() {
    auto* as_list = mActor->getASList();
    ksys::phys::CharacterController* controller;
    if (!as_list || !(controller = mActor->getCharacterController())) {
        setFailed();
        return;
    }

    ksys::as::ASList::Unk4 query;
    if (as_list->x(0x2f, &query, 0, 0, &ksys::as::ASList::Unk2::sub_710116383C, true)) {
        f32 scale = 1.0f;
        constexpr f32 epsilon = std::numeric_limits<f32>::epsilon();
        if (!sead::StringUtil::tryParseF32(&scale, query.name) ||
            (scale <= epsilon && scale >= -epsilon))
            scale = 1.0f;
        f32 depth;
        if (mActor->getDepthInWater() > 0.0f)
            depth = mActor->getDepthInWater();
        else
            depth = sub_71002B7EEC() - mActor->getMtx()(1, 3);
        f32 movement = ((depth - *mInWaterDepth_s) - *mTargetDepth_s) / scale;
        if (movement <= 0.0f)
            movement = 0.0f;
        _50 = movement;
    }

    if (as_list->x(0x2f, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        velocity.y = as_list->sub_710115D2D4().y * 30.0f * _50;
        const f32 x_ratio = *mPosReduceRatio_s;
        if (x_ratio >= 0.0f)
            velocity.x *= std::pow(x_ratio, ksys::VFR::instance()->getDeltaFrame());
        else
            velocity.x *= -std::pow(-x_ratio, ksys::VFR::instance()->getDeltaFrame());
        const f32 z_ratio = *mPosReduceRatio_s;
        if (z_ratio >= 0.0f)
            velocity.z *= std::pow(z_ratio, ksys::VFR::instance()->getDeltaFrame());
        else
            velocity.z *= -std::pow(-z_ratio, ksys::VFR::instance()->getDeltaFrame());
        controller->sub_7100F5F6FC(velocity);
    } else {
        sub_7100738428(mActor, *mPosReduceRatio_s);
    }
    m32(controller);
    if (isFinishedAS(0, 0))
        setFinished();
    _5c.sub_7100700640(mActor);
}

void WaterUpDownAnmDrivenMove::m32(ksys::phys::CharacterController* controller) {
    sub_7100738AA8(mActor, *mRotReduceRatio_s);
}

}  // namespace uking::action
