#include "Game/AI/AI/aiLineCheckTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace uking::ai {

LineCheckTag::LineCheckTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LineCheckTag::~LineCheckTag() {
    if (_38) {
        _38->release();
        _38 = nullptr;
    }
}

bool LineCheckTag::init_(sead::Heap* heap) {
    _38 = ksys::phys::RayCastForRequest::allocRequest(nullptr, ksys::phys::GroundHit::HitAll);
    sub_7100483350();
    return true;
}

void LineCheckTag::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->m107();
    changeChild("オフ");
}

void LineCheckTag::sub_7100483350() {
    if (!_38)
        return;
    switch (*mLineCheckType_m) {
    case 0: {
        sead::Vector3f direction = *mLineCheckVec_m;
        const f32 length = direction.normalize();
        _38->setStartAndDisplacementScaled(mActor->getMtx().getTranslation() + direction * 0.1f, direction,
                                           length);
        ksys::act::sub_7100EEACE8(_38);
        break;
    }
    case 1: {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        ksys::act::sub_7100EEAFDC(_38, pos, 0);
        ksys::act::sub_7100EEAF80(_38);
        break;
    }
    }
}

void LineCheckTag::calc_() {
    mActor->m107();
    if (!_38) {
        _38 = ksys::phys::RayCastForRequest::allocRequest(nullptr, ksys::phys::GroundHit::HitAll);
        return;
    }
    if (_38->isRequestQueued())
        return;
    if (_38->get70() == 1) {
        if (_38->hasHit()) {
            if (isCurrentChild("オフ"))
                changeChild("オン");
        } else if (isCurrentChild("オン")) {
            changeChild("オフ");
        }
    }
    sub_7100483350();
    _38->submitRequest(ksys::phys::ContactLayerType::Entity);
}

void LineCheckTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LineCheckTag::loadParams_() {
    getMapUnitParam(&mLineCheckType_m, "LineCheckType");
    getMapUnitParam(&mLineCheckVec_m, "LineCheckVec");
}

}  // namespace uking::ai
