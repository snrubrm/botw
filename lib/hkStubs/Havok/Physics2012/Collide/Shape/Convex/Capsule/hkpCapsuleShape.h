#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

class hkpCapsuleShape : public hkpConvexShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCapsuleShape)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CAPSULE)

    enum RayHitType {
        HIT_CAP0,
        HIT_CAP1,
        HIT_BODY,
    };

    hkpCapsuleShape() = default;
    hkpCapsuleShape(const hkVector4& vertexA, const hkVector4& vertexB, hkReal radius);
    explicit hkpCapsuleShape(hkFinishLoadedObjectFlag flag);
    ~hkpCapsuleShape() override;

    HK_FORCE_INLINE void getSupportingVertex(hkVector4Parameter direction,
                                             hkcdVertex& supportingVertexOut) const override;

    HK_FORCE_INLINE void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds,
                                                    hkcdVertex* verticesOut) const override;

    HK_FORCE_INLINE void getCentre(hkVector4& centreOut) const override;
    HK_FORCE_INLINE int getNumCollisionSpheres() const override;
    const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const override;
    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;
    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    inline const hkVector4* getVertices() const;

    HK_FORCE_INLINE const hkVector4& getVertex(int i) const;
    template <int I>
    HK_FORCE_INLINE const hkVector4& getVertex() const;

    HK_FORCE_INLINE void setVertex(int i, const hkVector4& position);
    template <int I>
    HK_FORCE_INLINE void setVertex(hkVector4Parameter position);

    void getFirstVertex(hkVector4& v) const override;

    static void closestPointLineSeg(const hkVector4& A, const hkVector4& B, const hkVector4& B2,
                                    hkVector4& pt);
    static void closestInfLineSegInfLineSeg(const hkVector4& A, const hkVector4& dA,
                                            const hkVector4& B, const hkVector4& dB,
                                            hkReal& distSquared, hkReal& t, hkReal& u, hkVector4& p,
                                            hkVector4& q);

protected:
    // The line's first point.
    hkVector4 m_vertexA;
    // The line's second point.
    hkVector4 m_vertexB;
};

inline const hkVector4* hkpCapsuleShape::getVertices() const {
    return &m_vertexA;
}

inline const hkVector4& hkpCapsuleShape::getVertex(int i) const {
    return getVertices()[i];
}

template <int I>
inline const hkVector4& hkpCapsuleShape::getVertex() const {
    return getVertices()[I];
}

// Inlined by Unk_71024f5e90::m6 0x7100f67444: each vertex is stored whole, then its w lane is set
// to the shape radius (+0x18).
inline void hkpCapsuleShape::setVertex(int i, const hkVector4& position) {
    hkVector4* vertices = &m_vertexA;
    vertices[i] = position;
    vertices[i](3) = m_radius;
}

template <int I>
inline void hkpCapsuleShape::setVertex(hkVector4Parameter position) {
    setVertex(I, position);
}
