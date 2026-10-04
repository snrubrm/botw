#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <gsys/gsysModel.h>
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModelAccessKey.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

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

class ASList;

// Placeholder: the AS runtime state (x1 of most element virtuals). Per-element records are 12-byte entries
// reached through the element index of the resource.
class Context {
public:
    struct Record {
        s8 _0;
        u8 _1;
        s8 _2;
        u8 _3;
        f32 _4;
        f32 _8;
    };

    struct Frame {
        sead::Buffer<Record> mRecords;
        s32 _10;
        u8 _14[0x20 - 0x14];
        sead::Buffer<u8> mIndexMap;  // element index -> record index
        res::AS* mAS;
    };
    static_assert(sizeof(Frame) == 0x38);

    // 0x7101258d1c: the record index of the element `index` (0 in the 'record 0' mode).
    u8 sub_7101258D1C(int index);
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

    /* 0x00 */ ASList* mList;
    /* 0x08 */ sead::SafeString mUnk8;
    /* 0x18 */ sead::SafeString mUnk18;  // PreASSelector::m40 returns its string
    /* 0x28 */ sead::SafeArray<Frame, 3> mFrames;
    /* 0xd0 */ Frame* _d0;  // the current frame
    /* 0xd8 */ Frame* _d8;  // overrides the ring when set
    /* 0xe0 */ f32 _e0;
    /* 0xe4 */ u8 _e4[0xf4 - 0xe4];
    /* 0xf4 */ u8 _f4;
    /* 0xf5 */ u8 _f5;
    /* 0xf6 */ u8 _f6[0x920 - 0xf6];
    /* 0x920 */ u8 _920;
    /* 0x921 */ u8 _921;
};

// Placeholder: per-element parameter block returned by Element::m25 (a range [_4, _8] and more floats).
struct ElementParams {
    u32 _0;
    f32 _4;
    f32 _8;
    f32 _c;
    f32 _10;
    f32 _14;
};

// Placeholder: the state passed down the tree by the update virtuals (m10, ...): `weight` is scaled by the
// blenders on their way down.
struct State {
    s32 _0;
    f32 weight;
};

class Element {
    SEAD_RTTI_BASE(Element)
public:
    Element();
    virtual ~Element() = default;

    // 0x71011653e8: the index of `resource` (this->m7() if there is none).
    int sub_71011653E8(const res::ASResource* resource);
    // 0x7101165408: the factory table field 0x18 of `resource` (-1 if there is none).
    int sub_7101165408(const res::ASResource* resource);
    // 0x710116554c: m11 followed by m37.
    int sub_710116554C(Context* ctx, State* state, const res::ASResource* resource);
    // 0x71011654e0: m37 followed by m14.
    void sub_71011654E0(Context* ctx, void* a2, State* a3, const res::ASResource* resource);
    // 0x7101165e60 / 0x7101165ebc (declaration only; used by SelectorBase::m35 / m36).
    void sub_7101165E60(Context* ctx, const res::ASResource* resource);
    void sub_7101165EBC(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
                        int index, const res::ASResource* resource);

    virtual f32 m4();
    virtual void m5();
    virtual int m6();
    virtual int m7();
    virtual bool m8();
    virtual bool m9();
    virtual bool m10(Context* ctx, State* state, const res::ASResource* resource) = 0;
    virtual void m11(Context* ctx, State* state, const res::ASResource* resource);
    virtual void m12(Context* ctx, State* state, const res::ASResource* resource);
    virtual void m13(Context* ctx, State* state, const res::ASResource* resource);
    virtual void m14(Context* ctx, void* a2, State* a3, const res::ASResource* resource);
    virtual void m15(Context* ctx, State* state, const res::ASResource* resource);
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
    virtual void m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
                     const res::ASResource* resource);
    virtual int m37(Context* ctx, State* state, const res::ASResource* resource);
};

class SelectorBase : public Element {
    SEAD_RTTI_OVERRIDE(SelectorBase, Element)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    SelectorBase();
    ~SelectorBase() override;

    void m11(Context* ctx, State* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* a2, State* a3, const res::ASResource* resource) override;
    void m15(Context* ctx, State* state, const res::ASResource* resource) override;
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
    void m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
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

    bool m32(Context* ctx, void* a2, void* a3, void* a4, void* a5, const res::ASResource* resource,
             f32 value) override;

    virtual void m38();
    virtual int m39(Context* ctx, u32 a2, const res::ASResource* resource);
};

class BoolSelector : public Selector {
    SEAD_RTTI_OVERRIDE(BoolSelector, Selector)
public:
    BoolSelector();

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

// Placeholder: selects the child whose value equals an integer parameter (ctor reads it from the owner).
class IntSelector : public Selector {
    SEAD_RTTI_OVERRIDE(IntSelector, Selector)
public:
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;

    /* 0x18 */ s32 _18;
};
KSYS_CHECK_SIZE_NX150(IntSelector, 0x20);

class ComboSelector : public Selector {
    SEAD_RTTI_OVERRIDE(ComboSelector, Selector)
public:
    ComboSelector();

    int m39(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class NodePosSelector : public Selector {
    SEAD_RTTI_OVERRIDE(NodePosSelector, Selector)
public:
    // Placeholder: 0x98-byte entry that starts with the bone key.
    struct Unk1 {
        gsys::BoneAccessKeyEx _0;
        u8 _38[0x98 - sizeof(gsys::BoneAccessKeyEx)];
    };

    NodePosSelector();
    ~NodePosSelector() override;

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
    ZEx00ExposureSelector();

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class GroundNormalSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(GroundNormalSelector, FloatSelector)
public:
    GroundNormalSelector();

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class GroundNormalSideSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(GroundNormalSideSelector, FloatSelector)
public:
    GroundNormalSideSelector();

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class AngleSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(AngleSelector, FloatSelector)
public:
    AngleSelector();

    virtual f32 m41();
    virtual f32 m42();
};

class RandomSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(RandomSelector, FloatSelector)
public:
    RandomSelector();

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class PreExclusionRandomSelector : public RandomSelector {
    SEAD_RTTI_OVERRIDE(PreExclusionRandomSelector, RandomSelector)
public:
    PreExclusionRandomSelector();
};

class SpeedSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(SpeedSelector, FloatSelector)
public:
    SpeedSelector();

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class YSpeedSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(YSpeedSelector, FloatSelector)
public:
    YSpeedSelector();

    f32 m40(Context* ctx, u32 a2, const res::ASResource* resource) override;
};

class EventFlagSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(EventFlagSelector, StringSelector)
public:
    EventFlagSelector();

    const char* m40(Context* ctx, const res::ASResource* resource) override;
    ~EventFlagSelector() override;

    sead::Buffer<void*> _18;
};

class PreASSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(PreASSelector, StringSelector)
public:
    PreASSelector();

    const char* m40(Context* ctx, const res::ASResource* resource) override;
};

class TimeSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(TimeSelector, StringSelector)
public:
    TimeSelector();

    const char* m40(Context* ctx, const res::ASResource* resource) override;
};

class WeatherSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(WeatherSelector, StringSelector)
public:
    WeatherSelector();

    const char* m40(Context* ctx, const res::ASResource* resource) override;
};

class Blender : public SelectorBase {
    SEAD_RTTI_OVERRIDE(Blender, SelectorBase)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m11(Context* ctx, State* state, const res::ASResource* resource) override;
    void m15(Context* ctx, State* state, const res::ASResource* resource) override;
    void m16(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m19(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m20(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m21(Context* ctx, const res::ASResource* resource, f32 value) override;
    void m22(Context* ctx, const res::ASResource* resource) override;
    f32 m26(Context* ctx, const res::ASResource* resource) override;
    bool m27(Context* ctx, const res::ASResource* resource) override;
    void m28(f32* a1, Context* ctx, const res::ASResource* resource) override;
    void m29(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m30(f32* a1, Context* ctx, const res::ASResource* resource) override;
    int m31(Context* ctx, const res::ASResource* resource) override;
    void m35(Context* ctx, const res::ASResource* resource) override;
    void m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
             const res::ASResource* resource) override;
    Blender();

    virtual f32 m38(Context* ctx, const res::ASResource* resource);
    virtual f32 m39(s32* a1, s32* a2, void* a3, void* a4);
};

class BoneBlender : public Blender {
    SEAD_RTTI_OVERRIDE(BoneBlender, Blender)
public:
    BoneBlender();

    f32 m39(s32* a1, s32* a2, void* a3, void* a4) override;
};

class ZEx00ExposureBlender : public Blender {
    SEAD_RTTI_OVERRIDE(ZEx00ExposureBlender, Blender)
public:
    ZEx00ExposureBlender();

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class GroundNormalBlender : public Blender {
    SEAD_RTTI_OVERRIDE(GroundNormalBlender, Blender)
public:
    GroundNormalBlender();

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class GroundNormalSideBlender : public Blender {
    SEAD_RTTI_OVERRIDE(GroundNormalSideBlender, Blender)
public:
    GroundNormalSideBlender();

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class AngleBlender : public Blender {
    SEAD_RTTI_OVERRIDE(AngleBlender, Blender)
public:
    AngleBlender();

    virtual f32 m40();
    virtual f32 m41();
};

class SpeedBlender : public Blender {
    SEAD_RTTI_OVERRIDE(SpeedBlender, Blender)
public:
    SpeedBlender();

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class WindVelocityBlender : public Blender {
    SEAD_RTTI_OVERRIDE(WindVelocityBlender, Blender)
public:
    WindVelocityBlender();

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class YSpeedBlender : public Blender {
    SEAD_RTTI_OVERRIDE(YSpeedBlender, Blender)
public:
    YSpeedBlender();

    f32 m38(Context* ctx, const res::ASResource* resource) override;
};

class SyncPlayContainer : public SelectorBase {
    SEAD_RTTI_OVERRIDE(SyncPlayContainer, SelectorBase)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    void m11(Context* ctx, State* state, const res::ASResource* resource) override;
    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    void m13(Context* ctx, State* state, const res::ASResource* resource) override;
    void m14(Context* ctx, void* a2, State* a3, const res::ASResource* resource) override;
    void m15(Context* ctx, State* state, const res::ASResource* resource) override;
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
    void m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name,
             const res::ASResource* resource) override;
    SyncPlayContainer();
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
    f32 m4() override;
    int m6() override;
    int m7() override;
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;

    /* 0x08 */ u16 _8;
    /* 0x0a */ s16 _a;
    /* 0x0c */ f32 _c;
};
KSYS_CHECK_SIZE_NX150(AnmAsset, 0x10);

class GraphicsAsset : public AnmAsset {
    SEAD_RTTI_OVERRIDE(GraphicsAsset, AnmAsset)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    int m31(Context* ctx, const res::ASResource* resource) override;

    /* 0x10 */ s16 _10;
    /* 0x12 */ s16 _12;
    /* 0x14 */ s32 _14;
};
KSYS_CHECK_SIZE_NX150(GraphicsAsset, 0x18);

class SkeltalAsset : public AnmAsset {
    SEAD_RTTI_OVERRIDE(SkeltalAsset, AnmAsset)
public:
    ~SkeltalAsset() override;

    void m12(Context* ctx, State* state, const res::ASResource* resource) override;
    int m30(f32* a1, Context* ctx, const res::ASResource* resource) override;

    /* 0x10 */ s16 _10;
    /* 0x12 */ s16 _12;
    /* 0x18 */ void* _18;
};
KSYS_CHECK_SIZE_NX150(SkeltalAsset, 0x20);

class ClearMatAnmAsset : public Asset {
    SEAD_RTTI_OVERRIDE(ClearMatAnmAsset, Asset)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    ClearMatAnmAsset();
};

}  // namespace ksys::as
