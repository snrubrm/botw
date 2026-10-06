#include "Game/AI/AI/aiBoxWaterRoot.h"
#include <aal/aalShape.h>
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::ai {

// NON_MATCHING: the zero stores of the members come out in a different order (the original stores
// 0xa0 alone first, then pairs downward to 0x38; ours pairs 0xa0 with 0x98 and leaves 0x70 alone).
BoxWaterRoot::BoxWaterRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void BoxWaterRoot::m9() {
    sub_710033D4C8();
}

BoxWaterRoot::~BoxWaterRoot() {
    if (_50) {
        _50->destroy();
        _50 = nullptr;
    }
    if (_58) {
        _58->destroy();
        _58 = nullptr;
    }
    if (_38) {
        mActor->getPhysics()->sub_7100FC0600(_38);
        _38 = nullptr;
    }
    if (_40) {
        mActor->getPhysics()->sub_7100FC0600(_40);
        _40 = nullptr;
    }
    if (_48) {
        mActor->getPhysics()->sub_7100FC0600(_48);
        _48 = nullptr;
    }
}

bool BoxWaterRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BoxWaterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710033D4C8();
    if (_58 && (!mSoundInDoorType_m || *mSoundInDoorType_m == 0) &&
        (*mWaterMaterial_m == 3 || *mWaterMaterial_m == 0)) {
        if (auto* mgr = ksys::snd::SoundMgr::instance()) {
            if (mgr->_38 && mgr->_38->_30)
                mgr->_38->_30->sub_7101027D4C(mActor ? mActor->getScale().x : 0.0f, _58);
        }
    }
}

void BoxWaterRoot::calc_() {
    if (_58 && mSoundInDoorType_m && *mSoundInDoorType_m != 0 &&
        (!ksys::StageInfo::sIsFinalTrial || !mWaterMaterial_m || *mWaterMaterial_m == 3 ||
         *mWaterMaterial_m == 0)) {
        if (!_60.isActive()) {
            if (auto* mgr = ksys::snd::SoundMgr::instance()) {
                if (mgr->_38 && mgr->_38->_30) {
                    _60 = mgr->_38->_30->sub_7101027E90(mActor ? mActor->getScale().x : 0.0f,
                                                        *mSoundInDoorType_m, _58);
                }
            }
        }
    }
}

void BoxWaterRoot::leave_() {
    _60.fade();
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (mgr->_38 && mgr->_38->_30) {
            auto* shape = _50;
            if (_58)
                shape = _58;
            if (shape)
                mgr->_38->_30->sub_7101027E0C(shape);
        }
    }
    if (_38)
        _38->removeFromWorld();
    if (_40)
        _40->removeFromWorld();
    if (_48)
        _48->removeFromWorld();
}

void BoxWaterRoot::loadParams_() {
    getMapUnitParam(&mWaterMaterial_m, "WaterMaterial");
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
    getMapUnitParam(&mWaterfallRadius_m, "WaterfallRadius");
    getMapUnitParam(&mWaterfallLength_m, "WaterfallLength");
    getMapUnitParam(&mWaterfallThickness_m, "WaterfallThickness");
    getMapUnitParam(&mWaterfallAngle_m, "WaterfallAngle");
    getMapUnitParam(&mSoundInDoorType_m, "SoundInDoorType");
}

}  // namespace uking::ai
