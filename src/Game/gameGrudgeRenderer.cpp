#include "Game/gameGraphics.h"
#include <gsys/gsysModel.h>
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

// GrudgeRenderer's TU (0x710128d348 .. 0x71012915b8). Only this helper is decompiled so far.

bool sub_7101290034(const sead::Vector3f& start, const sead::Vector3f& displacement, sead::Vector3f* hit_pos) {
    ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.setGroundHit(ksys::phys::GroundHit::Grudge);
    query.setStartAndDisplacement(start, displacement);
    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitPosition(hit_pos);
        hit = true;
    }
    return hit;
}

// 0x710128f4bc
void GrudgeRenderer::sub_710128F4BC(const sead::Camera* camera) {
    if ((_2ef8 & 1) == 0)
        return;
    camera->getWorldPosByMatrix(&_240);
    _264 = cGrudgeResetDistance;
    _268->requestDraw();
}

// 0x710128f888: the final-image pass calls this debug draw of the renderer; the original body is empty.
void GrudgeRenderer::sub_710128F888(agl::DrawContext* context,
                                    gsys::ModelRenderContext* render_context) {}

// NON_MATCHING: the original keeps the unit count in a register across the loop; ours rematerialises
// the load for the latch (register pressure from the loop-invariant compare string). One extra
// load and a `b.lt` instead of `b.ne`.
// 0x710128fd48: destroys the unit's uniform block and, when it owns one, its GPU buffer.
Unk_71025191c8::~Unk_71025191c8() {
    mUniformBlock.destroy();
    if (_121 & 1)
        sub_710128FD94();
}

// 0x7101290010: scales the unit's stored sizes by the reciprocal of `n`.
void Unk_71025191c8::sub_7101290010(s32 n) {
    const f32 scale = 1.0f / f32(n);
    _100 = scale;
    _104 = scale * f32(_11c);
}

// 0x710128f9e0: marks the renderer when the model has the GrudgeSlimeMold unit.
void GrudgeRenderer::sub_710128F9E0(gsys::Model* model) {
    if (!model)
        return;
    const auto& units = model->getUnits();
    for (s32 i = 0; i < units.size(); ++i) {
        gsys::ModelInfo* info = units[i];
        gsys::ModelUnit* unit = info->mModelUnit;
        if (!sead::IsDerivedFrom<gsys::ModelUnit>(unit))
            continue;
        const sead::SafeString name = unit->getName();
        if (name == "GrudgeSlimeMold")
            _2ef8 |= 4;
    }
}
