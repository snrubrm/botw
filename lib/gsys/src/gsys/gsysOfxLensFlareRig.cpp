#include "gsys/gsysOfxLensFlareRig.h"

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
