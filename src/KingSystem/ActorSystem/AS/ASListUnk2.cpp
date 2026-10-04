#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

void ASList::Unk2::sub_7101163ADC(SequencePlayContainer* sequence,
                                const res::ASResource* resource, f32 value, f32 duration) {
    if (!_88) {
        _88 = sequence;
        _90 = resource;
        _80 = value;
        _84 = duration;
    }
}

// NON_MATCHING: the two signed boundary checks run in the opposite order.
void ASList::Unk2::sub_7101163960(s32 start, s32 middle, s32 end, s32 index,
                                const res::ASSetting::BoneParams* params) {
    if (start >= middle || middle >= end || !params)
        return;
    auto& range = mBoneWeightRanges[index];
    range.start = start;
    range.middle = middle;
    range.end = end;
    range.params = params;
}

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

bool ASList::Unk2::sub_7101162F7C(f32 value) {
    Element* element = _18;
    if (!element)
        return false;
    Context* context = _0;
    const res::ASResource* resource = context->sub_7101258CC0();
    if (auto* params = element->m25(context, resource))
        return params->sub_7101302878(value);
    return false;
}

f32 ASList::Unk2::sub_7101163354(bool a1) {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        if (auto* params = element->m25(context, resource))
            return params->sub_710130298C(a1);
    }
    return 0.0f;
}

void ASList::Unk2::sub_71011635C0() {
    if (Element* element = _18) {
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m22(context, resource);
    }
}

int ASList::Unk2::sub_710116360C(f32* out) {
    Element* element = _18;
    if (!element)
        return -1;
    f32 value = 0.0f;
    if (!out)
        out = &value;
    else
        *out = 0.0f;
    Context* context = _0;
    const res::ASResource* resource = context->sub_7101258CC0();
    return element->m30(out, context, resource);
}

int ASList::Unk2::sub_710116367C() {
    Element* element = _18;
    if (!element)
        return -1;
    Context* context = _0;
    const res::ASResource* resource = context->sub_7101258CC0();
    return element->m31(context, resource);
}

void ASList::Unk2::sub_71011637D8() {
    if (!_18)
        _0->mFlags = 0;
}

void ASList::Unk2::sub_7101163AD4(f32 value, int key) {
    _0->sub_710125A1A4(value, key);
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
