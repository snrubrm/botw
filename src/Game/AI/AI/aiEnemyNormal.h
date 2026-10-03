#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"

namespace ksys::act {
struct Unk_7100d78e50;
class Unk_71024dccf8;
struct Unk_71006e4478;
}

namespace uking::ai {

// Unnamed 0x68-byte heap object owned by EnemyNormal (_48). It has no out-of-line constructor:
// it is constructed inline by EnemyNormal::m65 (0x710039d8f0); placeholder name = that address.
struct Unk_710039D8F0 {
    s32 _0 = -1;
    void* _8 = nullptr;
    sead::Matrix34f _10 = sead::Matrix34f::ident;
    sead::Vector3f _40 = sead::Vector3f::zero;
    bool _4c = false;
    ksys::act::BaseProcLink _50;
    u32 _60 = 0;
};

// Awareness filter of EnemyNormal::m68 (vtable 0x71023e8fa8; m2 0x71003a40dc, D0 0x71003a4170).
class Unk_71023e8fa8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

class EnemyNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNormal, ksys::act::ai::Ai)
public:
    // Attack candidate filled by m49/m50 (stack object of the attack selection at 0x710039ef24:
    // initialised to {-1, 0, 0}); placeholder.
    struct Unk1 {
        s32 _0 = -1;
        s32 _4 = 0;
        u16 _8 = 0;
    };

    // Target candidate passed to m56-m58, m66-m69, m71/m72 (stack object of m34
    // 0x710039e394); placeholder.
    struct Unk2 {
        ksys::act::BaseProcLink* _0 = nullptr;
        sead::Matrix34f _8 = sead::Matrix34f::ident;
        sead::Vector3f _38 = sead::Vector3f::zero;
        u8 _44 = 0;

        // 0x710039e308: target = link (position and matrix of its actor).
        void sub_710039E308(ksys::act::BaseProcLink* link);
        // 0x71003a02a4: target = an awareness entry.
        void sub_71003A02A4(ksys::act::Unk_7100d78e50* entry);
    };

    // Result filled by m60/m61 and passed to m62/m63 ({type, flags}); placeholder.
    struct Unk3 {
        s32 _0;
        u8 _4;
    };

    explicit EnemyNormal(const InitArg& arg);
    ~EnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual bool m43();
    virtual bool m44(const sead::Vector3f& pos) { return true; }
    virtual bool m45(const sead::Vector3f& target_pos, ksys::act::BaseProcLink& target,
                     bool skip_own_pos);
    // `target` is non-const: it is passed to isNPCProfile / acquireActor.
    virtual bool m46(const sead::Vector3f& pos, ksys::act::BaseProcLink& target);
    virtual ksys::act::Unk_7100d78e50* m47(ksys::act::AwarenessInstance* awareness,
                                           ksys::act::Unk_71024dccf8* filter, s32 a3);
    virtual void m48(sead::Vector3f* pos);
    virtual void m49(Unk1* out, s32 idx);
    virtual void m50(Unk1* out, s32 idx);
    virtual bool m51();
    virtual s32 m52(s32 idx);
    virtual s32 m53() { return 9; }
    virtual bool m54();
    virtual bool m55();
    virtual bool m56(Unk2* out, Unk1* info) { return false; }
    virtual void m57(s32 type, Unk2* target);
    virtual void m58(s32 type, Unk2* target) {}
    virtual void m59();
    virtual void m60(Unk3* out);
    virtual void m61(Unk3* out);
    virtual void m62(Unk3* result);
    virtual bool m63(Unk3* result) { return false; }
    virtual void m64();
    virtual bool m65(sead::Heap* heap);
    virtual bool m66(Unk2* out, Unk1* info);
    virtual bool m67(Unk2* out, Unk1* info);
    virtual bool m68(Unk2* out, Unk1* info);
    virtual void m69(Unk2* target);
    virtual bool m70();
    virtual bool m71(Unk2* out, Unk1* info);
    virtual bool m72(Unk2* out, Unk1* info);
    virtual bool m73();

    bool sub_71003A19AC();
    // 0x710039f938: signals aware actors within SpreadDist (a1) / SpeadDist2 and, with a1, the
    // fortress when the actor is near its home position.
    void sub_710039F938(bool a1);
    // 0x710039e76c: clears _3ac bit 2 once the player is no longer checked by m46.
    void sub_710039E76C();
    // 0x71003a02e0 / 0x71003a0e38: switch to プレイヤー発見 / 不審者発見 for `target`.
    void sub_71003A02E0(Unk2* target);
    void sub_71003A0E38(Unk2* target);
    // 0x71003a0fd8 / 0x71003a1164 / 0x71003a1298 / 0x71003a13e4 / 0x71003a157c: switch to
    // 音気づき / 脅威感知 / 気配気づき / 行動中仲間発見 / 不調仲間発見 for `target`.
    void changeToNoticeSound(Unk2* target);
    void changeToSenseThreat(Unk2* target);
    void changeToNoticePresence(Unk2* target);
    void sub_71003A13E4(Unk2* target);
    void sub_71003A157C(Unk2* target);
    // 0x71003a3d0c: m58 + the state change for an attack candidate type.
    void sub_71003A3D0C(s32 type, Unk2* target);
    // 0x710039ef24: tries the attack candidates of m49 (mode 0) / m50 (mode 1).
    bool sub_710039EF24(s32 mode);
    // 0x710039f570 (not decompiled: iterates Enemy::_d70 entries with an inline iterator).
    void sub_710039F570(bool a1);
    // 0x710039eb7c / 0x710039ec4c / 0x710039ed94: per-frame updates called by calc_.
    void sub_710039EB7C();
    void sub_710039EC4C();
    void sub_710039ED94();
    // 0x71003a04e0: the first awareness entry accepted by `filter`.
    ksys::act::Unk_7100d78e50* sub_71003A04E0(bool a1, ksys::act::Unk_71024dccf8* filter, s32 a3,
                                              bool a4);
    // 0x710039db34
    bool sub_710039DB34(bool a1);
    // 0x710039fe20: an awareness entry of sensor 0 / 1 for `link` (filter 0x7102451740) or for the
    // Unk_71002dccbc members (filter 0x7102451560).
    ksys::act::Unk_7100d78e50* sub_710039FE20(ksys::act::BaseProcLink* link);
    // 0x71003a2be0: finds a target for an attack candidate (dispatches on info->_0).
    bool sub_71003A2BE0(Unk2* out, Unk1* info);
    // 0x71003a2e20
    bool sub_71003A2E20(Unk2* out, Unk1* info);
    // 0x71003a2f18
    bool sub_71003A2F18(Unk2* out);
    // 0x71003a31c0
    bool sub_71003A31C0(Unk2* out);
    // 0x710039dd0c: target = an Enemy target snapshot (Enemy::_e08); for a moved snapshot the
    // position is placed behind the own position along its velocity (or its Z axis).
    void sub_710039DD0C(Unk2* out, ksys::act::Unk_71006e4478* snapshot);
    // 0x710039e1d0
    bool sub_710039E1D0(Unk2* out, s32 type, Unk1* info);
    // 0x71003a0114: sub_71003A04E0 with a filter chosen by `type` / `flags`.
    ksys::act::Unk_7100d78e50* sub_71003A0114(bool a1, s32 type, s32 a3, u16* flags);
    // 0x71003a33c0: whether `target` is acceptable for the search type (1 / 2 / 3).
    bool sub_71003A33C0(s32 type, ksys::act::BaseProcLink* target, u16* flags);
    // 0x71003a234c: territory radius for `target` (NPC / player or non-living / other).
    f32 sub_71003A234C(ksys::act::BaseProcLink* target);
    // 0x71003a34d0
    bool sub_71003A34D0(Unk2* out, s32 type, Unk1* info);
    // 0x71003a361c
    bool sub_71003A361C(Unk2* out, s32 type, Unk1* info);
    // 0x710039faa4
    void sub_710039FAA4(const sead::Vector3f& pos);
protected:
    // aitree_variable at offset 0x38
    int* mPlayerSoundSealRefCount_a{};
    // aitree_variable at offset 0x40
    int* mSealNoPlayerAwnRequestCount_a{};
    Unk_710039D8F0* _48 = nullptr;
    ksys::act::BaseProcLink _50;
    sead::Vector3f _60;
    u32 _6c;
    // static_param at offset 0x70
    const int* mWeaponIdx_s{};
    // static_param at offset 0x78
    const int* mSoundLostTimer_s{};
    // static_param at offset 0x80
    const int* mNoActionReactTimeMin_s{};
    // static_param at offset 0x88
    const int* mNoActionReactTimeMax_s{};
    // static_param at offset 0x90
    const float* mTerritoryArea_s{};
    // static_param at offset 0x98
    const float* mNpcTerritoryArea_s{};
    // static_param at offset 0xa0
    const float* mNoPlayerTerritoryArea_s{};
    // static_param at offset 0xa8
    const float* mSpreadDist_s{};
    // static_param at offset 0xb0
    const float* mEnlargeAwnRatio_s{};
    // static_param at offset 0xb8
    const float* mNoticeTerrorLevel_s{};
    // static_param at offset 0xc0
    const float* mSpeadDist2_s{};
    // static_param at offset 0xc8
    const float* mHomePosRadius_s{};
    // static_param at offset 0xd0
    const float* mSubsTerritoryArea_s{};
    // static_param at offset 0xd8
    const float* mLostExtinguishFireDist_s{};
    // static_param at offset 0xe0
    const float* mShortRangeTerritoryArea_s{};
    // static_param at offset 0xe8
    const float* mCloseRangeTerritoryArea_s{};
    // static_param at offset 0xf0
    const float* mPressBreakObject_s{};
    // static_param at offset 0xf8
    const float* mTerritoryHeight_s{};
    // static_param at offset 0x100
    const bool* mIsMindDoubtTarget_s{};
    // static_param at offset 0x108
    sead::SafeString mFortressTag_s{};
    // map_unit_param at offset 0x118
    const float* mTerritoryArea_m{};
    f32 _120 = 0;
    s32 _124 = 0;
    s32 _128 = 0;
    bool _12c = false;
    Unk_710235abc8 _130{mActor, 0x8000006};
    Unk_7102450528 _188;
    Unk_71024507f8 _200;
    Unk_71023e8ff8 _290;
    Unk_71023e8fd0 _2e0{mActor, 0x80000c0};
    Unk_71023e9028 _308;
    ksys::Timer _358;
    f32 _364 = 0;
    f32 _368 = 0;
    f32 _36c = 0;
    f32 _370 = 0;
    u8 _374[0x390 - 0x374];
    ksys::act::BaseProcLink _390;
    sead::Vector3f _3a0;
    sead::BitFlag32 _3ac;
    const float* _3b0 = nullptr;
    f32 _3b8 = 0;
    u32 _3bc;
    ksys::act::BaseProcLink _3c0;
};
KSYS_CHECK_SIZE_NX150(EnemyNormal, 0x3d0);

}  // namespace uking::ai
