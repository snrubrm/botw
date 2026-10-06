#include "Game/AI/AI/aiWaterSurfaceBase.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <math/seadBoundBox.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/BoxWater/physBoxWaterRigidBody.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

WaterSurfaceBase::WaterSurfaceBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaterSurfaceBase::~WaterSurfaceBase() {
    if (_40) {
        _40->destroy();
        _40 = nullptr;
    }
}

// NON_MATCHING: virtual-call argument scheduling differs in the bounds fallback.
bool WaterSurfaceBase::init_(sead::Heap* heap) {
    _40 = aal::ShapeCube::create("WaterSurface", heap);
    if (_40) {
        _40->mFlags.resetBit(aal::Shape::Flag::KeepPosition);
        _40->mFlags.resetBit(aal::Shape::Flag::KeepRotation);
        _40->setPosition(mActor->getMtx().getTranslation());
        if (auto* water = sead::DynamicCast<ksys::phys::BoxWaterRigidBody>(mActor->getMainBody())) {
            sead::Vector3f size = water->getExtents();
            size.y = 0.01f;
            _40->setVector(size);
        } else if (auto* body = mActor->getMainBody()) {
            sead::BoundBox3f box;
            body->getAabbInLocal(&box);
            _40->setVector(sead::Vector3f(box.getSizeX(), 0.01f, box.getSizeZ()));
        }
        sead::Matrix34f rotation = mActor->getMtx();
        rotation.setTranslation(sead::Vector3f::zero);
        _40->setRotate(rotation);
    }
    return true;
}

// NON_MATCHING: the home translation copy groups stores and changes cleanup scheduling.
void WaterSurfaceBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sub_71005ED41C();
    if (auto* list = actor->getASList()) {
        list->startAnimationMaybe(-1.0f, -1.0f, "Flow", 0, 0, true);
        list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, *mFlowSpeedFactor_m);
    }
    if (auto* water = sead::DynamicCast<ksys::phys::BoxWaterRigidBody>(actor->getMainBody()))
        water->_d8 = *mFlowSpeedFactor_m;
    _68 = actor->getHomeMtxRaw().getTranslation();
}

void WaterSurfaceBase::calc_() {
    auto* actor = mActor;
    if (!_48.isActive())
        sub_71005ED41C();
    if (_40) {
        const sead::Vector3f pos = actor->getMtx().getTranslation();
        _40->setPosition(pos);
    }
}

void WaterSurfaceBase::leave_() {
    if (_48.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_48.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    _48.fade();
}

void WaterSurfaceBase::sub_71005ED41C() {
    if (_48.isActive())
        return;
    auto* actor = mActor;
    auto* xlink = actor->getXLink();
    if (!xlink)
        return;
    auto* slink = xlink->_50;
    if (!slink)
        return;
    slink->setPropertyValue(3, *mFlowSpeedFactor_m);
    const bool is_dungeon = ksys::StageInfo::getCurrentMapType() == "CDungeon";
    const bool is_large = actor->getScale().length() >= 2.0f;
    if (!is_dungeon && is_large)
        _48 = ksys::eft::searchAndEmitSLink(actor, "waitWide", false);
    else
        _48 = ksys::eft::searchAndEmitSLink(actor, "wait", false);
    if (_48.isActive()) {
        _48.getEvent()->resetFlagBit(1);
        if (_40 && _48.isActive()) {
            if (auto* executor =
                    static_cast<xlink2::EventSLink*>(_48.getEvent())->getAliveAssetExecutor())
                if (auto* source = executor->getHandle()->getSoundSource())
                    source->mSpatialSetting.setShape(_40);
        }
    }
}

void WaterSurfaceBase::loadParams_() {
    getMapUnitParam(&mFlowSpeedFactor_m, "FlowSpeedFactor");
}

}  // namespace uking::ai
