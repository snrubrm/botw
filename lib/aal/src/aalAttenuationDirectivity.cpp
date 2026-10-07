#include "aal/aalAttenuationDirectivity.h"
#include "aal/aalAttenuationReader.h"

namespace aal {

AttenuationDirectivity::~AttenuationDirectivity() = default;

namespace {
constexpr f32 cMaxConeAngle = 180.0f;
constexpr f32 cDegToRad = 0.017453292f;
}  // namespace

// 0x7100bb7f9c
AttenuationDirectivity::AttenuationDirectivity(const sead::SafeString& name) {
    setObjName(name);
}

// 0x7100bb8130
f32 AttenuationDirectivity::calcConeReduction(f32 rate) const {
    if (rate <= 0.0f)
        return 1.0f;
    if (rate >= 1.0f)
        return mOuterReduction;
    return 1.0f - (1.0f - mOuterReduction) * rate;
}

// 0x7100bb8164
f32 AttenuationDirectivity::calcConeFilter(f32 rate) const {
    if (rate <= 0.0f)
        return 0.0f;
    if (rate >= 1.0f)
        return mOuterFilter;
    return mOuterFilter * rate;
}

// 0x7100bb8190
void AttenuationDirectivity::setupFromResourceReader(const AttenuationDirectivityReader& reader) {
    if (!reader.isValid())
        return;

    const f32 inner_cone_angle = reader.getInnerConeAngle();
    if (inner_cone_angle >= 0.0f && inner_cone_angle <= cMaxConeAngle)
        mInnerConeAngle = inner_cone_angle;

    const f32 outer_cone_angle = reader.getOuterConeAngle();
    if (outer_cone_angle >= 0.0f && outer_cone_angle <= cMaxConeAngle)
        mOuterConeAngle = outer_cone_angle;

    const f32 outer_reduction = reader.getOuterReduction();
    if (outer_reduction >= 0.0f && outer_reduction <= 1.0f)
        mOuterReduction = outer_reduction;

    const f32 outer_filter = reader.getOuterFilter();
    if (outer_filter >= 0.0f && outer_filter <= 1.0f)
        mOuterFilter = outer_filter;
}

// 0x7100bb8240
f32 AttenuationDirectivity::getInnerConeAngleRad() const {
    return mInnerConeAngle * cDegToRad;
}

// 0x7100bb8254
f32 AttenuationDirectivity::getOuterConeAngleRad() const {
    return mOuterConeAngle * cDegToRad;
}

}  // namespace aal
