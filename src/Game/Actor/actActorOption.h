#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class ActorBind;
}

namespace ksys::act {
class ActorLinkConstDataAccess;
}

namespace uking::act {

// Name from the CSV (ActorOption::*; the namespace is a guess). Direct child of DynamicActor. Factory 0x71000001b4:
// new(0xbb0) + inlined ctor (`_1c0 = 1`). RTTI static: see data_symbols.
class ActorOption : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(ActorOption, DynamicActor)
public:
    explicit ActorOption(const CreateArg& arg);
    ~ActorOption() override = default;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // The object at _ba0 (0x60 bytes, created by prepareInit_ for actors with a damage manager). Placeholder name.
    struct LinkInfo {
        ksys::act::BaseProcLink link;
        sead::Matrix34f mtx = sead::Matrix34f::ident;
        sead::Vector3f _40 = sead::Vector3f::zero;
        sead::Vector3f _4c = sead::Vector3f::zero;
        u32 _58 = 0;
        bool _5c = false;
        bool _5d = false;
    };

    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

    // 0003F4 acquires source into B90 and updates the ModelBindInfo at BA8.
    // GiantEnemy3DB684 checks ActorOption RTTI before calling this method.
    void sub_71000003F4(ksys::act::Actor* source, const sead::SafeString& bone,
                       const sead::Vector3f& translation, const sead::Vector3f& rotation);

    bool shouldUnload(s32* a1) override;
    Actor* m31() override;
    Actor* m48() override;

    /* 0xb90 */ ksys::act::BaseProcLink _b90;
    /* 0xba0 */ LinkInfo* _ba0 = nullptr;
    /* 0xba8 */ ksys::act::ActorBind* _ba8 = nullptr;     // a ModelBindInfo (heap)
};
KSYS_CHECK_SIZE_NX150(ActorOption, 0xbb0);

// 0x7100000610 (placeholder name): the `_b90` link of the accessor's ActorOption, or the dummy link.
ksys::act::BaseProcLink& sub_7100000610(const ksys::act::ActorLinkConstDataAccess& accessor);

}  // namespace uking::act
