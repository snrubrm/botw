#include "Game/AI/Action/actionAreaRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::action {

AreaRoot::AreaRoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AreaRoot::~AreaRoot() = default;

// NON_MATCHING: the original copies the translation as one 8+4-byte block
bool AreaRoot::init_(sead::Heap* heap) {
    _9d.reset(2);
    if (auto* obj = ksys::act::findLinkReferenceObj(mActor, "ForceSetPosDirAutoSaveAnchor",
                                                    sead::SafeString::cEmptyString, nullptr)) {
        _80 = obj->getTranslate();
        _8c = obj->getRotate();
        _9d.set(2);
    }
    _9c = 1;
    if (mActor)
        mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, *mForceCalcInEvent_m);
    return true;
}

void AreaRoot::loadParams_() {
    getStaticParam(&mAutoSaveInterval_s, "AutoSaveInterval");
    getMapUnitParam(&mCameraPriority_m, "CameraPriority");
    getMapUnitParam(&mAutoSave_m, "AutoSave");
    getMapUnitParam(&mForceCalcInEvent_m, "ForceCalcInEvent");
    getMapUnitParam(&mCameraSet_m, "CameraSet");
    getMapUnitParam(&mShape_m, "Shape");
    getMapUnitParam(&mWarpDestMapName_m, "WarpDestMapName");
    getMapUnitParam(&mWarpDestPosName_m, "WarpDestPosName");
}

void AreaRoot::calc_() {
    ksys::act::ai::Action::calc_();
}

void AreaRoot::m9() {
    if (mActor)
        mActor->setFlag(ksys::act::Actor::ActorFlag::_1c, *mForceCalcInEvent_m);
}

}  // namespace uking::action
