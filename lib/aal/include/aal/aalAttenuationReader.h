#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "aal/aalResourceHeader.h"

namespace aal {

/// Reads the binary resource of an Attenuator (signature "AATN", version 1): the names of the curves, the
/// directivity and the culling that it is made of.
/// TODO: getCurveName(DistanceParamTarget) is not modeled (the enum is not).
class AttenuatorReader {
public:
    explicit AttenuatorReader(const void* data);

    /// The names are empty if the resource is not valid.
    sead::SafeString getDirectivityName() const;
    sead::SafeString getCullingName() const;
    bool isListenerDirectivityEnabled() const;
    bool isOcclusionEnabled() const;

private:
    struct CurveEntry {
        u32 name_offset;
        u32 _4;
    };

    struct Data {
        ResourceHeader header;
        /// The offsets of the names are relative to this offset.
        u32 name_base_offset;
        CurveEntry curves[5];
        u32 directivity_name_offset;
        u32 culling_name_offset;
        u32 listener_directivity_enabled;
        u32 occlusion_enabled;
    };

    const char* getName_(u32 name_offset) const {
        return reinterpret_cast<const char*>(mData) + (mData->name_base_offset + name_offset);
    }

    const Data* mData = nullptr;
};

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
