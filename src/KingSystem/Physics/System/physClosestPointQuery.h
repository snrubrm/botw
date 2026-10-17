#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace ksys::phys {

class LayerMaskBuilder;
class RigidBody;
class QueryContactPointInfo;

class ClosestPointQuery {
    SEAD_RTTI_BASE(ClosestPointQuery)
public:
    ClosestPointQuery(RigidBody* body, QueryContactPointInfo* contact_point_info);
    virtual ~ClosestPointQuery();

    RigidBody* getBody() const { return mBody; }
    QueryContactPointInfo* getContactPointInfo() const { return mContactPointInfo; }

    void setLayerMasks(const LayerMaskBuilder& builder);
    void setLayerMasksAndBodyCollisionFilterInfo(const LayerMaskBuilder& builder);

    // 0x0000007100fb0850: forwards to the still undecompiled implementation 0x7100fb0858.
    bool execute(bool unk);
    bool isSuccess() const;

protected:
    void reset();

    RigidBody* mBody{};
    QueryContactPointInfo* mContactPointInfo{};
    u32 _18{};
    bool mIsSuccess = false;
    sead::Matrix34f mMtx = sead::Matrix34f::ident;
};

// 0x7100fb0858 (1160 B, still undecompiled): the ray-cast implementation behind
// ClosestPointQuery::execute (declared only).
bool sub_7100FB0858(ClosestPointQuery* self, bool unk);

}  // namespace ksys::phys
