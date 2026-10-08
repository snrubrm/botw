#include "KingSystem/Physics/RigidBody/physRigidBodySetParamAccessor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySetParam.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::phys {

int RigidBodySetParamAccessor::m0() {
    return _10->getNumRigidBodies();
}

RigidBody* RigidBodySetParamAccessor::m1(s32 idx, sead::Heap* heap) {
    // NON_MATCHING: the original keeps the FromResource check as two call arms (b.ne);
    // ours folds them into one call with a cset-selected argument.
    RigidBodyParam* param = &_10->rigid_bodies[idx];
    if (*param->info.use_entity_shape) {
        RigidBody* linked =
            _8->sub_7100FBB918(*param->info.link_entity_set, *param->info.link_entity_body);
        if (!linked || linked->getType() != RigidBody::Type::FromShape)
            return nullptr;
        return param->createEntityShapeBody(linked, _8->_188(1), heap);
    }
    const auto layer = getContactLayerType(param->getContactLayer());
    const u32 layer_idx = u32(layer) < NumContactLayerTypes ? u32(layer) : 0;
    SystemGroupHandler* handler = _8->_188(layer_idx);
    if (_10->type_val == RigidBodySetParam::Type::FromResource)
        return param->createRigidBody(handler, heap,
                                      RigidBodyParam::CreateFixedBoxWithNoCollision::Yes);
    return param->createRigidBody(handler, heap, RigidBodyParam::CreateFixedBoxWithNoCollision::No);
}

void RigidBodySetParamAccessor::m2(s32 idx, RigidBodyInstanceParam* param) {
    // NON_MATCHING: the original loads _8 before the getContactLayerType call;
    // ours loads it after.
    if (idx < _10->getNumRigidBodies())
        _10->rigid_bodies[idx].makeInstanceParam(param);
    else
        param->motion_type = MotionType::Fixed;
    const auto layer = getContactLayerType(param->contact_layer);
    param->system_group_handler =
        _8->_188(u32(layer) < NumContactLayerTypes ? u32(layer) : 0);
}

float RigidBodySetParamAccessor::m3(s32 idx) {
    if (_10->getNumRigidBodies() <= idx)
        return 1.0f;
    return *_10->rigid_bodies[idx].info.volume;
}

}  // namespace ksys::phys
