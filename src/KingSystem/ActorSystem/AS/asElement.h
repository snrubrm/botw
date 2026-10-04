#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class ASResource;
}

// The runtime tree of the AS (animation sequence) system: one element per ASResource.
// Names are the CSV (IDA) names: `as::Element`, `as::SelectorBase`, `as::Blender`, ... Mostly sead-RTTI classes
// whose vtable slot numbers are the `mNN` placeholder names (slots 0-3 are the RTTI functions and the
// destructors). The tree classes are created from the resource by a factory; the CSV calls the first
// container base `SelectorBase` (it is shared by Selector, Blender, SequencePlayContainer and SyncPlayContainer).
// Classes are only declared as far as they are decompiled: undeclared overrides keep the base's entry in
// our vtable.
namespace ksys::as {

// Placeholder: the AS runtime state (x1 of most element virtuals). Per-element records are 12-byte entries
// reached through the element index of the resource.
class Context {
public:
    struct Record {
        s8 _0;
        u8 _1;
        u8 _2;
        u8 _3;
        f32 _4;
        f32 _8;
    };

    // 0x7101258cd4: the record of the element `index` (record 0 if the context is not in the used state).
    Record* sub_7101258CD4(int index);
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

    virtual f32 m4();
    virtual void m5();
    virtual int m6();
    virtual int m7();
    virtual bool m8();
    virtual bool m9();
    virtual bool m10(Context* ctx, State* state, const res::ASResource* resource) = 0;
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual f32 m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual bool m24();
    virtual void* m25();
    virtual f32 m26(Context* ctx, const res::ASResource* resource);
    virtual int m27();
    virtual void m28();
    virtual void m29();
    virtual int m30();
    virtual int m31();
    virtual int m32();
    virtual int m33();
    virtual void m34();
    virtual void m35();
    virtual void m36(Context* ctx, sead::BufferedSafeString* out, const sead::SafeString& name);
    virtual int m37();
};

class SelectorBase : public Element {
    SEAD_RTTI_OVERRIDE(SelectorBase, Element)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    SelectorBase();
    ~SelectorBase() override;

    // 0x71013031fc: the resource of the child `index` (null if `resource` has no children).
    const res::ASResource* sub_71013031FC(const res::ASResource* resource, int index) const;

    sead::Buffer<Element*> mChildren;
};
KSYS_CHECK_SIZE_NX150(SelectorBase, 0x18);

class Selector : public SelectorBase {
    SEAD_RTTI_OVERRIDE(Selector, SelectorBase)
public:
    Selector();
};

class BoolSelector : public Selector {
    SEAD_RTTI_OVERRIDE(BoolSelector, Selector)
public:
    BoolSelector();
};

class ComboSelector : public Selector {
    SEAD_RTTI_OVERRIDE(ComboSelector, Selector)
public:
    ComboSelector();
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
};

class StringSelector : public Selector {
    SEAD_RTTI_OVERRIDE(StringSelector, Selector)
public:
    StringSelector();
};

class ZEx00ExposureSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(ZEx00ExposureSelector, FloatSelector)
public:
    ZEx00ExposureSelector();
};

class GroundNormalSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(GroundNormalSelector, FloatSelector)
public:
    GroundNormalSelector();
};

class GroundNormalSideSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(GroundNormalSideSelector, FloatSelector)
public:
    GroundNormalSideSelector();
};

class AngleSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(AngleSelector, FloatSelector)
public:
    AngleSelector();
};

class RandomSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(RandomSelector, FloatSelector)
public:
    RandomSelector();
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
};

class YSpeedSelector : public FloatSelector {
    SEAD_RTTI_OVERRIDE(YSpeedSelector, FloatSelector)
public:
    YSpeedSelector();
};

class EventFlagSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(EventFlagSelector, StringSelector)
public:
    EventFlagSelector();
    ~EventFlagSelector() override;

    sead::Buffer<void*> _18;
};

class PreASSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(PreASSelector, StringSelector)
public:
    PreASSelector();
};

class TimeSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(TimeSelector, StringSelector)
public:
    TimeSelector();
};

class WeatherSelector : public StringSelector {
    SEAD_RTTI_OVERRIDE(WeatherSelector, StringSelector)
public:
    WeatherSelector();
};

class Blender : public SelectorBase {
    SEAD_RTTI_OVERRIDE(Blender, SelectorBase)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    Blender();
};

class BoneBlender : public Blender {
    SEAD_RTTI_OVERRIDE(BoneBlender, Blender)
public:
    BoneBlender();
};

class ZEx00ExposureBlender : public Blender {
    SEAD_RTTI_OVERRIDE(ZEx00ExposureBlender, Blender)
public:
    ZEx00ExposureBlender();
};

class GroundNormalBlender : public Blender {
    SEAD_RTTI_OVERRIDE(GroundNormalBlender, Blender)
public:
    GroundNormalBlender();
};

class GroundNormalSideBlender : public Blender {
    SEAD_RTTI_OVERRIDE(GroundNormalSideBlender, Blender)
public:
    GroundNormalSideBlender();
};

class AngleBlender : public Blender {
    SEAD_RTTI_OVERRIDE(AngleBlender, Blender)
public:
    AngleBlender();
};

class SpeedBlender : public Blender {
    SEAD_RTTI_OVERRIDE(SpeedBlender, Blender)
public:
    SpeedBlender();
};

class WindVelocityBlender : public Blender {
    SEAD_RTTI_OVERRIDE(WindVelocityBlender, Blender)
public:
    WindVelocityBlender();
};

class YSpeedBlender : public Blender {
    SEAD_RTTI_OVERRIDE(YSpeedBlender, Blender)
public:
    YSpeedBlender();
};

class SyncPlayContainer : public SelectorBase {
    SEAD_RTTI_OVERRIDE(SyncPlayContainer, SelectorBase)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    SyncPlayContainer();
};

class Asset : public Element {
    SEAD_RTTI_OVERRIDE(Asset, Element)
public:
    Asset();
};

class ClearMatAnmAsset : public Asset {
    SEAD_RTTI_OVERRIDE(ClearMatAnmAsset, Asset)
public:
    bool m10(Context* ctx, State* state, const res::ASResource* resource) override;
    ClearMatAnmAsset();
};

}  // namespace ksys::as
