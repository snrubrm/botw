#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::map {
class Object;
}

namespace ksys::act {
class ActorLinkConstDataAccess;
}

namespace ksys::phys {
class Constraint;
class ContactPointInfo;
class RigidBody;
}  // namespace ksys::phys

namespace uking::ai {

// Complete one-slot table 24257F8; enter_ builds this 16-byte tag predicate on the stack.
class Unk_71024257f8 {
public:
    explicit Unk_71024257f8(u32 tag) : mTag(tag) {}
    virtual bool invoke(const ksys::act::ActorLinkConstDataAccess& accessor);

private:
    u32 mTag;
};
static_assert(sizeof(Unk_71024257f8) == 0x10);

// Declaration only: complete native lookup and enter_ identify actor, optional index and predicate.
// Address neighbors place this free helper in the AI namespace; the source owner is unknown.
ksys::map::Object* sub_71005AB22C(ksys::act::Actor* actor, s32* index,
                                 Unk_71024257f8* predicate);

class StoneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneStickRoot, ksys::act::ai::Ai)
public:
    explicit StoneStickRoot(const InitArg& arg);
    ~StoneStickRoot() override;
    bool hasUpdateForPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool updateForPreDelete() override;

protected:
    // Full enter_ and independent calc_ call these side-effect and position helpers.
    void sub_71005AB6B8();
    bool sub_71005AB83C();

    // static_param at offset 0x38
    const sead::Vector3f* mFixPoint_s{};
    bool _40 = false;
    void* _48 = nullptr;
    // Enter_ stores the tagged linked map object; both position and activation helpers use it.
    ksys::map::Object* _50 = nullptr;
    ksys::phys::Constraint* _58 = nullptr;
    ksys::phys::RigidBody* _60 = nullptr;
    ksys::phys::RigidBody* _68 = nullptr;
    ksys::phys::ContactPointInfo* _70 = nullptr;
    u32 _78 = 0;
};
KSYS_CHECK_SIZE_NX150(StoneStickRoot, 0x80);

}  // namespace uking::ai
