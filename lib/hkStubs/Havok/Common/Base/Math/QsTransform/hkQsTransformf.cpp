#include <Havok/Common/Base/hkBase.h>

void hkQsTransformf::copyToTransformNoScale(hkTransformf& transformOut) const {
    transformOut.set(m_rotation, m_translation);
}

void hkQsTransformf::setFromTransformNoScale(const hkTransformf& transform) {
    m_rotation.set(transform.getRotation());
    m_translation = transform.getTranslation();
    m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}
