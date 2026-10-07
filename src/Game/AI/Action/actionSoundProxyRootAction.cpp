#include "Game/AI/Action/actionSoundProxyRootAction.h"
#include "Game/Actor/actSoundProxy.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include <aal/aalShape.h>
#include <heap/seadExpHeap.h>

namespace uking::action {

SoundProxyRootAction::SoundProxyRootAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundProxyRootAction::~SoundProxyRootAction() {
    if (_20) {
        if (auto* shape = _20->mShape) {
            _20->sub_710105A3F8();
            _20->sub_710105A0D0(nullptr);
            shape->destroy();
        }
    }
    if (_28) {
        _28->destroy();
        _28 = nullptr;
    }
    if (_38) {
        delete _38;
        _38 = nullptr;
    }
}

bool SoundProxyRootAction::init_(sead::Heap* heap) {
    auto* actor = mActor;
    _1c = false;
    if (!actor)
        return false;
    _28 = sead::ExpHeap::create(0x2d0, "SoundProxyRootAction", heap, 8,
                              sead::Heap::cHeapDirection_Forward, false);
    if (!_28)
        return false;
    _20 = sead::DynamicCast<uking::act::SoundProxy>(actor);
    if (!_20)
        return false;
    _38 = new (heap, 8) xlink2::HandleSLink;
    return true;
}

void SoundProxyRootAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor)
        _20->mSourceMapObject = mActor->getMapObject();
    sub_7100FF1DB4();
    if (_20 && _38 && !_38->isActive())
        _20->sub_710105A10C("Wait", _38);
    _1c = true;
}

void SoundProxyRootAction::leave_() {
    _1c = false;
    if (_38 && _20)
        _20->sub_710105A254(_38, -1);
    if (!_20)
        return;
    if (auto* shape = _20->mShape) {
        _20->sub_710105A3F8();
        _20->sub_710105A0D0(nullptr);
        shape->destroy();
        if (!_20)
            return;
    }
    _20->sub_710105A510();
}

void SoundProxyRootAction::loadParams_() {}

void SoundProxyRootAction::calc_() {
    if (_1c) {
        sub_7100FF1DB4();
        if (_20 && _38 && !_38->isActive())
            _20->sub_710105A10C("Wait", _38);
    }
}

void SoundProxyRootAction::sub_7100FF1DB4() {
    if (!mActor)
        return;
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return;
    auto* area = object->getLinkData()->sub_7100D4EFA4("Area");
    if (area && !sub_7100FF1E5C(area, _28)) {
        if (_20) {
            if (auto* shape = _20->mShape) {
                _20->sub_710105A3F8();
                _20->sub_710105A0D0(nullptr);
                shape->destroy();
            }
        }
        _30 = 0;
    }
}

}  // namespace uking::action
