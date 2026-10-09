#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkaiUserEdgeUtils {
public:
    // Reflection176daf4 names UserEdgePair, fixes extent0x50 and each
    // member offset. Batch153d7ec and the independent game removalf83848
    // both traverse 0x50 records and consume UID/face offsets30/34/38/3c.
    struct UserEdgePair {
        hkVector4 m_x;
        hkVector4 m_y;
        hkVector4 m_z;
        hkUint32 m_instanceUidA;
        hkUint32 m_instanceUidB;
        hkInt32 m_faceA;
        hkInt32 m_faceB;
        hkUint32 m_userDataA;
        hkUint32 m_userDataB;
        hkHalf m_costAtoB;
        hkHalf m_costBtoA;
        // Reflected enum storage is one byte; enumerator identities remain
        // unproved, so this preserves storage without inventing an enum.
        hkUint8 m_direction;
    };
};
static_assert(sizeof(hkaiUserEdgeUtils::UserEdgePair) == 0x50);
