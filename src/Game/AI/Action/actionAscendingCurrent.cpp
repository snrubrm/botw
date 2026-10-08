#include "Game/AI/Action/actionAscendingCurrent.h"
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actReaction.h"
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

void AscendingCurrent::sub_71000A6F24() {
    sead::Matrix34f mtx;
    m34(&mtx);
    sead::Vector3f size;
    m33(&size);
    sead::Vector3f up;
    mtx.getBase(up, 1);
    up.normalize();
    sead::Vector3f pos = mtx.getTranslation();
    pos += up * (size.y * 0.5f);
    mtx.setTranslation(pos);
    _28.sub_71010F1364(&up);
    _28.sub_71010F15C8(&mtx);
    _28.sub_71010F1664(&size);
    if (mActor->getName() == "Obj_SupportApp_Wind") {
        sead::Matrix34f wind_mtx;
        wind_mtx.makeIdentity();
        wind_mtx.setTranslation(mtx.getTranslation());
        _58.setMatrix(wind_mtx, size);
    } else {
        _58.setMatrix(mtx, size);
    }
    if (_78) {
        _78->setPosition(pos);
        _78->setRotate(mtx);
        _78->setVector(size);
    }
}

void AscendingCurrent::calc_() {
    sub_71000A6F24();
    sub_71000A7354();
}

// NON_MATCHING: register allocation and scheduling order only; all calls, values and
// branches match.
void AscendingCurrent::sub_71000A71B0() {
    if (!_68.isActive()) {
        if (auto* xlink = mActor->getXLink()) {
            if (auto* user = xlink->_50)
                _68 = user->searchAndEmit("wind");
        }
    }
    if (!_68.isActive()) {
        auto* actor = ksys::act::Reaction::sInstance->_38;
        if (!actor)
            return;
        auto* xlink = actor->getXLink();
        if (!xlink)
            return;
        auto* user = xlink->_50;
        if (!user)
            return;
        user->setPropertyValue(25, mActor->getScale().x);
        user->setPropertyValue(26, mActor->getScale().y);
        user->setPropertyValue(27, *mWindSpeed_s * 30.0f);
        _68 = user->searchAndEmit("windAscending");
    }
    if (!_68.isActive())
        return;
    _68.getEvent()->resetFlagBit(1);
    if (_78) {
        if (auto* executor =
                static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor()) {
            if (auto* source = executor->getHandle()->getSoundSource())
                source->mSpatialSetting.setShape(_78);
        }
    }
}

// NON_MATCHING: register allocation and scheduling order only; all calls, values and
// branches match.
void AscendingCurrent::sub_71000A7354() {
    if (!_68.isActive())
        sub_71000A71B0();
    if (!_68.isActive())
        return;
    auto* executor =
        static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* source = executor->getHandle()->getSoundSource();
    if (!source)
        return;
    aal::Handle handle = source->getUnifiedSoundHandle();
    auto* unified = handle.getSoundSource();
    if (!unified)
        return;
    if (unified->mState <= 2)
        unified->setReleaseTime(1.0f);
    auto* supplier = unified->mSpeakerBalanceSupplier;
    if (!supplier)
        return;
    if (sead::DynamicCast<aal::SpeakerBalanceUnifier>(supplier))
        static_cast<aal::SpeakerBalanceUnifier*>(supplier)->setSpeakerBalanceMoveStep(2.0f);
}

bool AscendingCurrent::hasUpdateForPreDeleteCb() {
    return true;
}

bool AscendingCurrent::updateForPreDelete() {
    return _28.sub_71010F1314();
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
