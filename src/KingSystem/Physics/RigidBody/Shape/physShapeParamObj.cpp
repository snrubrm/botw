#include "KingSystem/Physics/RigidBody/Shape/physShapeParamObj.h"
#include <utility/aglDevTools.h>
#include "KingSystem/Physics/RigidBody/Shape/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Graphics/gfxLocationalLightMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::phys {

ShapeParamObj::ShapeParamObj()
    : shape_type(sead::SafeString::cEmptyString, "shape_type", this), radius(1.0, "radius", this),
      convex_radius(0.05, "convex_radius", this),
      translate_0(sead::Vector3f::zero, "translate_0", this),
      translate_1(sead::Vector3f::zero, "translate_1", this),
      rotate(sead::Vector3f::zero, "rotate", this), vertex_num(0, "vertex_num", this),
      material(sead::SafeString::cEmptyString, "material", this),
      sub_material(sead::SafeString::cEmptyString, "sub_material", this),
      wall_code({"None"}, "wall_code", this), floor_code({"None"}, "floor_code", this),
      item_code_disable_stick(false, "item_code_disable_stick", this) {}

ShapeParamObj::~ShapeParamObj() {
    vertices.freeBuffer();
}

bool ShapeParamObj::parse(const agl::utl::ResParameterObj& res_obj, sead::Heap* heap) {
    vertices.freeBuffer();

    applyResParameterObj(res_obj);

    const int num_vertices = vertex_num.ref();
    if (num_vertices > 0) {
        vertices.allocBufferAssert(num_vertices, heap);
        for (int i = 0; i < num_vertices; ++i) {
            sead::FormatFixedSafeString<32> name("vertex_%d", i);
            vertices[i].init(sead::Vector3f::zero, name, "頂点", this);
        }

        applyResParameterObj(res_obj);
    }

    return true;
}

ShapeType ShapeParamObj::getShapeType() const {
    if (*shape_type == "sphere")
        return ShapeType::Sphere;
    if (*shape_type == "capsule")
        return ShapeType::Capsule;
    if (*shape_type == "cylinder")
        return ShapeType::Cylinder;
    if (*shape_type == "box")
        return ShapeType::Box;
    if (*shape_type == "polytope")
        return ShapeType::Polytope;
    if (*shape_type == "character_prism")
        return ShapeType::CharacterPrism;

    return ShapeType::Unknown;
}

void ShapeParamObj::getCommon(CommonShapeParam* param) const {
    param->material = materialFromText(*material);
    param->sub_material = sub_material->cstr();
    param->floor_code = floorCodeFromText(*floor_code);
    param->wall_code = wallCodeFromText(*wall_code);
    param->item_code_disable_stick = *item_code_disable_stick;
}

void ShapeParamObj::getSphere(SphereShapeParam* param) const {
    param->radius = *radius;
    param->translate = *translate_0;
    getCommon(&param->common);
}

void ShapeParamObj::getCapsule(CapsuleShapeParam* param) const {
    param->radius = *radius;
    param->vertex_a = *translate_0;
    param->vertex_b = *translate_1;
    getCommon(&param->common);
}

void ShapeParamObj::getCylinder(CylinderShapeParam* param) const {
    param->radius = *radius;
    param->convex_radius = *convex_radius;
    param->vertex_a = *translate_0;
    param->vertex_b = *translate_1;
    getCommon(&param->common);
}

void ShapeParamObj::getBox(BoxShapeParam* param) const {
    param->translate = *translate_0;
    param->extents = *translate_1;
    param->rotate = *rotate;
    param->convex_radius = *convex_radius;
    getCommon(&param->common);
}

void ShapeParamObj::getPolytope(PolytopeShapeParam* param) const {
    param->vertex_num = *vertex_num;
    getCommon(&param->common);
}

void ShapeParamObj::getCharacterPrism(CharacterPrismShapeParam* param) const {
    param->radius = *radius;
    param->ring0_distance = translate_0->x;
    param->ring1_distance = translate_0->y;
    param->end_vertex_distance = translate_0->z;
    param->offset = *translate_1;
    getCommon(&param->common);
}

}  // namespace ksys::phys

Unk_7102519378::~Unk_7102519378() = default;

// The render-light record's debug draw; the Light slot forwards the draw arguments here.
void Unk_7102519378::drawDebug(agl::DrawContext*, const sead::Matrix34f&, const sead::Matrix44f&,
                               int) const {}

// 0x7101295f80: clears the record's dirty words and runs the subclass hook (slot 9) under the
// record's lock; RenderLightPool's allocator calls it on every record it hands out.
void Unk_7102519378::init() {
    mCS.lock();
    _48 = 0;
    _58 = 0;
    _5a = 0;
    m9();
    mCS.unlock();
}

// 0x7101295fc4: runs the subclass hook (slot 10) and clears _48 under the record's lock;
// LocationalLightMgr::sub_7100F13A58 calls it when it detaches a record.
void Unk_7102519378::reset() {
    mCS.lock();
    m10();
    _48 = 0;
    mCS.unlock();
}

// Slots 6..10 are empty in the base vtable (0x710129dae0 .. 0x710129daf0).
void Unk_7102519378::m6(sead::Heap*) {}
void Unk_7102519378::m7() {}
void Unk_7102519378::m8(u8) {}
void Unk_7102519378::m9() {}
void Unk_7102519378::m10() {}

// 0x7101296100 / 0x7101296178: returns the record to the render-light pool, frees the particle
// buffer and then destroys the uniform block and the base lock.
Unk_71025193e8::~Unk_71025193e8() {
    _128 = 0;
    if (mPoolLink) {
        static_cast<ksys::gfx::LocationalLightMgr*>(_50)->releaseRenderLight(mPoolLink);
        mPoolLink = nullptr;
    }
    if (mBuffer) {
        delete[] mBuffer;
        mBuffer = nullptr;
        mBufferCount = 0;
    }
}

Unk_71025193e8::Unk_71025193e8() = default;

// Discarded call: m11's result is unused (the original tail-calls slot 11), as in m12.
void Unk_71025193e8::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                               const sead::Matrix44f& projection, int view_index) const {
    if (_50 && (_48 & 1))
        m11();
}

void Unk_71025193e8::m9() {
    _5c = 0;
}

void Unk_71025193e8::m10() {
    if (mPoolLink) {
        static_cast<ksys::gfx::LocationalLightMgr*>(_50)->releaseRenderLight(mPoolLink);
        mPoolLink = nullptr;
    }
    _128 = 0;
    _5c = 0;
}

bool Unk_71025193e8::m11() const {
    return (_5c & 2) != 0;
}

void Unk_71025193e8::m12() {
    if (_50 && (_48 & 1))
        m11();
}

Unk_7102519460::Unk_7102519460() = default;
Unk_7102519460::~Unk_7102519460() = default;

f32 Unk_7102519460::setColor(const sead::Color4f& color) {
    const f32 luminance = color.r * 0.298912f + color.g * 0.586611f + color.b * 0.114478f;
    mColor = color / luminance;
    mColor.a = color.a;
    return luminance;
}

void Unk_7102519460::setColorAndLuminance(const sead::Color4f& color) {
    _100 = sead::Mathf::clampMin(setColor(color), 0.0f);
}

// NON_MATCHING: the original masks the view bit test with 0xffff before the branch.
void Unk_7102519460::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                               const sead::Matrix44f& projection, int view_index) const {
    if (!_50 || !(_48 & 1) || !m11())
        return;
    if (!(_5a & (1 << view_index)))
        return;

    const f32 radius = std::max(mRadius, 0.0f);
    if (radius <= 0.0f) {
        agl::utl::DevTools::beginDrawImm(context, view, projection);
        agl::utl::DevTools::drawLineImm(context, mStart, mEnd, mColor, 1.0f);
    } else {
        agl::utl::DevTools::drawCapsule(context, mStart, mEnd, radius, mColor, view, projection,
                                        false);
    }
    agl::utl::DevTools::drawCapsule(context, mStart, mEnd, _110, mColor, view, projection, false);
}

void Unk_7102519460::m9() {
    _5c = 0;
}

void Unk_7102519460::m10() {
    _5c = 0;
}

bool Unk_7102519460::m11() const {
    return (_5c & 2) != 0;
}

Unk_71025194d0::~Unk_71025194d0() = default;

void Unk_71025194d0::m9() {
    _5c = 0;
}

void Unk_71025194d0::m10() {
    _5c = 0;
}

bool Unk_71025194d0::m11() const {
    return (_5c & 1) != 0;
}

Unk_7102519540::~Unk_7102519540() = default;

f32 Unk_7102519540::setColor(const sead::Color4f& color) {
    const f32 luminance = color.r * 0.298912f + color.g * 0.586611f + color.b * 0.114478f;
    mColor = color / luminance;
    mColor.a = color.a;
    return luminance;
}

void Unk_7102519540::setColorAndLuminance(const sead::Color4f& color) {
    _100 = sead::Mathf::clampMin(setColor(color), 0.0f);
}

// NON_MATCHING: the original masks the view bit test with 0xffff before the branch.
void Unk_7102519540::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                               const sead::Matrix44f& projection, int view_index) const {
    if (!_50 || !(_48 & 1) || !m11())
        return;
    if (!(_5a & (1 << view_index)))
        return;

    const f32 radius = std::max(mRadius, 0.0f);
    if (radius <= 0.0f) {
        agl::utl::DevTools::beginDrawImm(context, view, projection);
        agl::utl::DevTools::drawLineImm(context, mStart, mEnd, mColor, 1.0f);
    } else {
        agl::utl::DevTools::drawCapsule(context, mStart, mEnd, radius, mColor, view, projection,
                                        false);
    }
    agl::utl::DevTools::drawCapsule(context, mStart, mEnd, _110, mColor, view, projection, false);
}

void Unk_7102519540::m9() {
    _5c = 0;
}

void Unk_7102519540::m10() {
    _5c = 0;
}

bool Unk_7102519540::m11() const {
    return (_5c & 2) != 0;
}

Unk_71025195b0::~Unk_71025195b0() = default;

void Unk_71025195b0::m9() {
    _5c = 0;
}

void Unk_71025195b0::m10() {
    _5c = 0;
}

bool Unk_71025195b0::m11() const {
    return (_5c & 2) != 0;
}

Unk_7102519620::Unk_7102519620() = default;
Unk_7102519620::~Unk_7102519620() = default;

// NON_MATCHING: the original masks the view bit test with 0xffff before the branch.
void Unk_7102519620::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                               const sead::Matrix44f& projection, int view_index) const {
    if (!_50 || !(_48 & 1) || !m11())
        return;
    if (!(_5a & (1 << view_index)))
        return;

    sead::Vector3f dir = mDir;
    if (dir.equals(sead::Vector3f::ey, 0.01f))
        dir.set(0.01f, 0.99f, -0.01f);
    dir.normalize();
    agl::utl::DevTools::drawSpotLight(context, mPos, dir, mColor, _f0, _f4, view, projection);
}

void Unk_7102519620::m9() {
    _5c = 0;
}

void Unk_7102519620::m10() {
    _5c = 0;
}

bool Unk_7102519620::m11() const {
    return (_5c & 1) != 0;
}

Unk_7102519690::~Unk_7102519690() {
    _128 = 0;
    if (mPoolLink) {
        static_cast<ksys::gfx::LocationalLightMgr*>(_50)->releaseRenderLight(mPoolLink);
        mPoolLink = nullptr;
    }
    if (mBuffer) {
        delete[] mBuffer;
        mBuffer = nullptr;
        mBufferCount = 0;
    }
}

// Discarded call: m11's result is unused (the original tail-calls slot 11), as in Unk_71025193e8::m12.
void Unk_7102519690::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                               const sead::Matrix44f& projection, int view_index) const {
    if (_50 && (_48 & 1))
        m11();
}

void Unk_7102519690::m9() {
    _5c = 0;
}

void Unk_7102519690::m10() {
    if (mPoolLink) {
        static_cast<ksys::gfx::LocationalLightMgr*>(_50)->releaseRenderLight(mPoolLink);
        mPoolLink = nullptr;
    }
    _128 = 0;
    _5c = 0;
}

bool Unk_7102519690::m11() const {
    return _128 > 0.0f;
}

void Unk_7102519690::m12() {
    if (_50 && (_48 & 1))
        m11();
}

Unk_7102519708::~Unk_7102519708() = default;

// NON_MATCHING: the original keeps the green store in both branches; ours merges it.
f32 Unk_7102519708::setColor(const sead::Color4f& color) {
    const f32 luminance = sead::Mathf::clampMin(
        color.r * 0.298912f + color.g * 0.586611f + color.b * 0.114478f, 0.0f);
    if (luminance > 0.0f) {
        mColor = color / luminance;
    } else {
        mColor.r = 0;
        mColor.g = 0;
        mColor.b = 0;
    }
    mColor.a = color.a;
    return luminance;
}

// NON_MATCHING: same store merge as setColor.
void Unk_7102519708::setColorAndLuminance(const sead::Color4f& color) {
    _104 = setColor(color);
}

// NON_MATCHING: the original masks the view bit test with 0xffff before the branch.
void Unk_7102519708::drawDebug(agl::DrawContext* context, const sead::Matrix34f& view,
                               const sead::Matrix44f& projection, int view_index) const {
    if (!_50 || !(_48 & 1) || !m11())
        return;
    if (!(_5a & (1 << view_index)))
        return;

    sead::Vector3f dir = mDir;
    if (dir.equals(sead::Vector3f::ey, 0.01f))
        dir.set(0.01f, 0.99f, -0.01f);
    dir.normalize();
    agl::utl::DevTools::drawSpotLight(context, mPos - dir * _118, dir, mColor, _10c * 0.5f, _120,
                                      view, projection);
    agl::utl::DevTools::drawPointLight(context, mPos, _11c, mColor, view, projection);
}

void Unk_7102519708::m9() {
    _5c = 0;
}

void Unk_7102519708::m10() {
    _5c = 0;
}

bool Unk_7102519708::m11() const {
    return (_5c & 1) != 0;
}

Unk_7102519778::~Unk_7102519778() = default;

void Unk_7102519778::m9() {
    _5c = 0;
}

void Unk_7102519778::m10() {
    _5c = 0;
}

bool Unk_7102519778::m11() const {
    return (_5c & 1) != 0;
}

// The render-light records declare one to three float4 uniform arrays and select the
// current uniform buffer by index. NON_MATCHING (all m8): two registers swapped in the inlined
// agl::UniformBlock::setBufferIndexMaybe multiply.
void Unk_71025193e8::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(1, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 7, 0, 1);
    mUniformBlock.create(heap, 2, 1);
    u8* buffer = new (heap, 0x20, std::nothrow) u8[0x80];
    if (buffer) {
        mBufferCount = 0x80;
        mBuffer = buffer;
    }
}

void Unk_71025193e8::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_7102519460::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(3, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 6, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 4, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 4, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_7102519460::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_71025194d0::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(1, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 10, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_71025194d0::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_7102519540::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(3, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 6, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 4, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 4, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_7102519540::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_71025195b0::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(3, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 6, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 3, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 3, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_71025195b0::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_7102519620::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(2, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 4, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 7, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_7102519620::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_7102519690::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(1, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 7, 0, 1);
    mUniformBlock.create(heap, 2, 1);
    u8* buffer = new (heap, 0x20, std::nothrow) u8[0x80];
    if (buffer) {
        mBufferCount = 0x80;
        mBuffer = buffer;
    }
}

void Unk_7102519690::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_7102519708::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(2, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 4, 0, 1);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 7, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_7102519708::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

void Unk_7102519778::m6(sead::Heap* heap) {
    mUniformBlock.startDeclare(1, heap);
    mUniformBlock.declare_(static_cast<agl::UniformBlock::Type>(6), 10, 0, 1);
    mUniformBlock.create(heap, 2, 1);
}

void Unk_7102519778::m8(u8 index) {
    mUniformBlock.setBufferIndexMaybe(index);
}

