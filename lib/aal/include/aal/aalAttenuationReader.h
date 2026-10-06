#pragma once

#include <basis/seadTypes.h>
#include "aal/aalResourceHeader.h"

namespace aal {

/// Reads the binary resource of an AttenuationCulling (signature "AACL", versions 1 and 2).
class AttenuationCullingReader {
public:
    explicit AttenuationCullingReader(const void* data);

    f32 getCullingDistance() const;
    f32 getCullingMergin() const;
    /// Not stored by version 1 resources (false).
    bool isPriorityDownEnabled() const;

private:
    struct Data {
        ResourceHeader header;
        f32 culling_distance;
        f32 culling_mergin;
        u8 priority_down_enabled;
    };

    const Data* mData = nullptr;
    bool mIsVersion1 = false;
};

/// Reads the binary resource of an AttenuationDirectivity (signature "AADR", version 1).
class AttenuationDirectivityReader {
public:
    explicit AttenuationDirectivityReader(const void* data);

    f32 getInnerConeAngle() const;
    f32 getOuterConeAngle() const;
    f32 getOuterReduction() const;
    f32 getOuterFilter() const;

private:
    struct Data {
        ResourceHeader header;
        f32 inner_cone_angle;
        f32 outer_cone_angle;
        f32 outer_reduction;
        f32 outer_filter;
    };

    const Data* mData = nullptr;
};

}  // namespace aal
