#include "aal/aalAttenuator.h"
#include <basis/seadNew.h>
#include "aal/aalAttenuationCulling.h"
#include "aal/aalAttenuationDirectivity.h"
#include "aal/aalAttenuationMgr.h"
#include "aal/aalAttenuationReader.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b8cb74
Attenuator* Attenuator::create(const sead::SafeString& name, sead::Heap* heap) {
    Attenuator* attenuator = new (heap, std::nothrow) Attenuator(name);
    if (!attenuator)
        return nullptr;
    return attenuator->initialize(heap) ? attenuator : nullptr;
}

// 0x7100b8ced0
Attenuator::Attenuator(const sead::SafeString& name) {
    setObjName(name);
}

// 0x7100b8d0fc (D2) / 0x7100b8d118 (D0)
Attenuator::~Attenuator() {
    finalize();
}

// NON_MATCHING: the original does not unroll the loop.
// 0x7100b8cbdc
bool Attenuator::initialize(sead::Heap* heap) {
    mDirectivityName = new (heap, std::nothrow) sead::FixedSafeString<32>;
    if (!mDirectivityName)
        return false;
    mCullingName = new (heap, std::nothrow) sead::FixedSafeString<32>;
    if (!mCullingName) {
        delete mDirectivityName;
        return false;
    }
    for (s32 i = 0; i < 5; ++i) {
        mCurves[i] = nullptr;
        mCurveNames[i] = new (heap, std::nothrow) sead::FixedSafeString<32>;
        if (!mCurveNames[i]) {
            delete mDirectivityName;
            delete mCullingName;
            if (i >= 1)
                delete mCurveNames[0];
            return false;
        }
        mCurveIndices[i] = -1;
    }
    return true;
}

// 0x7100b8cdb8
void Attenuator::destroy() {
    finalize();
    delete this;
}

// 0x7100b8cdf4
void Attenuator::finalize() {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (mgr && mgr->mDefaultAttenuator == this)
        mgr->mDefaultAttenuator = nullptr;

    for (s32 i = 0; i < 5; ++i) {
        if (mCurveNames[i]) {
            delete mCurveNames[i];
            mCurveNames[i] = nullptr;
        }
    }
    if (mDirectivityName) {
        delete mDirectivityName;
        mDirectivityName = nullptr;
    }
    if (mCullingName) {
        delete mCullingName;
        mCullingName = nullptr;
    }
}

// 0x7100b8d154
void Attenuator::setCurve(DistanceParamTarget target, Curve* curve) {
    mCurves[target] = curve;
    if (mCurveNames[target]) {
        if (curve)
            mCurveNames[target]->copy(curve->getObjName());
        else
            mCurveNames[target]->copy(sead::SafeString::cEmptyString);
    }
    mCurveIndices[target] =
        curve ? SystemAccessor::getAttenuationMgr()->mCurves.indexOf(curve) : -1;
}

// 0x7100b8d360
void Attenuator::setAttenuationDirectivity(AttenuationDirectivity* directivity) {
    mDirectivity = directivity;
    if (mDirectivityName) {
        if (directivity)
            mDirectivityName->copy(directivity->getObjName());
        else
            mDirectivityName->copy(sead::SafeString::cEmptyString);
    }
    mDirectivityIndex =
        directivity ? SystemAccessor::getAttenuationMgr()->mDirectivities.indexOf(directivity) : -1;
}

// 0x7100b8d524
void Attenuator::setAttenuationCulling(AttenuationCulling* culling) {
    mCulling = culling;
    if (mCullingName) {
        if (culling)
            mCullingName->copy(culling->getObjName());
        else
            mCullingName->copy(sead::SafeString::cEmptyString);
    }
    mCullingIndex =
        culling ? SystemAccessor::getAttenuationMgr()->mCullings.indexOf(culling) : -1;
}

// 0x7100b8d6e8
void Attenuator::setupFromResourceReader(const AttenuatorReader& reader) {
    if (!reader.isValid())
        return;

    for (s32 i = 0; i < DistanceParamTarget::size(); ++i) {
        const sead::SafeString name = reader.getCurveName(DistanceParamTarget(i));
        Curve* curve = nullptr;
        if (name.getStringTop()[0] != sead::SafeString::cNullChar)
            curve = SystemAccessor::getAttenuationMgr()->findCurve(name);
        setCurve(DistanceParamTarget(i), curve);
    }

    {
        const sead::SafeString name = reader.getDirectivityName();
        AttenuationDirectivity* directivity = nullptr;
        if (name.getStringTop()[0] != sead::SafeString::cNullChar)
            directivity = SystemAccessor::getAttenuationMgr()->findAttenuationDirectivity(name);
        setAttenuationDirectivity(directivity);
    }

    {
        const sead::SafeString name = reader.getCullingName();
        AttenuationCulling* culling = nullptr;
        if (name.getStringTop()[0] != sead::SafeString::cNullChar)
            culling = SystemAccessor::getAttenuationMgr()->findAttenuationCulling(name);
        setAttenuationCulling(culling);
    }

    mListenerDirectivityEnabled = reader.isListenerDirectivityEnabled();
    mOcclusionEnabled = reader.isOcclusionEnabled();
}

// 0x7100b8d910
void Attenuator::solveNameToInstance() {
    for (s32 i = 0; i < DistanceParamTarget::size(); ++i)
        solveCurveNameToInstance_(DistanceParamTarget(i));

    if (mDirectivityName) {
        AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
        mDirectivity = mgr->findAttenuationDirectivity(*mDirectivityName);
        if (mDirectivity) {
            mDirectivityIndex = mgr->mDirectivities.indexOf(mDirectivity);
        } else {
            mDirectivityName->clear();
            mDirectivityIndex = -1;
        }
    }

    if (mCullingName) {
        AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
        mCulling = mgr->findAttenuationCulling(*mCullingName);
        if (mCulling) {
            mCullingIndex = mgr->mCullings.indexOf(mCulling);
        } else {
            mCullingName->clear();
            mCullingIndex = -1;
        }
    }
}

// 0x7100b8da14
void Attenuator::solveCurveNameToInstance_(DistanceParamTarget target) {
    if (!mCurveNames[target])
        return;
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    Curve* curve = mgr->findCurve(*mCurveNames[target]);
    mCurves[target] = curve;
    if (curve) {
        mCurveIndices[target] = mgr->mCurves.indexOf(curve);
    } else {
        mCurveNames[target]->clear();
        mCurveIndices[target] = -1;
    }
}

// 0x7100b8dae4
const sead::SafeString& Attenuator::getCurveName(DistanceParamTarget target) const {
    if (mCurveNames[target])
        return *mCurveNames[target];
    return sead::SafeString::cEmptyString;
}

}  // namespace aal
