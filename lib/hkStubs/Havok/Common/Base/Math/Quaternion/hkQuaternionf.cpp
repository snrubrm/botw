#include <Havok/Common/Base/hkBase.h>

#include <cmath>

// NON_MATCHING: the final indexed store is merged across branches; register scheduling differs.
void hkQuaternionf::set(const hkRotationf& rotation) {
    const hkReal trace = rotation(0, 0) + rotation(1, 1) + rotation(2, 2);
    hkVector4f result;
    if (trace > 0.0f) {
        const hkReal root = std::sqrt(trace + 1.0f);
        const hkReal factor = 0.5f / root;
        result(0) = factor * (rotation(2, 1) - rotation(1, 2));
        result(1) = factor * (rotation(0, 2) - rotation(2, 0));
        result(2) = factor * (rotation(1, 0) - rotation(0, 1));
        result(3) = root * 0.5f;
    } else {
        const int next[3] = {1, 2, 0};
        int i = rotation(1, 1) > rotation(0, 0) ? 1 : 0;
        if (rotation(2, 2) > rotation(i, i))
            i = 2;
        const int j = next[i];
        const int k = next[j];
        const hkReal root = std::sqrt(rotation(i, i) - (rotation(j, j) + rotation(k, k)) + 1.0f);
        const hkReal factor = 0.5f / root;
        result(i) = root * 0.5f;
        result(3) = factor * (rotation(k, j) - rotation(j, k));
        result(j) = factor * (rotation(j, i) + rotation(i, j));
        result(k) = factor * (rotation(k, i) + rotation(i, k));
    }
    m_vec = result;
}
