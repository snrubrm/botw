#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"

namespace ksys::as {

// NON_MATCHING: equivalent nonpositive clamp and swapped element/context registers.
void ASList::Unk2::sub_71011627C4(State* state) {
    _28 = _20;
    _20 = _18;
    _34 = _30;
    _30 = 0.0f;
    _43 = (_43 << 1) | 1;
    if (state) {
        Context::Frame* previous = _0->_d0;
        _0->sub_7101258C80();
        _0->_d0->sub_71012580E0(*previous);
        _88->sub_710125F94C(_0, _90, _84, _80);
        state->weight = 1.0f;
        Context* context = _0;
        Element* element = _18;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m12(context, state, resource);
        context = _0;
        element = _18;
        resource = context->sub_7101258CC0();
        element->m13(context, state, resource);
        state->weight = 1.0f;
        context = _0;
        element = _18;
        resource = context->sub_7101258CC0();
        element->m10(context, state, resource);
        _0->mFlags |= 0x10;
    } else if (_48) {
        _84 = _48->_84;
        _80 = _48->_80;
        _0->sub_7101258C80();
        _0->sub_710125A924(*_48->_0);
    }
    _38 = _84 - _80;
    if (_38 <= 0.0f)
        _38 = 0.0f;
    _3c = 1.0f / _84;
    _30 = 1.0f - _38 * _3c;
}

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
