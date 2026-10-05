#include "Game/AI/AI/aiIbutsuWaterFallRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::ai {

IbutsuWaterFallRoot::IbutsuWaterFallRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IbutsuWaterFallRoot::~IbutsuWaterFallRoot() {
    if (_40) {
        _40->destroy();
        _40 = nullptr;
    }
    if (_48) {
        _48->destroy();
        _48 = nullptr;
    }
    if (_50) {
        _50->destroy();
        _50 = nullptr;
    }
}

bool IbutsuWaterFallRoot::init_(sead::Heap* heap) {
    return sub_7100445394(heap);
}

bool IbutsuWaterFallRoot::sub_7100445394(sead::Heap* heap) {
    _40 = aal::ShapeCylinder::create("IbutsuWaterFall(River)", heap);
    if (!_40)
        return false;
    _40->mFlags.resetBit(aal::Shape::KeepPosition);
    _40->mFlags.resetBit(aal::Shape::KeepRotation);

    _48 = aal::ShapeCylinder::create("IbutsuWaterFall", heap);
    if (!_48)
        return false;
    _48->mFlags.resetBit(aal::Shape::KeepPosition);
    _48->mFlags.resetBit(aal::Shape::KeepRotation);

    _50 = aal::ShapeSphere::create("IbutsuWaterFall(Basin)", heap);
    if (!_50)
        return false;
    _50->mFlags.resetBit(aal::Shape::KeepPosition);
    _50->mFlags.resetBit(aal::Shape::KeepRotation);
    return true;
}

void IbutsuWaterFallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->checkBasicSig()) {
        changeChild("完全停止");
        _38 = false;
    } else {
        changeChild("通常");
        _38 = true;
    }
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.setBit(9);
    sub_7100445510();
}

void IbutsuWaterFallRoot::leave_() {
    sub_7100445AA0();
}

void IbutsuWaterFallRoot::calc_() {
    auto* actor = mActor;
    sub_710044584C();
    if (isCurrentChild("停止中"))
        actor->m107();
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("停止中")) {
        changeChild("完全停止");
        _38 = false;
    } else if (isCurrentChild("通常") && actor->checkBasicSig()) {
        mActor->m107();
        changeChild("停止中");
        _38 = true;
    }
}

void IbutsuWaterFallRoot::loadParams_() {}

}  // namespace uking::ai
