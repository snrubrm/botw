#include "aal/aalAttenuationReader.h"

namespace aal {

// 0x7100b95c78
AttenuationCullingReader::AttenuationCullingReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x4c434141))  // "AACL"
        return;
    if (header->header.version == 2) {
        mData = header;
    } else if (header->header.version == 1) {
        mIsVersion1 = true;
        mData = header;
    }
}

// 0x7100b95d1c
f32 AttenuationCullingReader::getCullingDistance() const {
    return mData ? mData->culling_distance : 0.0f;
}

// 0x7100b95d34
f32 AttenuationCullingReader::getCullingMergin() const {
    return mData ? mData->culling_mergin : 0.0f;
}

// 0x7100b95d4c
bool AttenuationCullingReader::isPriorityDownEnabled() const {
    if (mIsVersion1)
        return false;
    return mData->priority_down_enabled != 0;
}

// 0x7100b95d70
AttenuationDirectivityReader::AttenuationDirectivityReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x52444141))  // "AADR"
        return;
    if (header->header.version == 1)
        mData = header;
}

// 0x7100b95e00
f32 AttenuationDirectivityReader::getInnerConeAngle() const {
    return mData ? mData->inner_cone_angle : 0.0f;
}

// 0x7100b95e18
f32 AttenuationDirectivityReader::getOuterConeAngle() const {
    return mData ? mData->outer_cone_angle : 0.0f;
}

// 0x7100b95e30
f32 AttenuationDirectivityReader::getOuterReduction() const {
    return mData ? mData->outer_reduction : 0.0f;
}

// 0x7100b95e48
f32 AttenuationDirectivityReader::getOuterFilter() const {
    return mData ? mData->outer_filter : 0.0f;
}

}  // namespace aal
