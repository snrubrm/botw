#include <Havok/Animation/Animation/Playback/Utilities/hkaSampleAndCombineUtils.h>

// NON_MATCHING: the compiler peels an odd first element instead of using a final remainder.
void hkaSampleAndCombineUtils::scaleTranslations(hkReal scale, hkQsTransform* poseInOut,
                                                int numTransforms) {
    const hkSimdReal factor(scale);
    for (int i = 0; i < numTransforms; ++i)
        poseInOut[i].m_translation.mul(factor);
}
