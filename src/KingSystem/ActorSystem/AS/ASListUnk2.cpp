#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/System/VFR.h"

// Declaration only; the original source namespace/owner of this byte query is unknown.
bool sub_7100E9CF8C();

namespace ksys::as {

bool ASList::Unk2::sub_710116392C() {
    return (_41 & 4) && sub_7100E9CF8C();
}

// NON_MATCHING: the nonpositive clamp and direct field cleanup differ from the indexed loop.
void ASList::Unk2::sub_7101161D74() {
    if (!(_3c > 0.0f))
        return;
    _38 -= _0->sub_710125A9A8();
    f32 remaining = _38 * _3c;
    if (remaining <= 0.0f)
        remaining = 0.0f;
    _30 = 1.0f - remaining;
    sead::Mathf::chase(&_34, 1.0f, VFR::instance()->getDeltaFrame() * 0.34f);
    if (_30 >= 1.0f) {
        _3c = 0.0f;
        _20 = nullptr;
        _28 = nullptr;
    } else if (_34 >= 1.0f) {
        _28 = nullptr;
    }
}

// NON_MATCHING: the two temporary log-system strings have different address/store scheduling.
void ASList::Unk2::sub_7101161FDC() {
    if (!Element::sub_71011654D8())
        return;
    _0->mFlags &= ~0x40;
    act::Actor* actor = _0->sub_7101258ABC();
    if (!actor->isEditorNodeConnected())
        return;
    if (Element* element = _18) {
        sead::FixedSafeString<256> output;
        sead::FixedSafeString<128> path;
        sead::FixedSafeString<1280> message;
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->sub_7101165EBC(context, &output, path, 0, resource);
        const char* filename = actor->getParam()->getRes().mASList->getASFileName(_0->mUnk8);
        if (!filename)
            return;
        message.format("[ASPath][FromPick][Actor:%s][File:%s][Slot:%d][ASPath:%s]",
                       actor->getName().cstr(), filename, _42, output.cstr());
        actor->logForEditor("ASEditor", message);
    } else {
        sead::FixedSafeString<256> message;
        message.format("[ASPath][FromPick][Actor:%s][File:Dummy][Slot:%d][ASPath:/0]",
                       actor->getName().cstr(), _42);
        actor->logForEditor("ASEditor", message);
    }
}

void ASList::Unk2::sub_7101162C58(void* bones, BoneBlendState* state) {
    if (!_18)
        return;
    for (auto& range : mBoneWeightRanges)
        range.params = nullptr;
    state->_8 = bones;
    state->_10 = this;
    _0->sub_7101258C1C();
    mFlags &= 0xfdcf;
    if (_44[1]) {
        _44[1] = 0;
        _20 = nullptr;
        _28 = nullptr;
    }
    if (Element* element = _18) {
        state->_18 = 0;
        state->weight = _10 * _30;
        Context* context = _0;
        const res::ASResource* resource = context->sub_7101258CC0();
        element->m15(context, state, resource);
        _0->sub_7101258C48();
        if (Element* element2 = _20) {
            state->_18 = 1;
            state->weight = _10 * ((1.0f - _30) * _34);
            context = _0;
            const res::ASResource* resource2 = context->sub_7101258CC0();
            element2->m15(context, state, resource2);
            _0->sub_7101258C48();
            if (Element* element3 = _28) {
                state->_18 = 2;
                state->weight = _10 * ((1.0f - _30) * (1.0f - _34));
                context = _0;
                const res::ASResource* resource3 = context->sub_7101258CC0();
                element3->m15(context, state, resource3);
                _0->sub_7101258C48();
            }
        }
    }
    _0->sub_7101258C1C();
}

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

bool ASList::Unk2::sub_7101162254(bool a1) {
    if (!_18)
        return false;
    if (a1)
        sub_7101161EE0(-1.0f, _18, true);
    _10 = 1.0f;
    mFlags = 1;
    _48 = nullptr;
    _44[0] = 1;
    mBoneWeightRanges[0].params = nullptr;
    mBoneWeightRanges[1].params = nullptr;
    mBoneWeightRanges[2].params = nullptr;
    _18 = nullptr;
    _20 = nullptr;
    _28 = nullptr;
    if (_0->_d8) {
        _0->_d8 = nullptr;
        _0->sub_7101258C1C();
    }
    _0->mNumEvents2 = 0;
    _0->sub_710125923C();
    mFlags |= 8;
    _0->_e0 = 1.0f;
    sub_7101161FDC();
    return true;
}

// NON_MATCHING: the scheduling of the argument moves before the tail call to m17 (the original sets w2 / w3 after the
// ldp of the callee-saved registers)
void ASList::Unk2::sub_71011633C0(Unk2* other) {
    Element* element = _18;
    if (!element)
        return;
    Element* other_element = other->_18;
    if (!other_element)
        return;
    Context* other_context = other->_0;
    const res::ASResource* other_resource = other_context->sub_7101258CC0();
    if (const ElementParams* params = other_element->m25(other_context, other_resource)) {
        const f32 duration = params->sub_710130296C(false);
        Context* context = _0;
        if (duration <= 0.0f) {
            const res::ASResource* resource = context->sub_7101258CC0();
            element->m17(context, 0, 0, resource, 0.0f, 0.0f);
        } else {
            const f32 start = (params->_4 - params->_10) / duration;
            const f32 end = (params->_8 - params->_10) / duration;
            const res::ASResource* resource = context->sub_7101258CC0();
            element->m17(context, 0, 0, resource, start, end);
        }
    }
}

}  // namespace ksys::as
