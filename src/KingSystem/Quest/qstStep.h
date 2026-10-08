#pragma once

#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::qst {

struct ActorData;
struct Indicator;

struct Step {
    struct ActLink {
        // The arguments of the constructor (0x71012b4124).
        struct Args {
            const char* name;
            const char* unique_name;
            act::BaseProc* proc;
            al::ByamlIter* iter_40;
            al::ByamlIter* iter_30;
            u32 _28;
            u8 _2c;
            u8 _2d;
        };

        ActLink(const Args& args, sead::Heap* heap);
        virtual ~ActLink();

        // 0x00000071012b4274: releases the linked actor (clears the quest-link state of its schedule)
        void sub_71012B4274();
        bool sub_71012B43D0(act::Actor* actor, const sead::SafeString& name) const;

        act::BaseProcLink link;
        u32 _18;
        u8 _1c = 0;
        u8 _1d = 0;
        const char* name;
        u32 name_hash = 0;
        al::ByamlIter* _30 = nullptr;
        sead::Heap* heap;
        al::ByamlIter* _40 = nullptr;
        const char* unique_name;
    };
    KSYS_CHECK_SIZE_NX150(ActLink, 0x50);

    Step(const u8** iter_data, sead::Heap* heap);
    virtual ~Step();

    bool sub_7100FDB89C(act::Actor* actor) const;
    bool sub_7100FDB538(act::Actor* actor, const sead::SafeString& name) const;
    bool sub_7100FDB794(act::Actor* actor) const;
    bool initActorData(u32 unused, sead::BufferedSafeString* out_message);
    bool initIndicator(u32 unused, sead::BufferedSafeString* out_message);
    bool sub_7100FDC2A4(al::ByamlIter* iter);

    sead::ObjArray<ActLink> links;
    u32 _28 = 0;
    gdt::FlagHandle dep_flag = gdt::InvalidHandle;
    const char* dep_flag_name = &sead::SafeString::cNullChar;
    u32 _38 = 3;
    u32 _3c = 0;
    bool attention_off = false;
    const char* message_name = &sead::SafeString::cNullChar;
    const char* name = &sead::SafeString::cNullChar;
    gdt::FlagHandle next_flag = gdt::InvalidHandle;
    const char* next_flag_name = &sead::SafeString::cNullChar;
    sead::Heap* heap = nullptr;
    ActorData* actor_data = nullptr;
    Indicator* indicator_info = nullptr;
    al::ByamlIter* iter = nullptr;
};
KSYS_CHECK_SIZE_NX150(Step, 0x88);

}  // namespace ksys::qst
