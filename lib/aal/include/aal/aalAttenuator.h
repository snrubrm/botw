#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "aal/aalCurve.h"
#include "aal/aalDistanceParamTarget.h"
#include "aal/aalNamedObj.h"

namespace sead {
class Heap;
}

namespace aal {

class AttenuationCulling;
class AttenuationDirectivity;
class AttenuatorReader;

/// How the sounds that use it (SpatialSetting::setAttenuator) are attenuated: a distance curve for each parameter, the
/// directivity and the culling. The curves, the directivity and the culling are found by their names in the
/// AttenuationMgr (solveNameToInstance).
class Attenuator : public FixedNamedObj<32>, public sead::hostio::Node {
public:
    /// Allocates the attenuator on `heap`; nullptr if the allocation or the initialization fails.
    static Attenuator* create(const sead::SafeString& name, sead::Heap* heap);

    explicit Attenuator(const sead::SafeString& name);
    ~Attenuator() override;

    bool initialize(sead::Heap* heap);
    /// finalize() and delete.
    void destroy();
    void finalize();

    void setCurve(DistanceParamTarget target, Curve* curve);
    void setAttenuationDirectivity(AttenuationDirectivity* directivity);
    void setAttenuationCulling(AttenuationCulling* culling);
    void setupFromResourceReader(const AttenuatorReader& reader);
    /// Looks the curves, the directivity and the culling up by their names.
    void solveNameToInstance();
    /// The name of the curve (the empty string if there is none).
    const sead::SafeString& getCurveName(DistanceParamTarget target) const;

    Curve* getCurve(DistanceParamTarget target) const { return mCurves[target]; }
    AttenuationDirectivity* getAttenuationDirectivity() const { return mDirectivity; }
    AttenuationCulling* getAttenuationCulling() const { return mCulling; }
    bool isListenerDirectivityEnabled() const { return mListenerDirectivityEnabled; }

    /// The node in the list of the attenuators of the AttenuationMgr.
    sead::ListNode mListNode;

private:
    void solveCurveNameToInstance_(DistanceParamTarget target);

    sead::SafeArray<Curve*, 5> mCurves;
    AttenuationDirectivity* mDirectivity = nullptr;
    AttenuationCulling* mCulling = nullptr;
    bool mListenerDirectivityEnabled = false;
    bool mOcclusionEnabled = false;
    /// The names of the curves, directivity and culling that are not loaded yet (allocated by initialize).
    sead::SafeArray<sead::FixedSafeString<32>*, 5> mCurveNames;
    sead::FixedSafeString<32>* mDirectivityName = nullptr;
    sead::FixedSafeString<32>* mCullingName = nullptr;
    /// The index of the curves, directivity and culling in the lists of the AttenuationMgr.
    sead::SafeArray<s32, 5> mCurveIndices;
    s32 mDirectivityIndex = -1;
    s32 mCullingIndex = -1;
    bool _fc = false;
    bool _fd = false;
    Curve::DrawGraphArg mDrawGraphArg;
};
static_assert(sizeof(Attenuator) == 0x158, "aal::Attenuator size mismatch");

}  // namespace aal
