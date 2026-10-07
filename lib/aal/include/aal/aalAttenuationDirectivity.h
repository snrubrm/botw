#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "aal/aalNamedObj.h"

namespace aal {

class AttenuationDirectivityReader;

/// The reduction of the volume (and of the high frequencies) of a sound by the angle between its direction and the
/// listener: no reduction inside the inner cone, the full reduction outside of the outer cone.
class AttenuationDirectivity : public FixedNamedObj<32>, public sead::hostio::Node {
public:
    explicit AttenuationDirectivity(const sead::SafeString& name);
    ~AttenuationDirectivity() override;

    /// The volume factor for `rate` (0: inside of the inner cone, 1: outside of the outer cone).
    f32 calcConeReduction(f32 rate) const;
    /// The filter factor for `rate`.
    f32 calcConeFilter(f32 rate) const;
    void setupFromResourceReader(const AttenuationDirectivityReader& reader);

    f32 getInnerConeAngleRad() const;
    f32 getOuterConeAngleRad() const;

    f32 mInnerConeAngle = 45.0f;
    f32 mOuterConeAngle = 90.0f;
    f32 mOuterReduction = 0.5f;
    f32 mOuterFilter = 0.5f;
    /// The node in the list of the directivities of the AttenuationMgr.
    sead::ListNode mListNode;
};
static_assert(sizeof(AttenuationDirectivity) == 0x78, "aal::AttenuationDirectivity size mismatch");

}  // namespace aal
