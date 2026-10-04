#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceASResource.h"

namespace ksys::as {

Element::Element() {}

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

void Element::m11(Context* ctx, State* state, const res::ASResource* resource) {}
void Element::m12(Context* ctx, State* state, const res::ASResource* resource) {}
void Element::m13(Context* ctx, State* state, const res::ASResource* resource) {}
void Element::m14(Context* ctx, void* a2, State* a3, const res::ASResource* resource) {}
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

void Element::m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
                  const res::ASResource* resource) {
    out->appendWithFormat("%s, ", name.cstr());
}

int Element::m37(Context* ctx, State* state, const res::ASResource* resource) {
    return 0;
}

int Element::sub_710116554C(Context* ctx, State* state, const res::ASResource* resource) {
    m11(ctx, state, resource);
    return m37(ctx, state, resource);
}

void Element::sub_71011654E0(Context* ctx, void* a2, State* a3, const res::ASResource* resource) {
    m37(ctx, a3, resource);
    m14(ctx, a2, a3, resource);
}

}  // namespace ksys::as
