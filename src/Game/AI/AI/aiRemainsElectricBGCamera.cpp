#include "Game/AI/AI/aiRemainsElectricBGCamera.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RemainsElectricBGCamera::RemainsElectricBGCamera(const InitArg& arg)
    : RailMoveRemainsBGCamera(arg) {}

RemainsElectricBGCamera::~RemainsElectricBGCamera() {
    for (s32 i = 0; i < 4; ++i)
        _128[i].remove();
}

bool RemainsElectricBGCamera::init_(sead::Heap* heap) {
    return RailMoveRemainsBGCamera::init_(heap);
}

void RemainsElectricBGCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    _118.reset();
    for (s32 i = 0; i < 4; ++i)
        _128[i].remove();
    _208 = 0;
    RailMoveRemainsBGCamera::enter_(params);
}

void RemainsElectricBGCamera::leave_() {
    RailMoveRemainsBGCamera::leave_();
}

f32 RemainsElectricBGCamera::m43() {
    if (_118.hasProc()) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
        if (parent) {
            auto* as_list = parent->getASList();
            if (as_list && as_list->_14.isValid())
                return as_list->sub_710115D2D4().z;
        }
    }
    return 0.0f;
}

void RemainsElectricBGCamera::loadParams_() {
    RailMoveRemainsBGCamera::loadParams_();
    getStaticParam(&mParentActorName_s, "ParentActorName");
}

}  // namespace uking::ai
