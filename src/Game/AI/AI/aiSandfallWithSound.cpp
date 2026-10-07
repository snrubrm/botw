#include "Game/AI/AI/aiSandfallWithSound.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace uking::ai {

SandfallWithSound::SandfallWithSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandfallWithSound::~SandfallWithSound() {
    if (_38) {
        _38->destroy();
        _38 = nullptr;
    }
}

bool SandfallWithSound::init_(sead::Heap* heap) {
    _38 = aal::ShapeSegment::create("Sandfall", heap);
    if (_38) {
        _38->mFlags.resetBit(aal::Shape::KeepPosition);
        _38->mFlags.resetBit(aal::Shape::KeepRotation);
        sub_7100556370();
    }
    return true;
}

void SandfallWithSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandfallWithSound::calc_() {
    sub_7100556370();
    sub_710055646C();
}

// NON_MATCHING: stack placement and scheduling of the height and position temporaries differ.
void SandfallWithSound::sub_7100556370() {
    if (!_38)
        return;
    auto* placement = ksys::map::PlacementMgr::instance();
    if (!placement || !placement->mTeraSystem || !mActor)
        return;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    f32 height = 0;
    const sead::Vector2f xz{pos.x, pos.z};
    ksys::tera::sub_71011094A0(&height, &xz, placement->mTeraSystem, -1, 0);
    _60 = {pos.x, height, pos.z};
    _38->setPosition(pos);
    const sead::Vector3f direction = _60 - pos;
    _38->setVector(direction);
}

// 0x710055646c
void SandfallWithSound::sub_710055646C() {
    auto* actor = mActor;
    if (!_40.isActive()) {
        _40 = ksys::eft::searchAndEmitSLink(actor, "Sandfall", false);
        if (_40.isActive())
            _40.getEvent()->resetFlagBit(1);
    }
    if (_40.isActive()) {
        if (auto* executor =
                static_cast<xlink2::EventSLink*>(_40.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (source->mState <= 2 && _38)
                    source->mSpatialSetting.setShape(_38);
    }
    if (!_50.isActive())
        _50 = ksys::eft::searchAndEmitSLink(actor, "Basin", false);
    if (_50.isActive())
        _50.setPosition(_60);
}

// 0x71005565d8
void SandfallWithSound::sub_71005565D8() {
    if (_40.isActive()) {
        if (auto* executor =
                static_cast<xlink2::EventSLink*>(_40.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
        _40.fade();
        _50.fade();
    }
}

void SandfallWithSound::leave_() {
    sub_71005565D8();
}

void SandfallWithSound::loadParams_() {}

}  // namespace uking::ai
