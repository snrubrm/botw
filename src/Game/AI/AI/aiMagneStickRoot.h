#pragma once

#include <math/seadBoundBox.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace ksys::map {
class Object;
}

namespace ksys::phys {
class RigidBody;
class ShapeCast;
}

namespace uking::ai {

// Placeholder name (vtable 0x7102407060; built on the stack by MagneStickRoot::sub_71004A0384): accepts the
// actors that have the tag `mTag`.
class Unk_7102407060 {
public:
    explicit Unk_7102407060(u32 tag) : mTag(tag) {}
    // 0x71004a1e84
    virtual bool m0(const ksys::act::ActorConstDataAccess& accessor) { return accessor.hasTag(mTag); }

    u32 mTag;
};

class MagneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MagneStickRoot, ksys::act::ai::Ai)
public:
    explicit MagneStickRoot(const InitArg& arg);
    ~MagneStickRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void loadParams_() override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual bool m40();
    virtual bool m41(const sead::Matrix34f* mtx, const sead::Vector3f* a, const sead::Vector3f* b);
    virtual f32 m42();
    virtual void m43(sead::Matrix34f* out, ksys::act::ActorLinkConstDataAccess* accessor);
    virtual bool m44(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                     const sead::BoundBox3f* bounds);
    virtual bool m45(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                     const sead::BoundBox3f* bounds);
    virtual bool m46(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                     const sead::BoundBox3f* bounds);
    virtual bool m47(ksys::act::ActorLinkConstDataAccess* accessor, const sead::Vector3f* pos,
                     const sead::BoundBox3f* bounds);
    virtual void m48(f32 radius, const sead::Matrix34f* mtx, const sead::Vector3f* a,
                     const sead::Vector3f* b);
    virtual void m49(sead::Vector3f* out, sead::Vector3f pos, const sead::Vector3f& target);
    virtual void m50() {}
    virtual void m51() {}

    bool sub_71004A1138(ksys::phys::ShapeCast* cast);
    // 0x71004a0174 (placeholder name): the first object linked to `proc`'s map object, from index
    // `*idx` on, whose actor exists and passes `filter`; stores its index in `*idx` (-1 if none).
    ksys::map::Object* sub_71004A0174(ksys::act::BaseProc* proc, s32* idx, Unk_7102407060* filter);
    // 0x71004a0384 (placeholder name): acquires in `out` the nearest linked actor with tag 0x7fe6e43f
    // that is closer than `_88`.
    void sub_71004A0384(ksys::act::ActorConstDataAccess* out);

protected:
    u32 _38 = 0;
    // static_param at offset 0x40
    const float* mDefaultConnectionDistance_s{};
    // static_param at offset 0x48
    const float* mCollideRadiusFactor_s{};
    // map_unit_param at offset 0x50
    const float* mCollideRadius_m{};
    // map_unit_param at offset 0x58
    const bool* mJoinSystemGroup_m{};
    // map_unit_param at offset 0x60
    const bool* mRegistFromBeginning_m{};
    // map_unit_param at offset 0x68
    const bool* mIgnoreObstacle_m{};
    // aitree_variable at offset 0x70
    bool* mIsTargetFixedAcceptor_a{};
    bool _78 = false;
    bool _79 = false;
    u32 _7c = 0;
    f32 _80 = 0.0f;
    f32 _84 = 0.0f;
    f32 _88 = sead::Mathf::maxNumber();
    ksys::Timer _8c;
    ksys::phys::RigidBody* _98 = nullptr;
};

}  // namespace uking::ai
