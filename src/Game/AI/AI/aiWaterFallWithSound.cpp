#include "Game/AI/AI/aiWaterFallWithSound.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <gsys/gsysModel.h>
#include <math/seadBoundSphere.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

WaterFallWithSound::WaterFallWithSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaterFallWithSound::~WaterFallWithSound() {
    if (_38) {
        _38->destroy();
        _38 = nullptr;
    }
}

// inline-only in the original; name is a guess. init_ and calc_ both fit the capsule around the lower part of
// the model's bounding sphere.
void WaterFallWithSound::updateShapeFromModel_() {
    if (auto* model = mActor->getModel()) {
        sead::BoundSphere3f bounding;
        model->getBounding(&bounding);
        sead::Vector3f center = bounding.getCenter();
        const f32 radius = mActor->getScale().x * 3.0f;
        const f32 half_height = sead::Mathf::clampMin(bounding.getRadius() - radius, 0.0f);
        const sead::Vector3f axis(0.0f, half_height * 2, 0.0f);
        center.y -= half_height;
        _38->setPosition(center);
        _38->setVector(axis);
        _38->setRadius(radius);
    }
}

bool WaterFallWithSound::init_(sead::Heap* heap) {
    _38 = aal::ShapeCapsule::create("WaterFall", heap);
    if (_38) {
        _38->mFlags.resetBit(aal::Shape::Flag::KeepPosition);
        _38->mFlags.resetBit(aal::Shape::Flag::KeepRotation);
        if (_38)
            updateShapeFromModel_();
    }
    return true;
}

void WaterFallWithSound::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005EBEC0();
}

void WaterFallWithSound::calc_() {
    if (!_40.isActive())
        sub_71005EBEC0();
    if (_38)
        updateShapeFromModel_();
}

void WaterFallWithSound::leave_() {
    sub_71005EC090();
}

void WaterFallWithSound::sub_71005EBEC0() {
    auto* actor = mActor;
    if (_40.isActive())
        return;
    _40 = ksys::eft::searchAndEmitSLink(actor, "WaterFall", false);
    if (_40.isActive()) {
        _40.getEvent()->resetFlagBit(1);
        if (_38 && _40.isActive()) {
            if (auto* executor = static_cast<xlink2::EventSLink*>(_40.getEvent())->getAliveAssetExecutor())
                if (auto* source = executor->getHandle()->getSoundSource())
                    source->mSpatialSetting.setShape(_38);
        }
    }
}

void WaterFallWithSound::sub_71005EC090() {
    if (_40.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_40.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
        _40.fade();
    }
}

void WaterFallWithSound::loadParams_() {}

}  // namespace uking::ai
