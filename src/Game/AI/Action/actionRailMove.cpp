#include "Game/AI/Action/actionRailMove.h"

#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RailMove::RailMove(const InitArg& arg) : RailMoveBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
RailMove::~RailMove() {
    ;
}

bool RailMove::init_(sead::Heap* heap) {
    return RailMoveBase::init_(heap);
}

void RailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rail = ksys::map::PlacementMgr::instance()->mPlacement18->sub_7100D48744(mRailName_d);
    if (!rail) {
        setFailed();
        return;
    }
    _68.sub_7100EEBAE0(rail, 0.0f);
    _68.x(0.5f);
    const auto& position = _68._30.sub_7100EEB370();
    _1c = position - mActor->getMtx().getTranslation();
    RailMoveBase::enter_(params);
}

void RailMove::leave_() {
    RailMoveBase::leave_();
}

void RailMove::loadParams_() {
    RailMoveBase::loadParams_();
    getDynamicParam(&mRailName_d, "RailName");
}

void RailMove::calc_() {
    RailMoveBase::calc_();
}

void RailMove::m32() {
    if (_68.sub_7100EEBB74()) {
        const sead::Vector3f& target = _68._30.sub_7100EEB370();
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        const f32 dx = target.x - pos.x;
        const f32 dz = target.z - pos.z;
        if (sead::Mathf::sqrt(dx * dx + dz * dz) < 1.0f)
            _68.x(0.5f);
        _1c = _68._30.sub_7100EEB370() - mActor->getMtx().getTranslation();
    }
}

}  // namespace uking::action
