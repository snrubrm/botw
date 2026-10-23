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

}  // namespace gsys
