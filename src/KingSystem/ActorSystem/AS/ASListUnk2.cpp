#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

void ASList::Unk2::sub_71011634C0(f32 value) {
    Element* element = _18;
    if (!element)
        return;
    _0->_f0 = value;
    Context* context = _0;
    const res::ASResource* resource = context->sub_7101258CC0();
    element->m18(context, false, value, 1.0f, resource);
    EventState state;
    state._0 = false;
    state._1 = true;
    state._2 = false;
    context = _0;
    resource = context->sub_7101258CC0();
    element->sub_710116554C(context, &state, resource);
}

const sead::SafeString* ASList::Unk2::sub_7101161CD8() {
    if (!_18)
        return &sead::SafeString::cEmptyString;
    return &_0->mUnk8;
}

void ASList::Unk2::sub_71011631BC(f32 value) {
    if (value < 0)
        return;
    _0->_e0 = value;
}

// NON_MATCHING: callee-saved register numbers (element / a1 swapped)
void ASList::Unk2::sub_7101161CF8(bool a1, f32 value) {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m17(context, 0, a1, resource, value, value);
    }
}

}  // namespace ksys::as
