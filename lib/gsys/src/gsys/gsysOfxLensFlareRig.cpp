#include "gsys/gsysOfxLensFlareRig.h"
#include <effect/aglFxOfxLensFlare.h>

namespace agl::fx {

// 0x7100c4d5e4
void OfxBase::PresetBase::initialize(int, sead::Heap*) {}

// 0x7100c4cddc
void OfxLensFlare::drawDebugImpl_(agl::DrawContext*, int, const OfxBase::Context&) const {}

}  // namespace agl::fx

namespace gsys {

s32 OfxLensFlareImpl::Preset::getTypeID() const {
    return sTypeInfo->id;
}

s32 OfxLensFlareImpl::getTypeID() const {
    return sTypeInfo->id;
}

s32 OfxLensFlareRig::getTypeID() const {
    return sTypeInfo->id;
}

s32 OfxLargeLensFlareImpl::Preset::getTypeID() const {
    return sTypeInfo->id;
}

s32 OfxLargeLensFlareImpl::getTypeID() const {
    return sTypeInfo->id;
}

s32 OfxLargeLensFlareRig::getTypeID() const {
    return sTypeInfo->id;
}

s32 OfxLensFlareImpl::Preset::getMaxElementNum() const {
    return 5;
}

s32 OfxLensFlareImpl::getMaxElementNum() const {
    return 5;
}

s32 OfxLargeLensFlareImpl::Preset::getMaxElementNum() const {
    return 20;
}

s32 OfxLargeLensFlareImpl::getMaxElementNum() const {
    return 20;
}

}  // namespace gsys
