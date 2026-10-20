#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "Game/Actor/actObjBoardWoodTriangleUserTag.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include <container/seadObjArray.h>
#include "Game/Actor/aiUnk_7102357d20.h"

// The message senders of ObjBoardWoodTriangle01 (placeholder names from their vtables). They have the shared base
// destructor; their D0 only deletes and m2 returns the message payload (nullptr when there is none).
class Unk_71023aca50 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class Unk_71023aca78 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class Unk_71023acaa0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    u32 _18;
    u32 _1c = 0;
};

class Unk_71023acac8 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    u32 _18;
    u32 _1c = 0;
};

class Unk_71023acaf0 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    u32 _18;
    u32 _1c = 0;
};

class Unk_71023acb18 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    u32 _18;
    u32 _1c = 0;
};

class Unk_71023acb40 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return &_18; }

    u32 _18;
    u32 _1c = 0;
};

class Unk_71023acb68 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

namespace uking::action {

class ObjBoardWoodTriangle01 : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ObjBoardWoodTriangle01, ksys::act::ai::Action)
public:
    explicit ObjBoardWoodTriangle01(const InitArg& arg);
    ~ObjBoardWoodTriangle01() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
    // Full 0x710020d9b4 tracks links and updates this action's message senders.
    void sub_710020D9B4();

    sead::FixedObjArray<ksys::act::BaseProcLink, 4> _20;
    // A tracked link and its counter (sub_710020D9B4 adds entries with the counter at 0).
    struct LinkEntry {
        ksys::act::BaseProcLink link;
        s32 _10 = 0;
    };

    sead::FixedObjArray<LinkEntry, 16> _a0;
    Unk_7102362e80 _2c0{mActor, 0x80000cc};
    Unk_71023aca50 _2f0{mActor, 0x80000cd};
    Unk_71023aca78 _308{mActor, 0x80000ce};
    Unk_71023acaa0 _320{mActor, 0x80000cf};
    Unk_71023acaa0 _340{mActor, 0x80000cf};
    Unk_71023acac8 _360{mActor, 0x80000cb};
    Unk_71023acaf0 _380{mActor, 0x80000d0};
    Unk_71023acb18 _3a0{mActor, 0x80000d1};
    Unk_71023acb40 _3c0{mActor, 0x80000d2};
    Unk_71023acb68 _3e0{mActor, 0x3000019};
    f32 _3f8 = 1.0f;
    act::ObjBoardWoodTriangleUserTag _400{mActor};
    bool _460 = false;
};
KSYS_CHECK_SIZE_NX150(ObjBoardWoodTriangle01, 0x468);

}  // namespace uking::action
