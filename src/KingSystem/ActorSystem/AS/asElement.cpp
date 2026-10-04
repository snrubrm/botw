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

bool Element::m9() {
    return true;
}

void Element::m11() {}
void Element::m12() {}
void Element::m13() {}
void Element::m14() {}
void Element::m15() {}
void Element::m16() {}
void Element::m17() {}

f32 Element::m18() {
    return -1;
}

void Element::m19() {}
void Element::m20() {}
void Element::m21() {}
void Element::m22() {}
void Element::m23() {}

bool Element::m24() {
    return true;
}

void* Element::m25() {
    return nullptr;
}

int Element::sub_71011653E8(const res::ASResource* resource) {
    if (resource)
        return resource->getIndex();
    return m7();
}

f32 Element::m26(Context* ctx, const res::ASResource* resource) {
    return ctx->sub_7101258CD4(resource ? resource->getIndex() : m7())->_8;
}

int Element::m27() {
    return 0;
}

void Element::m28() {}
void Element::m29() {}

int Element::m30() {
    return -1;
}

int Element::m31() {
    return -1;
}

int Element::m32() {
    return 0;
}

int Element::m33() {
    return 0;
}

void Element::m34() {}
void Element::m35() {}

void Element::m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name) {
    out->appendWithFormat("%s, ", name.cstr());
}

int Element::m37() {
    return 0;
}

}  // namespace ksys::as
