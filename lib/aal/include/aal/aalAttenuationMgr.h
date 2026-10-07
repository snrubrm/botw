#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "aal/aalAttenuationComponentListReflexer.h"
#include "aal/aalAttenuationCulling.h"
#include "aal/aalAttenuationDirectivity.h"
#include "aal/aalAttenuator.h"
#include "aal/aalCurve.h"
#include "aal/aalCustomCurve.h"
#include "aal/aalRollOffCurve.h"
#include "aal/aalUnitDistanceCurve.h"
#include "aal/aalHandle.h"

namespace sead {
class ArchiveFileDevice;
class Heap;
}  // namespace sead

namespace aal {

class DebugDrawer;
class Emitter;

/// An entry of the table of the attenuators sorted by the hash of their name.
struct AttenuatorHashEntry {
    bool operator<(const AttenuatorHashEntry& rhs) const { return hash < rhs.hash; }

    u32 hash;
    Attenuator* attenuator;
};

/// Owns the attenuators and their components (curves, directivities and cullings), loaded from the attenuation
/// archive, and finds them by name. TODO: incomplete (the loading and the debug preview are not modeled).
class AttenuationMgr : public sead::hostio::Node {
public:
    AttenuationMgr();
    ~AttenuationMgr();

    void initialize(sead::Heap* heap);
    void finalize();
    void calc();

    /// Creates the table of the attenuators sorted by the hash of their name (findAttenuator uses it if it exists).
    void createAttenuatorHashTable(sead::Heap* heap);

    Attenuator* findAttenuator(const sead::SafeString& name) const;
    Curve* findCurve(const sead::SafeString& name) const;
    AttenuationDirectivity* findAttenuationDirectivity(const sead::SafeString& name) const;
    AttenuationCulling* findAttenuationCulling(const sead::SafeString& name) const;
    /// The attenuator with that name, or the default attenuator.
    Attenuator* findAttenuatorOrDefault(const sead::SafeString& name) const;
    /// nullptr if the index is out of range.
    Attenuator* getAttenuator(s32 index) const;

    Attenuator* createAndAddAttenuator(const sead::SafeString& name, sead::Heap* heap);
    /// Create a component (nullptr if the name is empty or taken, or there is no memory) and add it to its list.
    RollOffCurve* createAndAddRollOffCurve(const sead::SafeString& name, sead::Heap* heap);
    CustomCurve* createAndAddCustomCurve(const sead::SafeString& name, sead::Heap* heap);
    UnitDistanceCurve* createAndAddUnitDistanceCurve(const sead::SafeString& name, sead::Heap* heap);
    AttenuationDirectivity* createAndAddAttenuationDirectivity(const sead::SafeString& name, sead::Heap* heap);
    AttenuationCulling* createAndAddAttenuationCulling(const sead::SafeString& name, sead::Heap* heap);
    /// Uses the attenuator with that name as the default attenuator (if there is one).
    void setDefaultAttenuatorName(const sead::SafeString& name);

    // The components are added to and removed from the lists by their own create functions.
    void addCurveInner_(Curve* curve);
    void removeCurveInner_(Curve* curve);
    void addAttenuationDirectivityInner_(AttenuationDirectivity* directivity);
    void removeAttenuationDirectivityInner_(AttenuationDirectivity* directivity);
    void addAttenuationCullingInner_(AttenuationCulling* culling);
    void removeAttenuationCullingInner_(AttenuationCulling* culling);

    Attenuator* getDefaultAttenuator() const { return mDefaultAttenuator; }

private:
    void removeAndDeleteAllComponents_();
    /// `directory`/`name` followed by `extension`.
    void makeResourcdFullPath_(sead::BufferedSafeString* out, const sead::SafeString& directory,
                               const sead::SafeString& name, const sead::SafeString& extension) const;

    friend class Attenuator;
    friend class AttenuatorListReflexer;
    friend class AttenuationCurveListReflexer;
    friend class AttenuationDirectivityListReflexer;
    friend class AttenuationCullingListReflexer;

    bool mInitialized = false;
    sead::OffsetList<Attenuator> mAttenuators;
    AttenuatorListReflexer* mAttenuatorReflexer = nullptr;
    sead::OffsetList<Curve> mCurves;
    AttenuationCurveListReflexer* mCurveReflexer = nullptr;
    sead::OffsetList<AttenuationDirectivity> mDirectivities;
    AttenuationDirectivityListReflexer* mDirectivityReflexer = nullptr;
    sead::OffsetList<AttenuationCulling> mCullings;
    AttenuationCullingListReflexer* mCullingReflexer = nullptr;
    Attenuator* mDefaultAttenuator = nullptr;
    sead::FixedSafeString<32>* mDefaultAttenuatorName = nullptr;
    sead::Buffer<AttenuatorHashEntry> mAttenuatorHashTable;
    // The preview of the attenuation (a sound that is played to listen to an attenuator). TODO: not modeled.
    void* _b0 = nullptr;
    void* _b8 = nullptr;
    s32 _c0 = -1;
    bool _c4 = false;
    void* _c8 = nullptr;
    void* _d0 = nullptr;
    s32 _d8 = -1;
    u16 _dc = 0xffff;
    void* _e0 = nullptr;
    Emitter* mPreviewEmitter = nullptr;
    Handle mPreviewHandle;
    sead::Vector3f _100 = sead::Vector3f::zero;
    u64 _110 = 0;
    f32 mPreviewVolume = 1.0f;
    bool mPreviewPlaying = false;
    bool _11d = false;
    bool _11e = false;
    bool _11f = false;
    f32 _120 = 0.1f;
    bool _124 = true;
    Curve::DrawGraphArg mDrawGraphArg;
    bool _17c = false;
};
static_assert(sizeof(AttenuationMgr) == 0x180, "aal::AttenuationMgr size mismatch");

}  // namespace aal
