#include "Game/AI/Action/actionAscendingCurrent.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

AscendingCurrent::AscendingCurrent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AscendingCurrent::~AscendingCurrent() {
    if (_68.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    if (_78) {
        _78->destroy();
        _78 = nullptr;
    }
    _28.sub_71010F17FC(false);
}

// NON_MATCHING: the original allocates the shape name's SafeString temporary before the locals (stack
// layout) and registers w22 / w23 the other way round for the translation copy.
bool AscendingCurrent::init_(sead::Heap* heap) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f size;
    m33(&size);
    sead::Vector3f up;
    mActor->getMtx().getBase(up, 1);
    up.normalize();
    pos += up * (size.y * 0.5f);
    _28.sub_71010F13AC(&pos, &size, &sead::Vector3f::zero, heap, nullptr);
    _28.sub_71010F1344(*mWindSpeed_s * 30.0f);
    _28.sub_71010F1364(&up);
    _78 = aal::ShapeCube::create("AscendingCurrent", heap);
    if (_78) {
        _78->mFlags.resetBit(aal::Shape::Flag::KeepPosition);
        _78->mFlags.resetBit(aal::Shape::Flag::KeepRotation);
        _78->setPosition(pos);
        _78->setRotate(sead::Vector3f::zero);
        _78->setVector(size);
    }
    return true;
}

void AscendingCurrent::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    m32();
    if (_28.mBody) {
        if (mActor->getXLink()) {
            mActor->getXLink()->sub_7101231468(0x19, mActor->getScale().x, false);
            mActor->getXLink()->sub_7101231468(0x1a, mActor->getScale().y, false);
            mActor->getXLink()->sub_7101231468(0x1b, *mWindSpeed_s * 30.0f, false);
        }
        _58 = ksys::eft::searchAndEmitELink(mActor, "Chemical_Updraft");
        sub_71000A6F24();
        sub_71000A71B0();
    }
}

void AscendingCurrent::leave_() {
    if (_68.getEvent()) {
        if (_68.isActive()) {
            if (auto* executor =
                    static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor())
                if (auto* source = executor->getHandle()->getSoundSource())
                    if (auto* calculator = source->mSpatialCalculator)
                        calculator->detachShape(true);
        }
        _68.fade();
    }
    _58.fade();
    _28.sub_71010F17FC(false);
}

void AscendingCurrent::loadParams_() {
    getStaticParam(&mWindSpeed_s, "WindSpeed");
}

void AscendingCurrent::calc_() {
    sub_71000A6F24();
    sub_71000A7354();
}

bool AscendingCurrent::hasUpdateForPreDeleteCb() {
    return true;
}

void AscendingCurrent::m32() {
    _28.sub_71010F16FC();
}

void AscendingCurrent::m33(sead::Vector3f* size) {
    *size = mActor->getScale() * 2;
}

void AscendingCurrent::m34(sead::Matrix34f* mtx) {
    mActor->getHomeMtx(mtx);
}

}  // namespace uking::action
