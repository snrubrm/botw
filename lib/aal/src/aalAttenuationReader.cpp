#include "aal/aalAttenuationReader.h"

namespace aal {

// 0x7100b95e60
AttenuatorReader::AttenuatorReader(const void* data) {
    auto* header = static_cast<const Data*>(data);
    if (!header->header.isValid(0x4e544141))  // "AATN"
        return;
    if (header->header.version == 1)
        mData = header;
}

// NON_MATCHING: the original stores the SafeString vtable once and selects the string pointer (name or the empty string)
// 0x7100b95f58
sead::SafeString AttenuatorReader::getDirectivityName() const {
    const char* name = mData ? getName_(mData->directivity_name_offset) : nullptr;
    return name ? sead::SafeString(name) : sead::SafeString::cEmptyString;
}

// NON_MATCHING: same as getDirectivityName
// 0x7100b95fb8
sead::SafeString AttenuatorReader::getCullingName() const {
    const char* name = mData ? getName_(mData->culling_name_offset) : nullptr;
    return name ? sead::SafeString(name) : sead::SafeString::cEmptyString;
}

// 0x7100b96018
bool AttenuatorReader::isListenerDirectivityEnabled() const {
    return mData ? mData->listener_directivity_enabled != 0 : false;
}

// 0x7100b96038
bool AttenuatorReader::isOcclusionEnabled() const {
    return mData ? mData->occlusion_enabled != 0 : false;
}

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
