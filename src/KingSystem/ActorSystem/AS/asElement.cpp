#include "KingSystem/ActorSystem/AS/asElement.h"
#include <math/seadQuat.h>
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

void sub_7101165950(f32 weight, sead::Vector3f* out, const sead::Vector3f* a,
                  const sead::Vector3f* b) {
    if (weight < 0.01f) {
        *out = *a;
        return;
    }
    if (weight > 0.99f) {
        *out = *b;
        return;
    }
    const f32 length_a = a->length();
    const f32 length_b = b->length();
    if (length_a > 0.01f && length_b > 0.01f) {
        sead::Vector3f axis;
        axis.setCross(*a, *b);
        const f32 axis_length = axis.normalize();
        if (axis_length > 0.0001f) {
            sead::Quatf rotation;
            rotation.setAxisRadian(axis, sead::Mathf::atan2(axis_length, a->dot(*b)) * weight);
            sead::Matrix34f matrix;
            matrix.fromQuat(rotation);
            out->setMul(matrix, *a);
            const f32 length = out->length();
            if (length > 0.0f)
                *out *= ((1.0f - weight) * length_a + length_b * weight) / length;
            return;
        }
    }
    *out = (1.0f - weight) * *a + *b * weight;
}

// NON_MATCHING: the compiler saves the output pointer and weight in the opposite order.
void sub_71011658C0(f32 weight, sead::Matrix34f* out, const sead::Matrix34f* a,
                  const sead::Matrix34f* b) {
    sead::Vector3f translation_a;
    sead::Vector3f translation_b;
    a->getTranslation(translation_a);
    b->getTranslation(translation_b);
    sead::Matrix34CalcCommon<f32>::slerpTo(*out, *a, *b, weight);
    sead::Vector3f translation;
    sub_7101165950(weight, &translation, &translation_a, &translation_b);
    out->setTranslation(translation);
}

Element::Element() {}

bool Element::sub_71011654D8() {
    return false;
}

void Element::sub_7101165E60(Context* ctx, const res::ASResource* resource) {
    m35(ctx, resource);
    ctx->sub_7101258D70(sub_71011653E8(resource));
}

f32 Element::m4() {
    return 0;
}

void Element::m5() {}

int Element::m6() {
    return -1;
}

int Element::m7() {
    return 0;
}

bool Element::m8() {
    return true;
}

bool Element::m9(Context* ctx, PlayState* state, const res::ASResource* resource) {
    return true;
}

void Element::m11(Context* ctx, EventState* state, const res::ASResource* resource) {}
void Element::m12(Context* ctx, State* state, const res::ASResource* resource) {}
void Element::m13(Context* ctx, State* state, const res::ASResource* resource) {}
void Element::m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) {}
void Element::m15(Context* ctx, State* state, const res::ASResource* resource) {}
void Element::m16(Context* ctx, const res::ASResource* resource, f32 value) {}
void Element::m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5,
                  f32 a6) {}

f32 Element::m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) {
    return -1;
}

void Element::m19(Context* ctx, const res::ASResource* resource, f32 value) {}
void Element::m20(Context* ctx, const res::ASResource* resource, f32 value) {}
void Element::m21(Context* ctx, const res::ASResource* resource, f32 value) {}
void Element::m22(Context* ctx, const res::ASResource* resource) {}
Element* Element::m23(Context* ctx, const res::ASResource* resource) {
    return this;
}

bool Element::m24(Context* ctx, const res::ASResource* resource) {
    return true;
}

const ElementParams* Element::m25(Context* ctx, const res::ASResource* resource) {
    return nullptr;
}

int Element::sub_7101165408(const res::ASResource* resource) {
    if (resource)
        return res::getASElementFactoryField18(resource);
    return -1;
}

int Element::sub_71011653E8(const res::ASResource* resource) {
    if (resource)
        return resource->getIndex();
    return m7();
}

bool Element::sub_710116541C(Context* ctx, PlayState* state, const res::ASResource* resource) {
    const int index = sub_71011653E8(resource);
    ctx->sub_7101258D60(index, state->_8);
    state->_8 = ctx->sub_7101258D1C(index) + 1;
    Context::Record* record = ctx->sub_7101258CD4(index);
    record->_3 = 1;
    record->_3 = state->_4 ? 1 : 5;
    return m9(ctx, state, resource);
}

f32 Element::m26(Context* ctx, const res::ASResource* resource) {
    return ctx->sub_7101258CD4(resource ? resource->getIndex() : m7())->_8;
}

bool Element::m27(Context* ctx, const res::ASResource* resource) {
    return false;
}

void Element::m28(f32* a1, Context* ctx, const res::ASResource* resource) {}
void Element::m29(f32* a1, Context* ctx, const res::ASResource* resource) {}

int Element::m30(f32* a1, Context* ctx, const res::ASResource* resource) {
    return -1;
}

int Element::m31(Context* ctx, const res::ASResource* resource) {
    return -1;
}

bool Element::m32(Context* ctx, void* a2, void* a3, void* a4, void* a5,
                  const res::ASResource* resource, f32 value) {
    return false;
}

bool Element::m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5) {
    return false;
}

void Element::m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) {}
void Element::m35(Context* ctx, const res::ASResource* resource) {}

void Element::sub_7101165EBC(Context* ctx, sead::BufferedSafeString* out,
                             sead::BufferedSafeString& name, int index,
                             const res::ASResource* resource) {
    const int old_length = name.calcLength();
    name.appendWithFormat("/%d", index);
    m36(ctx, out, name, resource);
    name.trim(old_length);
}

void Element::m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
                  const res::ASResource* resource) {
    out->appendWithFormat("%s, ", name.cstr());
}

int Element::m37(Context* ctx, EventState* state, const res::ASResource* resource) {
    return 0;
}

int Element::sub_710116554C(Context* ctx, EventState* state, const res::ASResource* resource) {
    m11(ctx, state, resource);
    return m37(ctx, state, resource);
}

void Element::sub_71011654E0(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) {
    m37(ctx, a3, resource);
    m14(ctx, a2, a3, resource);
}

}  // namespace ksys::as
