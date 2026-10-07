#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAnimation.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include <gsys/gsysModelAccessKey.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/GameData/gdtFlagHandle.h"

namespace ksys::res {
class AS;
class ASResource;
// 0x71012ed388: field 0x18 of the AS element factory table entry of the resource's type index (declaration only).
int getASElementFactoryField18(const ASResource* resource);
}

// The runtime tree of the AS (animation sequence) system: one element per ASResource.
// Names are the CSV (IDA) names: `as::Element`, `as::SelectorBase`, `as::Blender`, ... Mostly sead-RTTI classes
// whose vtable slot numbers are the `mNN` placeholder names (slots 0-3 are the RTTI functions and the
// destructors). The tree classes are created from the resource by a factory; the CSV calls the first
// container base `SelectorBase` (it is shared by Selector, Blender, SequencePlayContainer and SyncPlayContainer).
// Classes are only declared as far as they are decompiled: undeclared overrides keep the base's entry in
// our vtable.
namespace ksys::act {
class Actor;
}

namespace ksys::as {

class Element;
class Unk_710125af7c;

// ASList-owned linked element list; source name inferred. Only the buffer prefix is modelled.
// This partial declaration must not be constructed or used to infer the original allocation size.
struct ElementList {
    sead::Buffer<Element*> elements;
};

class ASList;
struct BoneBlendState;
struct MotionState;

// Placeholder: per-element state block (a Frame entry; returned by Element::m25): flags in `_0`
// (bit 1 = running?), a range [_4, _8] and more floats.
struct ElementParams {
    // 0x7101302744 (out of line: the array allocation of Frame::mEntries and the static default call it).
    ElementParams();
    // (user-provided: the original's `delete[]` of a Frame's entry buffer reads an array cookie)
    ~ElementParams() {}

    // 0x7101302a70: like sub_7101302764, but advances from `position` by `dt` (the playback position is not read);
    // returns the number of wraps.
    s32 sub_7101302A70(f32 dt, f32 position);
    // 0x7101302930 / 38 / 40 / 48: stubs that return true (called after the float setters).
    bool sub_7101302930(void* a1);
    bool sub_7101302938(void* a1);
    bool sub_7101302940(void* a1);
    bool sub_7101302948(void* a1);
    // 0x7101302834 (flags bit 1 = running): finished test.
    bool sub_7101302834() const;
    // 0x7101302878: range test of `value` against [_4, _8] (the range may wrap).
    bool sub_7101302878(f32 value) const;
    // 0x71013029e4: linear interpolation between _10 and `_1c` (when `a` and set) or _14.
    f32 sub_71013029E4(bool a, f32 t) const;
    // 0x71013028bc: starts the playback (flags bit 1 = loop, bit 2, bit 4 = started); always returns true.
    bool sub_71013028BC(bool loop, bool a2, f32 position, f32 rate, f32 start, f32 length, f32 count);
    // 0x7101302764: advances the playback by `dt` (rate _c; wraps or clamps at the length _14).
    void sub_7101302764(f32 dt);
    // 0x7101302a1c: sets the playback position (wraps by the length _14 when looping).
    void sub_7101302A1C(f32 position);
    // 0x7101302950: _1c = _14 * value (if _1c is set).
    void sub_7101302950(f32 value);
    // 0x710130296c: duration from _10 to `_1c` (when `a` and set) or _14.
    f32 sub_710130296C(bool a) const;
    // 0x710130298c: progress ((current - _10) / duration), 0 if there is no duration.
    f32 sub_710130298C(bool a) const;

    u32 _0 = 0;
    f32 _4 = 0;
    f32 _8 = 0;
    f32 _c = 1.0f;
    f32 _10 = 0;
    f32 _14 = 0;
    f32 _18 = 0;
    f32 _1c = -1.0f;
};
static_assert(sizeof(ElementParams) == 0x20);

// Placeholder: the AS runtime state (x1 of most element virtuals). Per-element records are 12-byte entries
// reached through the element index of the resource.
class Context {
public:
    // 0x7101258608
    Context();
    // 0x7101258a4c: frees the frames' and the event buffers (the destructor of the original; D2).
    ~Context();

    struct Frame;

    struct Record {
        Record() { _3 = 0; }
        // 0x7101257df4: the element state block of the record (a shared empty block if it has none).
        ElementParams* sub_7101257DF4(Frame* frame, bool a2);
        // 0x7101257d90: releases the record's element state block and marks the record as free.
        void sub_7101257D90(Frame* frame);

        s8 _0;
        u8 _1;
        s8 _2;
        u8 _3;
        f32 _4;
        f32 _8;
    };

    struct Frame {
        // Sizes of the buffers of a frame (a part of the AS resource).
        struct Sizes {
            ASList* mList;
            u8 _8[0x10 - 0x8];
            s32 mNumRecords;
            s32 mNumIndices;
            s32 mNumEntries;
            s32 mNum930;
        };
        // 0x7101257f0c: allocates the three buffers (false if a size is out of range or on failure).
        bool sub_7101257F0C(const Sizes& sizes, sead::Heap* heap);
        // 0x7101257e38 (out of line: the array allocation of ASList's frame buffer calls it).
        Frame();
        // 0x7101257e54: frees the buffers (the same as finalize()).
        ~Frame();
        // 0x7101257eb0: frees the three buffers.
        void finalize();
        // 0x71012580e0: copies the contents of `other` (false if the buffer sizes differ).
        bool sub_71012580E0(const Frame& other);
        // 0x7101258398: releases every record and unmaps every element.
        void sub_7101258398();
        // 0x710125848c: maps element `element` to a free record, searching from `hint`.
        void sub_710125848C(int element, int hint);
        // 0x7101258570: gives the record of element `element` the first free element state block.
        void sub_7101258570(int element);

        sead::Buffer<Record> mRecords;
        sead::Buffer<ElementParams> mEntries;
        sead::Buffer<u8> mIndexMap;  // element index -> record index
        res::AS* mAS = nullptr;
    };
    static_assert(sizeof(Frame) == 0x38);

    // 0x7101258d4c: the element state block of `record` in the current frame.
    ElementParams* sub_7101258D4C(Record* record, bool a2);
    // 0x7101258d1c: the record index of the element `index` (0 in the 'record 0' mode).
    int sub_7101258D1C(int index);
    // 0x710125aaa0: sets the value of the element's entry in the three pending (index, value) pairs.
    void sub_710125AAA0(u32 index, s16 value);
    // 0x710125aa38: returns the pending value for the index, or -1 if none is queued.
    s32 sub_710125AA38(u32 index);
    // 0x710125a9a8: delta time scaled by context and the actor's common AS rate.
    f32 sub_710125A9A8();
    // 0x710125a1a4: sets the pending value of `key` (no check for an earlier one).
    void sub_710125A1A4(f32 value, int key);
    // 0x710125a164: the pending value of `key` (0 if there is none).
    f32 sub_710125A164(u32 key);
    // 0x710125a1f0: stores `value` as the pending value of `key` (once per update); the
    // element and its resource are passed on to the unnamed 0x710125a248.
    void sub_710125A1F0(f32 value, int key, Element* element, const res::ASResource* resource);
    // 0x710125a248: advances the input value of key, applying the resource input limit.
    void sub_710125A248(f32 value, u32 key, Element* element, const res::ASResource* resource);
    // 0x710125a630: clears pending bits that were not applied during this update.
    void sub_710125A630();
    // 0x710125a67c: copies the active frame and state; reset_events omits the event banks.
    bool sub_710125A67C(const Context& other, bool reset_events);
    // 0x710125a924: copies the preceding ring frame from the other context.
    bool sub_710125A924(const Context& other);
    // 0x7101259990: tests the active/previous event-bank overlap and update flags.
    bool sub_7101259990(bool a1);
    // 0x7101259de8 / 0x7101259f94: queues trigger/hold events.
    void sub_7101259DE8(f32 weight, int type, const sead::SafeString& value);
    void sub_7101259F94(f32 duration, f32 weight, int type, const sead::SafeString& value);
    // 0x7101258cd4: the record of the element `index` (record 0 if the context is not in the used state).
    Record* sub_7101258CD4(int index);

    // 0x7101258c1c / c48 / c80: select the current frame (_f4) of the 3-frame ring.
    void sub_7101258C1C();
    void sub_7101258C48();
    void sub_7101258C80();
    // 0x7101258e08 / e14 / e20: sizes / fields of the current frame.
    int sub_7101258E08();
    int sub_7101258E14();
    int sub_7101258E20();
    // 0x7101258e2c: the list's model.
    gsys::Model* sub_7101258E2C();
    // 0x710125923c: clears both strings.
    void sub_710125923C();

    // 0x7101258cc0: the first element resource of the AS of the current frame (null if none).
    res::ASResource* sub_7101258CC0();
    // 0x7101258abc: the owner actor of the list.
    act::Actor* sub_7101258ABC();

    /* 0x00 */ ASList* mList = nullptr;
    /* 0x08 */ sead::SafeString mUnk8;
    /* 0x18 */ sead::SafeString mUnk18;  // PreASSelector::m40 returns its string
    /* 0x28 */ sead::SafeArray<Frame, 3> mFrames;
    /* 0xd0 */ Frame* _d0 = &mFrames[0];  // the current frame
    /* 0xd8 */ Frame* _d8 = nullptr;  // overrides the ring when set
    /* 0xe0 */ f32 _e0 = 1.0f;
    /* 0xe4 */ f32 _e4 = 1.0f;
    /* 0xe8 */ f32 _e8 = -1.0f;
    /* 0xec */ f32 _ec = 0;  // delta time
    /* 0xf0 */ f32 _f0 = -1.0f;
    /* 0xf4 */ u8 _f4 = 0;
    /* 0xf5 */ u8 _f5 = 0;
    /* 0xf6 */ s8 _f6 = 0;  // index of the current event bank
    /* 0xf7 */ s8 mNumEvents2 = 0;
    /* 0xf8 */ u8 _f8 = 0;
    /* 0xf9 */ s8 _f9 = 0;  // number of pending index/value pairs
    /* 0xfa */ u8 _fa = 0;
    u8 _fb[0x100 - 0xfb];

    // The events queued while the frame is evaluated (two banks each, selected by `_f6`; each bank holds up to 16).
    struct EventA {
        f32 mDuration;
        f32 _4;
        sead::SafeString mName;
        f32 _18;
        u32 _1c;
    };
    struct EventB {
        f32 mDuration;
        f32 _4;
        sead::SafeString mName;
        s32 _18;
        u32 _1c;
    };
    template <typename Event>
    struct EventBank {
        sead::SafeArray<Event, 16> mEvents;
        s32 mCount;
        u32 _204;
    };
    static_assert(sizeof(EventBank<EventA>) == 0x208);

    // 0x7101259274 / 0x710125930c: queue an event on the current bank of the first / second kind (only while
    // `_f4 == _f5`; the duration is at least 1).
    void sub_7101259274(f32 a0, f32 duration, f32 a2, const sead::SafeString& name);
    void sub_710125930C(f32 a0, f32 duration, const sead::SafeString& name, s32 a3);
    // 0x7101259bd8: ends the expiring events of types 12 / 65 / 66 and promotes the finished ones.
    void sub_7101259BD8();
    // 0x71012590bc: expires the events (`a`: the first-bank variant).
    void sub_71012590BC(bool a);
    // 0x7101258d70: releases the record of element `index` and unmaps it.
    void sub_7101258D70(int index);
    // 0x7101258d60 / 0x7101258d68: Frame::sub_710125848C / sub_7101258570 on the current frame.
    void sub_7101258D60(int element, int hint);
    void sub_7101258D68(int element);
    // 0x7101258e38: starts the evaluation of a frame of the AS `as` (`frame`: a frame to use instead of the ring).
    void sub_7101258E38(f32 a0, const sead::SafeString& name, res::AS* as, Frame* frame, bool a4, bool a5);
    // 0x7101258ac8: sets the list and allocates the three frames and the `_930` buffer.
    bool sub_7101258AC8(const Frame::Sizes& sizes, sead::Heap* heap);
    // 0x7101258f4c: ends the evaluation of the frame (`a`: ...) and flips the event bank.
    void sub_7101258F4C(u32 a, u32 b);

    /* 0x100 */ sead::SafeArray<EventBank<EventA>, 2> mBanksA{};
    /* 0x510 */ sead::SafeArray<EventBank<EventB>, 2> mBanksB{};
    /* 0x920 */ union {
        u32 mFlags = 0;
        struct {
            u8 _920;
            u8 _921;
        };
    };
    /* 0x924 */ u32 _924 = 0;
    /* 0x928 */ u32 _928 = 0;
    u8 _92c[0x930 - 0x92c];
    /* 0x930 */ sead::Buffer<f32> _930;
    struct Event2 {
        u16 mType;
        u16 mFlags = 0;
        sead::SafeString mName;
        f32 _18;
        f32 _1c;
    };
    /* 0x940 */ sead::SafeArray<Event2, 32> mEvents2{};
    struct PendingValue {
        u16 index;
        s16 value;
    };
    /* 0xd40 */ sead::SafeArray<PendingValue, 3> mPendingValues{};
};


// Placeholder: the state passed down the tree by the update virtuals (m10, ...): `weight` is scaled by the
// blenders on their way down.
struct State {
    f32 _0;
    f32 weight;
    u8 _8[0x30 - 0x8];
    f32 _30;
};

// Three event flags, separate from the playback State. Callers 0x71011634c0,
// 0x7101161824 and 0x7101162940 construct three bytes for m11/m14/m37.
struct EventState {
    bool _0;
    bool _1;
    bool _2;
};
static_assert(sizeof(EventState) == 3);

// Placeholder: the state of the m9 virtual (offset 0 / 4 / 8 are the only fields seen: a kind, a flag that
// picks the record's state (1 / 5), and a counter that Element::sub_710116541C advances).
struct PlayState {
    f32 _0;
    bool _4;
    s32 _8;
};

// 0x7101165950: blends vector direction and length, with a linear fallback for small vectors/angles.
void sub_7101165950(f32 weight, sead::Vector3f* out, const sead::Vector3f* a, const sead::Vector3f* b);
// 0x71011658c0: `out` = the blend of `a` and `b` by `weight` (slerp of the rotation part and the
// translations through the unnamed 0x7101165950). `out` may alias `a`.
void sub_71011658C0(f32 weight, sead::Matrix34f* out, const sead::Matrix34f* a, const sead::Matrix34f* b);

class Element {
    SEAD_RTTI_BASE(Element)
public:
    // Recovered creation-record prefix; its list pointer and flags tail are not modelled.
    // Do not construct this partial declaration or infer its full size.
    struct CreateArg {
        gsys::Model* model;
        sead::Heap* heap;
        res::AS* as;
        act::Actor* actor;
        // Partial skeletal animation source tree, consumed by SkeltalAsset::m8.
        Unk_710125af7c* partialSkeletalSources;
    };

    struct InitArg {
        const CreateArg* createArg;
        const res::ASResource* resource;
        ElementList* list;
        sead::SafeArray<s16, 512>* indexMap;
    };

    Element();
    virtual ~Element() = default;

    // 0x71011653e8: the index of `resource` (this->m7() if there is none).
    int sub_71011653E8(const res::ASResource* resource);
    // 0x71011654d8: returns false.
    static bool sub_71011654D8();
    // 0x710116541c: maps the element's record (`state->_8` + 1 becomes the record's index) and calls m9.
    bool sub_710116541C(Context* ctx, PlayState* state, const res::ASResource* resource);
    // 0x7101165408: the factory table field 0x18 of `resource` (-1 if there is none).
    int sub_7101165408(const res::ASResource* resource);
    // 0x710116554c: m11 followed by m37.
    int sub_710116554C(Context* ctx, EventState* state, const res::ASResource* resource);
    // 0x71011654e0: m37 followed by m14.
    void sub_71011654E0(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource);
    // 0x7101165e60 / 0x7101165ebc: used by SelectorBase::m35 / m36.
    void sub_7101165E60(Context* ctx, const res::ASResource* resource);
    void sub_7101165CA8(Context* ctx, bool a1, const res::ASResource* resource, f32 value,
                       f32 a2, f32 a3);
    void sub_7101165EBC(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
                        int index, const res::ASResource* resource);

    virtual f32 m4();
    virtual void m5(act::Actor* actor, gsys::Model* model, const sead::SafeString& name,
                    sead::Heap* heap, const res::AS* as);
    virtual int m6();
    virtual int m7();
    virtual bool m8(const InitArg& arg);
    virtual bool m9(Context* ctx, PlayState* state, const res::ASResource* resource);
    virtual bool m10(Context* ctx, State* state, const res::ASResource* resource) = 0;
    virtual void m11(Context* ctx, EventState* state, const res::ASResource* resource);
    virtual void m12(Context* ctx, State* state, const res::ASResource* resource);
    virtual void m13(Context* ctx, State* state, const res::ASResource* resource);
    virtual void m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource);
    virtual void m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource);
    virtual void m16(Context* ctx, const res::ASResource* resource, f32 value);
    virtual void m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5,
                     f32 a6);
    virtual f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource);
    virtual void m19(Context* ctx, const res::ASResource* resource, f32 value);
    virtual void m20(Context* ctx, const res::ASResource* resource, f32 value);
    virtual void m21(Context* ctx, const res::ASResource* resource, f32 value);
    virtual void m22(Context* ctx, const res::ASResource* resource);
    virtual Element* m23(Context* ctx, const res::ASResource* resource);
    virtual bool m24(Context* ctx, const res::ASResource* resource);
    virtual const ElementParams* m25(Context* ctx, const res::ASResource* resource);
    virtual f32 m26(Context* ctx, const res::ASResource* resource);
    virtual bool m27(Context* ctx, const res::ASResource* resource);
    virtual void m28(f32* a1, Context* ctx, const res::ASResource* resource);
    virtual void m29(f32* a1, Context* ctx, const res::ASResource* resource);
    virtual int m30(f32* a1, Context* ctx, const res::ASResource* resource);
    virtual int m31(Context* ctx, const res::ASResource* resource);
    virtual bool m32(Context* ctx, void* a2, void* a3, void* a4, void* a5,
                     const res::ASResource* resource, f32 value);
    virtual bool m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5);
    virtual void m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource);
    virtual void m35(Context* ctx, const res::ASResource* resource);
    virtual void m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
                     const res::ASResource* resource);
    virtual int m37(Context* ctx, EventState* state, const res::ASResource* resource);
};

class SelectorBase : public Element {
    SEAD_RTTI_OVERRIDE(SelectorBase, Element)
public:
    bool m8(const InitArg& arg) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    SelectorBase();
    ~SelectorBase() override;

    void m11(Context* ctx, EventState* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) override;
    void m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) override;
    void m16(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5,
             f32 a6) override;
    void m19(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m20(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m21(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m22(Context* ctx, const res::ASResource* resource) override;
    Element* m23(Context* ctx, const res::ASResource* resource) override;
    bool m24(Context* ctx, const res::ASResource* resource) override;
    const ElementParams* m25(Context* ctx, const res::ASResource* resource) override;
    f32 m26(Context* ctx, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;
    void m28(f32* a1, Context* ctx, const res::ASResource* resource) override;
    void m29(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m30(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m31(Context* ctx, const res::ASResource* resource) override;
    bool m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5) override;
    void m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) override;
    void m35(Context* ctx, const res::ASResource* resource) override;
    void m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
             const res::ASResource* resource) override;

    // 0x71013031fc: the resource of the child `index` (null if `resource` has no children).
    const res::ASResource* sub_71013031FC(const res::ASResource* resource, int index) const;
    // 0x71013031b4: the selected child index of the element (`*out`), true if there is one.
    bool sub_71013031B4(s32* out, Context* ctx, const res::ASResource* resource);

    sead::Buffer<Element*> mChildren;
};
KSYS_CHECK_SIZE_NX150(SelectorBase, 0x18);

class Selector : public SelectorBase {
    SEAD_RTTI_OVERRIDE(Selector, SelectorBase)
public:
    Selector();

    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) override;
    bool m32(Context* ctx, void* a2, void* a3, void* a4, void* a5, const res::ASResource* resource,
             f32 value) override;

    virtual void m38(Context* ctx, const res::ASResource* resource);
    virtual int m39(Context* ctx, u32 a2, const res::ASResource* resource);
};

class BoolSelector : public Selector {
    SEAD_RTTI_OVERRIDE(BoolSelector, Selector)
public:
    BoolSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

// Placeholder: selects the child whose value equals an integer parameter (ctor reads it from the owner).
class IntSelector : public Selector {
    SEAD_RTTI_OVERRIDE(IntSelector, Selector)
public:
    IntSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
    // 0x7101260fc0: looks up the owner value in the resource's selector entries.
    static s32 getValue(act::Actor* actor, const res::ASResource* resource);

    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;

    /* 0x18 */ s32 _18;
};
KSYS_CHECK_SIZE_NX150(IntSelector, 0x20);

class ComboSelector : public Selector {
    SEAD_RTTI_OVERRIDE(ComboSelector, Selector)
public:
    ComboSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class NodePosSelector : public Selector {
    SEAD_RTTI_OVERRIDE(NodePosSelector, Selector)
public:
    // The initializer constructs the bone key and its fixed bone-name string before setting the callback.
    struct Unk1 {
        gsys::BoneAccessKeyEx _0;
        sead::FixedSafeString<64> _38;
        f32 (*_90)(const sead::Vector3f&);
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x98);

    NodePosSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
    ~NodePosSelector() override;

    bool m8(const InitArg& arg) override;
    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;

    sead::Buffer<Unk1> _18;
};

class FloatSelector : public Selector {
    SEAD_RTTI_OVERRIDE(FloatSelector, Selector)
public:
    FloatSelector();

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;

    virtual f32 m40(Context* ctx, u32 a2, const res::ASResource* resource);
};

class StringSelector : public Selector {
    SEAD_RTTI_OVERRIDE(StringSelector, Selector)
public:
    StringSelector();

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
    // 0x710131d9f0: the string of the selected entry of the resource's string array (empty if none).
    const sead::SafeString& sub_710131D9F0(Context* ctx, const res::ASResource* resource);

    virtual const char* m40(Context* ctx, const res::ASResource* resource);
};

class ZEx00ExposureSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(ZEx00ExposureSelector, FloatSelector)
public:
    ZEx00ExposureSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class GroundNormalSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(GroundNormalSelector, FloatSelector)
public:
    GroundNormalSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class GroundNormalSideSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(GroundNormalSideSelector, FloatSelector)
public:
    GroundNormalSideSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class AngleSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(AngleSelector, FloatSelector)
public:
    AngleSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
    virtual f32 m41();
    virtual f32 m42();
};

class RandomSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(RandomSelector, FloatSelector)
public:
    RandomSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class PreExclusionRandomSelector : public RandomSelector {
    SEAD_RTTI_OVERRIDE(PreExclusionRandomSelector, RandomSelector)
public:
    PreExclusionRandomSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class SpeedSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(SpeedSelector, FloatSelector)
public:
    SpeedSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class YSpeedSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(YSpeedSelector, FloatSelector)
public:
    YSpeedSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class EventFlagSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(EventFlagSelector, StringSelector)
public:
    EventFlagSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    bool m8(const InitArg& arg) override;
    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
    const char* m40(Context* ctx, const res::ASResource* resource) override;
    ~EventFlagSelector() override;

    sead::Buffer<gdt::FlagHandle> _18;
};

class PreASSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(PreASSelector, StringSelector)
public:
    PreASSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    const char* m40(Context* ctx, const res::ASResource* resource) override;
};

class TimeSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(TimeSelector, StringSelector)
public:
    TimeSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    const char* m40(Context* ctx, const res::ASResource* resource) override;
};

class WeatherSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(WeatherSelector, StringSelector)
public:
    WeatherSelector(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    const char* m40(Context* ctx, const res::ASResource* resource) override;
};

class Blender : public SelectorBase {
    SEAD_RTTI_OVERRIDE(Blender, SelectorBase)
public:
    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m11(Context* ctx, EventState* state, const res::ASResource* resource) override;
    bool m32(Context* ctx, void* a2, void* a3, void* a4, void* a5, const res::ASResource* resource,
             f32 value) override;
    bool m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) override;
    void m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) override;
    void m16(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5,
             f32 a6) override;
    void m19(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m20(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m21(Context* ctx, const res::ASResource* resource, f32 value) override;
    f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) override;
    void m22(Context* ctx, const res::ASResource* resource) override;
    f32 m26(Context* ctx, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;
    void m28(f32* a1, Context* ctx, const res::ASResource* resource) override;
    void m29(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m30(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m31(Context* ctx, const res::ASResource* resource) override;
    void m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) override;
    void m35(Context* ctx, const res::ASResource* resource) override;
    void m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
             const res::ASResource* resource) override;
    Blender();

    // 0x71013166c4: updates the (up to two) blended children of `record` (the first child's m9 finishing
    // fades the record out, the second one's drops the second child).
    bool sub_71013166C4(Context::Record* record, Context* ctx, PlayState* state,
                        const res::ASResource* resource);

    // 0x7101316bc0: updates the blended duration in the context record.
    void sub_7101316BC0(Context* ctx, const res::ASResource* resource);

    virtual f32 m38(Context* ctx, const res::ASResource* resource);
    // Picks the child (and the one it is blended with) whose range contains the element's input value; returns
    // the blend weight of the second child.
    virtual f32 m39(s32* first, s32* second, Context* ctx, const res::ASResource* resource);
};

class BoneBlender : public Blender {
    SEAD_RTTI_OVERRIDE(BoneBlender, Blender)
public:
    BoneBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;
    f32 m39(s32* first, s32* second, Context* ctx, const res::ASResource* resource) override;
};

class ZEx00ExposureBlender : public Blender {
    SEAD_RTTI_OVERRIDE(ZEx00ExposureBlender, Blender)
public:
    ZEx00ExposureBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class GroundNormalBlender : public Blender {
    SEAD_RTTI_OVERRIDE(GroundNormalBlender, Blender)
public:
    GroundNormalBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class GroundNormalSideBlender : public Blender {
    SEAD_RTTI_OVERRIDE(GroundNormalSideBlender, Blender)
public:
    GroundNormalSideBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class AngleBlender : public Blender {
    SEAD_RTTI_OVERRIDE(AngleBlender, Blender)
public:
    AngleBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
    f32 m39(s32* first, s32* second, Context* ctx, const res::ASResource* resource) override;

    virtual f32 m40();
    virtual f32 m41();
};

class SpeedBlender : public Blender {
    SEAD_RTTI_OVERRIDE(SpeedBlender, Blender)
public:
    SpeedBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class WindVelocityBlender : public Blender {
    SEAD_RTTI_OVERRIDE(WindVelocityBlender, Blender)
public:
    WindVelocityBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class YSpeedBlender : public Blender {
    SEAD_RTTI_OVERRIDE(YSpeedBlender, Blender)
public:
    YSpeedBlender(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class SyncPlayContainer : public SelectorBase {
    SEAD_RTTI_OVERRIDE(SyncPlayContainer, SelectorBase)
public:
    int m7() override;
    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m11(Context* ctx, EventState* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* a2, EventState* a3, const res::ASResource* resource) override;
    void m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) override;
    void m16(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 a5,
             f32 a6) override;
    f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) override;
    void m19(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m20(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m21(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m22(Context* ctx, const res::ASResource* resource) override;
    bool m24(Context* ctx, const res::ASResource* resource) override;
    f32 m26(Context* ctx, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;
    void m28(f32* a1, Context* ctx, const res::ASResource* resource) override;
    void m29(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m30(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m31(Context* ctx, const res::ASResource* resource) override;
    bool m32(Context* ctx, void* a2, void* a3, void* a4, void* a5, const res::ASResource* resource,
             f32 value) override;
    bool m33(Context* ctx, void* a2, void* a3, const res::ASResource* resource, f32 a5) override;
    void m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) override;
    void m35(Context* ctx, const res::ASResource* resource) override;
    void m36(Context* ctx, sead::BufferedSafeString* out, sead::BufferedSafeString& name,
             const res::ASResource* resource) override;
    SyncPlayContainer(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
};

// A container that plays its children one after the other (CSV: ASSequencePlayContainer).
class SequencePlayContainer : public SelectorBase {
    SEAD_RTTI_OVERRIDE(SequencePlayContainer, SelectorBase)
public:
    SequencePlayContainer(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    // (the first out-of-line virtual: the vtable is emitted with it)
    bool m24(Context* ctx, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;
    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    // 0x710125ebb0: advances the sequence (declaration only).
    u32 sub_710125EBB0(Context* ctx, State* state, const res::ASResource* resource);
    void sub_710125F94C(Context* ctx, const res::ASResource* resource, f32 value, f32 duration);
    void m16(Context* ctx, const res::ASResource* resource, f32 value) override {}
    f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) override;
    void m19(Context* ctx, const res::ASResource* resource, f32 value) override {}
    void m20(Context* ctx, const res::ASResource* resource, f32 value) override {}
    void m21(Context* ctx, const res::ASResource* resource, f32 value) override {}
    void m22(Context* ctx, const res::ASResource* resource) override {}
    bool m32(Context* ctx, void* a2, void* a3, void* a4, void* a5, const res::ASResource* resource,
             f32 value) override;
};

class Asset : public Element {
    SEAD_RTTI_OVERRIDE(Asset, Element)
public:
    Asset();
};

// Placeholder: an animation asset. `_a` is the index of the resource (res::ASResource::getIndex()).
class AnmAsset : public Asset {
    SEAD_RTTI_OVERRIDE(AnmAsset, Asset)
public:
    // 0x7101314a4c: `value` is the initial index of the resource (replaced by the resource's index if there is one).
    AnmAsset(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);

    f32 m4() override;
    int m6() override;
    int m7() override;
    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m16(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m17(Context* ctx, u32 a2, u32 a3, const res::ASResource* resource, f32 from,
             f32 to) override;
    // 0x7101315328: computes playback position and start/end frames.
    void sub_7101315328(f32* position, f32* start, f32* end, const res::ASResource* resource);
    // 0x7101315430 (lane1 s47, placeholder name): returns `_8` (the loop flag; the resource is not used).
    bool sub_7101315430(const res::ASResource* resource);
    // 0x710131586c: stores original loop mode and applies the resource override.
    void sub_710131586C(bool loop, const res::ASResource* resource);
    // 0x7101315930 (declaration only): obtains the current animation frame.
    f32 sub_7101315930(Context* ctx, const res::ASResource* resource);
    // 0x7101315ad0: advances playback, returning the remaining time and writing start/wrap count.
    f32 sub_7101315AD0(ElementParams* params, f32* start, s32* wraps, bool restart,
                      const res::ASResource* resource, f32 time);
    // 0x7101314bcc (1.6 KB, not decompiled; declaration only): starts the element's animation for m9
    // (`weight` and `flag` are the first two fields of the PlayState). Placeholder signature.
    bool sub_7101314BCC(f32 weight, Context* ctx, bool flag, const res::ASResource* resource);
    // 0x1315cb0 (declaration only)
    f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) override;
    void m19(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m20(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m21(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m22(Context* ctx, const res::ASResource* resource) override;
    const ElementParams* m25(Context* ctx, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;

    int m37(Context* ctx, EventState* state, const res::ASResource* resource) override;

    /* 0x08 */ bool _8;
    /* 0x09 */ bool _9;
    /* 0x0a */ s16 _a;
    /* 0x0c */ f32 _c;
};
KSYS_CHECK_SIZE_NX150(AnmAsset, 0x10);

class GraphicsAsset : public AnmAsset {
    SEAD_RTTI_OVERRIDE(GraphicsAsset, AnmAsset)
public:
    void m5(act::Actor* actor, gsys::Model* model, const sead::SafeString& name,
            sead::Heap* heap, const res::AS* as) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* state, EventState* events, const res::ASResource* resource) override;
    int m31(Context* ctx, const res::ASResource* resource) override;

    /* 0x10 */ gsys::AnimationAccessKey<gsys::MaterialAnmType> mKey;
    /* 0x14 */ gsys::MaterialAnmType _14;
};
KSYS_CHECK_SIZE_NX150(GraphicsAsset, 0x18);

class SkeltalAsset : public AnmAsset {
    SEAD_RTTI_OVERRIDE(SkeltalAsset, AnmAsset)
public:
    // Placeholder: the object at +0x18 (a partial-skeletal-animation source); its vector at +0x28 is added to
    // the output of m34.
    struct Unk18 {
        // Vtable 0x7102517148: D1/D0 followed by the child-link reset at 0x710125b118.
        virtual ~Unk18();
        virtual void sub_710125B118();
        Unk18* _8;
        Unk18* _10;
        u8 _18[0x20 - 0x18];
        gsys::AnimationAccessKey<gsys::SkeletalAnmType> mKey;
        bool _24;
        bool _25;
        const sead::Vector3f* _28;
    };
    static_assert(sizeof(Unk18) == 0x30);

    // 0x710125c568
    SkeltalAsset(const CreateArg& arg, s32 value);
    // 0x710125c384 (declaration only)
    SkeltalAsset(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
    ~SkeltalAsset() override;

    void m5(act::Actor* actor, gsys::Model* model, const sead::SafeString& name,
            sead::Heap* heap, const res::AS* as) override;
    bool m8(const InitArg& arg) override;
    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* state, EventState* events, const res::ASResource* resource) override;
    void sub_710125CB88(Context* ctx, MotionState* state, const res::ASResource* resource);
    void m15(Context* ctx, BoneBlendState* state, const res::ASResource* resource) override;
    f32 m18(Context* ctx, bool a2, f32 a3, f32 a4, const res::ASResource* resource) override;
    void m28(f32* a1, Context* ctx, const res::ASResource* resource) override;
    void m29(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m30(f32* a1, Context* ctx, const res::ASResource* resource) override;
    void m34(void* a1, Context* ctx, void* a3, const res::ASResource* resource) override;

    /* 0x10 */ gsys::AnimationAccessKey<gsys::SkeletalAnmType> mKey;
    /* 0x18 */ Unk18* _18;
};
KSYS_CHECK_SIZE_NX150(SkeltalAsset, 0x20);

// Original tree lookup/create at 0x710125af7c; implementation remains declared only.
class Unk_710125af7c {
public:
    bool sub_710125AF7C(SkeltalAsset::Unk18** out,
                       const gsys::AnimationAccessKey<gsys::SkeletalAnmType>* key,
                       gsys::Model* model, act::Actor* actor, sead::Heap* heap);
};

class ClearMatAnmAsset : public Asset {
    SEAD_RTTI_OVERRIDE(ClearMatAnmAsset, Asset)
public:
    bool m9(Context* ctx, PlayState* state, const res::ASResource* resource) override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    ClearMatAnmAsset(const CreateArg& arg, s32 value, const res::ASResource* resource);
    static Element* make(const CreateArg& arg, s32 value, const res::ASResource* resource);
};

}  // namespace ksys::as
