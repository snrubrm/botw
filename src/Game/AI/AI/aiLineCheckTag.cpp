#include "Game/AI/AI/aiLineCheckTag.h"
#include "KingSystem/ActorSystem/actActor.h"
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

void LineCheckTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LineCheckTag::loadParams_() {
    getMapUnitParam(&mLineCheckType_m, "LineCheckType");
    getMapUnitParam(&mLineCheckVec_m, "LineCheckVec");
}

}  // namespace uking::ai
