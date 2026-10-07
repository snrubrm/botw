#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "aal/aalNamedObj.h"

namespace aal {

class AttenuationCullingReader;
class Curve;

/// The distance up to which a sound is audible: the sound is culled (not played) beyond `culling_distance`, and
/// faded out over `culling_mergin` before that.
class AttenuationCulling : public FixedNamedObj<32>, public sead::hostio::Node {
public:
    explicit AttenuationCulling(const sead::SafeString& name);
    ~AttenuationCulling() override = default;

    /// The gain (0 - 1) at `distance` for the culling distance and mergin. The result is squared.
    static f32 calcCullingGain(f32 distance, f32 culling_distance, f32 culling_mergin);
    /// Same, with the distance and mergin of this culling. `curve` (can be null) moves the start of the fade out.
    f32 calcCullingGain(f32 distance, Curve* curve) const;
    /// 0 if the curve culls at `distance`, 1 otherwise.
    static f32 calcCullingGainByCurve(f32 distance, Curve* curve);
    void setupFromResourceReader(const AttenuationCullingReader& reader);

    bool isPriorityDownEnabled() const { return mPriorityDown; }

    f32 mCullingDistance = 0.0f;
    f32 mCullingMergin = 0.0f;
    bool mPriorityDown = false;
    /// The node in the list of the cullings of the AttenuationMgr.
    sead::ListNode mListNode;
    f32 mCullingStartDistance = 0.0f;
};
static_assert(sizeof(AttenuationCulling) == 0x80, "aal::AttenuationCulling size mismatch");

}  // namespace aal
