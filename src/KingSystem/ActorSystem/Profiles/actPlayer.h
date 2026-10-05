#pragma once

#include <math/seadVector.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/Awareness/actAITerror.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/MathUtil.h"

namespace ksys::phys {
class Constraint;
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

// The player actor (CSV prefix Player::; vtable 0x710246ae38, 387 slots; factory 0x85cce0
// `new(0x2ec0)`, ctor 0x85cd24). RTTI static: GOT 0x710257a530.
// Slots 360-385 are new primary slots for Player's overrides of ksys::act::PlayerLink virtuals
// that PlayerBase does not override (in PlayerLink declaration order of the overriders below)
// plus the new virtuals m362, m363 and m386. Keep the order of that block.
// TODO: incomplete.
class Player : public PlayerBase {
    SEAD_RTTI_OVERRIDE(Player, PlayerBase)
public:
    // CSV Player::RideInfo (ctor 0x852aa0, vtable 0x710246ad80): a HorseRideInfo subclass with an
    // intermediate base (vtable 0x710244eaa0) in between; embedded at +0x26b0. TODO: incomplete.
    class RideInfo : public uking::act::Unk_710244eaa0 {
        SEAD_RTTI_OVERRIDE(RideInfo, uking::act::Unk_710244eaa0)
    public:
        explicit RideInfo(Actor* actor);
        ~RideInfo() override;

        bool m7() override { return Unk_710244eaa0::m7(); }
        void m8() override;

        // 0x852b90 (CSV init): creates the fixed constraint (_2d8).
        void init(sead::Heap* heap);
        // 0x852c28 (CSV x_0): destroys the constraint.
        void x_0();

        /* 0x1f0 */ BaseProcLink _1f0;
        /* 0x200 */ ModelBindInfo _200;
        /* 0x2a0 */ gsys::BoneAccessKeyEx _2a0;
        /* 0x2d8 */ phys::Constraint* _2d8 = nullptr;
        /* 0x2e0 */ phys::RigidBody* _2e0 = nullptr;
        /* 0x2e8 */ u32 _2e8 = 0;
        /* 0x2ec */ f32 _2ec = 0.0f;
        /* 0x2f0 */ bool _2f0 = false;
    };
    KSYS_CHECK_SIZE_NX150(RideInfo, 0x2f8);

    f32 getArmorChargeAttackAddLevel();
    f32 sub_7100885630(s32 level);

    explicit Player(const CreateArg& arg);
    // CSV Player::construct: the actor factory function.
    static BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~Player() override;

    // Overrides of PlayerBase (and inherited) slots.
    /*   4 */ InitResult init_() override;
    /*   7 */ PreDeletePrepareResult prepareForPreDelete_() override;
    /*   8 */ bool startPreparingForPreDelete_() override;
    /*  18 */ bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    /*  19 */ void onPreDeleteStart_(PrepareArg&) override {}
    /*  20 */ void preDelete2_(const PreDeleteArg& arg) override;
    /*  30 */ s32 getMaxLife() override { return _1868; }
    /*  37 */ f32 getGuardableAngle() override;
    /*  41 */ void m41(sead::Matrix34f* mtx) override;
    /*  42 */ void m42(const sead::Matrix34f& mtx) override;
    /*  47 */ bool m47() override;
    /*  50 */ bool m50() override;
    /*  62 */ bool shouldUnload(s32* a1) override { return false; }
    /*  63 */ void m63() override;
    /*  64 */ void initMaybe() override;
    /*  69 */ void calcMaybe() override;
    /*  70 */ void m70() override;
    /*  71 */ void updatePositionMaybe() override;
    /*  74 */ void m74() override;
    /*  76 */ void m76(VFR::ScopedDeltaSetter* setter) override;
    /*  77 */ void m77(VFR::ScopedDeltaSetter* setter) override;
    /*  78 */ void afterModelMatrixUpdate() override;
    /*  81 */ bool m81(const Message& message) override;
    /*  83 */ bool m83() override;
    /*  84 */ void updateMtxFromPhysics() override;
    /*  85 */ void setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) override;
    /*  88 */ void m88() override;
    /*  89 */ void m89() override;
    /*  90 */ void m90() override;
    /*  99 */ PlayerArmors* getArmors() override;
    /* 109 */ int m109() override { return 0x30; }
    /* 114 */ void m114() override;
    /* 115 */ void m115() override;
    /* 116 */ void m116() override;
    /* 117 */ void m117(Unk117* arg) override;
    /* 119 */ void* m119() override;
    /* 129 */ PlayerLink* m129() override;
    /* 130 */ uking::act::HorseRideInfo* getPlayerRideInfo() override;
    /* 145 */ void m145() override {}
    /* 146 */ bool m146() override;
    /* 147 */ void m147() override;
    /* 148 */ f32 m148() override { return _20d0; }
    /* 151 */ bool m151(u16 bit) override;
    /* 157 */ bool m157(sead::Heap* heap) override;
    /* 158 */ void m158() override;
    /* 159 */ uking::act::Unk_71025ae680* m159() override;
    /* 160 */ void m160() override;
    /* 161 */ void m161() override;
    /* 165 */ bool m165(sead::BufferedSafeString* out) override;
    /* 166 */ bool isGuard() override { return _c40.isOnBit(4); }
    /* 167 */ bool isGuardJust() override;
    /* 176 */ void m176() override;
    /* 180 */ bool m180() override;
    /* 181 */ bool m181() override;
    /* 182 */ bool m182() override;
    /* 183 */ bool m183() override;
    /* 198 */ bool isNoShieldDamageFloor() override;
    /* 203 */ bool m203() override { return x_21(); }
    /* 213 */ bool isMasterSwordEquipped() override { return isMasterSwordEquipped_(); }
    /* 214 */ bool m214() override { return _1ca4 == 6; }
    /* 215 */ bool m215() override { return _207e; }
    /* 216 */ bool armorEffectHasWakeWindEffect() override { return _2081; }
    /* 217 */ bool m217() override;
    /* 218 */ bool m218() override;
    /* 219 */ bool m219() override { return _2550._8.isOnBit(9); }
    /* 224 */ bool m224() override { return _1f84 == 3 || _1f84 == 4; }
    /* 225 */ bool m225() override;
    /* 226 */ bool m226() override;
    /* 227 */ bool m227() override;
    /* 228 */ void m228(bool a1) override;
    /* 229 */ void m229() override;
    /* 230 */ bool m230() override;
    /* 231 */ f32 m231() override;
    /* 232 */ f32 getAncientAttackRate() override;
    /* 233 */ f32 m233(int) override;
    /* 234 */ s32 m234() override;
    /* 235 */ f32 m235() override;
    /* 236 */ f32 getBoneAttackRate() override;
    /* 242 */ bool m242() override { return _c50.isOnBit(6); }
    /* 243 */ bool m243() override;
    /* 244 */ const sead::Vector3f* m244() override;
    /* 245 */ const sead::Vector3f* m245() override;
    /* 246 */ const sead::Vector3f* getPosCopyMagnesis() override;
    /* 247 */ const sead::Vector3f* m247() override { return &_22a8; }
    /* 248 */ f32 m248() override;
    /* 249 */ bool m249() override { return false; }
    /* 250 */ const sead::Vector3f* m250() override { return &sead::Vector3f::zero; }
    /* 251 */ const sead::Vector3f* m251() override { return &sead::Vector3f::zero; }
    /* 252 */ const sead::Vector3f* m252() override { return &sead::Vector3f::zero; }
    /* 253 */ const sead::Vector3f* m253() override { return &sead::Vector3f::zero; }
    /* 254 */ bool m254() override { return false; }
    /* 255 */ const sead::Vector3f* m255() override { return &_22e8; }
    /* 256 */ bool m256() override;
    /* 257 */ bool m257() override;
    /* 258 */ bool m258(f32* out) override;
    /* 261 */ bool m261(f32* out) override;
    /* 263 */ Unk_71024ef4e8* getAttachedTargetActor2() override;
    /* 264 */ Unk_71024ef4e8* getAttachedTargetActor() override;
    /* 265 */ const sead::Vector3f* m265() override { return &_230c; }
    /* 267 */ void m267() override;
    /* 268 */ bool m268() override;
    /* 269 */ bool m269() override;
    /* 270 */ bool m270() override;
    /* 272 */ void getArmorPartName(u8 idx, sead::BufferedSafeString* out) override;
    /* 273 */ uking::act::Weapon* m273() override;
    /* 274 */ uking::act::Weapon* m274() override;
    /* 275 */ uking::act::Weapon* m275() override;
    /* 276 */ Actor* m276(int idx) override;
    /* 277 */ void m277(ActorConstDataAccess* accessor, int idx) override;
    /* 278 */ s32 m278(u8 idx) override;
    /* 279 */ s32 getArmorDyeStuff() override;
    /* 280 */ bool m280() override;
    /* 281 */ bool isEquipedDyedArmor() override;
    /* 282 */ void getArmorSeriesType(sead::BufferedSafeString* out) override;
    /* 283 */ void getEnemyTeam(sead::BufferedSafeString* out) override;
    /* 284 */ bool ArmorSeriesTypeStuff() override;
    /* 285 */ bool armorSeriesStuff(u8 idx, const sead::SafeString& series) override;
    /* 286 */ void getMaskType(sead::BufferedSafeString* out) override;
    /* 287 */ bool m287() override;
    /* 288 */ s32 m288() override;
    /* 289 */ s32 m289() override;
    /* 290 */ bool m290() override;
    /* 291 */ s32 m291() override;
    /* 295 */ bool m295() override;
    /* 296 */ s32 m296() override;
    /* 297 */ s32 m297() override { return _1f8c; }
    /* 298 */ s32 m298(int) override;
    /* 300 */ f32 m300() override { return _2074; }
    /* 301 */ f32 m301() override;
    /* 302 */ bool m302() override { return _1f88 == 3; }
    /* 303 */ bool m303() override;
    /* 304 */ bool m304() override;
    /* 305 */ f32 m305() override;
    /* 306 */ bool m306() override { return x_44(); }
    /* 309 */ void m309(f32) override;
    /* 310 */ void m310(f32) override;
    /* 311 */ void m311() override;
    /* 312 */ gsys::BoneAccessKey m312(int idx) override;
    /* 318 */ void m318(sead::Matrix34f* out) override;
    /* 319 */ f32 m319() override { return _2094; }
    /* 320 */ f32 m320() override { return getStatusEffectSpeed(); }
    /* 321 */ s32 m321() override { return _1ffc; }
    /* 322 */ s32 m322() override { return _2000; }
    /* 323 */ void m323() override;
    /* 324 */ void m324(int value) override { _1ffc = value; }
    /* 325 */ void m325(f32 value) override { _2000 = value; }
    /* 326 */ f32 m326() override { return _2084; }
    /* 327 */ f32 m327() override { return _2088; }
    /* 328 */ bool m328() override;
    /* 329 */ bool isRevivalFairyActive(ActorConstDataAccess* accessor) override;
    /* 330 */ bool isZoraHeroActive(ActorConstDataAccess* accessor) override;
    /* 331 */ bool canUseRevaliGale() override;
    /* 332 */ bool canUseDarukProtection() override;
    /* 333 */ bool canUseUrbosaFury() override;
    /* 334 */ bool canUseMiphaGrace() override;
    /* 335 */ f32 getRevaliGaleTime() override { return _1df4; }
    /* 336 */ f32 m336() override { return _1e00; }
    /* 337 */ f32 m337() override { return _1e0c; }
    /* 338 */ f32 m338() override { return _1e18; }
    /* 339 */ f32 m339() override { return -_1dfc; }
    /* 340 */ f32 m340() override { return -_1e08; }
    /* 341 */ f32 m341() override { return -_1e14; }
    /* 342 */ f32 m342() override { return -_1e20; }
    /* 343 */ s32 m343() override { return _1cc8; }
    /* 344 */ s32 m344() override { return _1cd0; }
    /* 345 */ s32 m345() override { return _1ccc; }
    /* 346 */ void updateSupportTimerRates() override;
    /* 347 */ bool isDarukProtectionEnabled() override;
    /* 348 */ bool m348() override { return _1cbe != 0; }
    /* 350 */ f32 getNoDeathDamage() override;
    /* 351 */ BaseProcLink& getSpAttackTarget() override { return _2c98; }
    /* 352 */ bool m352(sead::Vector3f* out) override;
    /* 353 */ bool m353() override;
    /* 354 */ f32 getAtkMultiplier() override;

    // New primary slots 360-386 (order matters).
    /* 360 */ f32 m360() override { return _20f0; }
    /* 361 */ bool hasFairy() override;
    /* 362 */ virtual void m362();
    /* 363 */ virtual void m363();
    /* 364 */ f32 m364() override;
    /* 365 */ bool m365() override;
    /* 366 */ void m366() override;
    /* 367 */ void showCannotGoAnyFarther() override;
    /* 368 */ void showCannotGoAnyFarther2() override;
    /* 369 */ void m369(int value) override {
        _c50.setBit(14);
        _e5c = value;
    }
    /* 370 */ void m370(f32 value) override { x_34(value, false); }
    /* 371 */ void m371(f32 value) override { decreaseStaminaForActionMaybe(value); }
    /* 372 */ void m372() override;
    /* 373 */ bool m373() override;
    /* 374 */ bool m374() override;
    /* 375 */ bool m375() override { return stillAlive(); }
    /* 376 */ bool m376() override;
    /* 377 */ void m377() override;
    /* 378 */ s32 m378() override;
    /* 379 */ void m379() override;
    /* 380 */ void m380() override;
    /* 381 */ void m381() override;
    /* 382 */ Actor* m382() override;
    /* 383 */ bool m383() override { return _c50.isOnBit(18); }
    /* 384 */ int m384() override { return _1cd4; }
    /* 385 */ int m385() override { return _1cd8; }
    /* 386 */ virtual void m386() {}

    // Non-virtual member functions (CSV names; placeholder names x_NN are the CSV's).
    void x_0(const char* animation);  // 0x856950
    // Parameter names are unknown; the order of float vs. integer parameters is a guess.
    void switchToAnimSequenceMaybe(const char* name, bool a2, f32 a3);  // 0x855608
    void x_23(const char* name, bool a2, f32 a3);                       // 0x85588c
    void x_18(bool a1);                                                 // 0x855a6c
    // 0x7100855bb4 (declared only; PlayerKokkoGlide::enter_ with "ParashawlGlide").
    void sub_7100855BB4(const char* name, bool a2, f32 a3);
    // All 33 callers pass -1.0f in s0, which x_19 does not use.
    void x_19(f32 a1);                                                  // 0x855d40
    // All callers pass -1.0f in s0 (unused, like x_19).
    void x_24(f32 a1);                                                  // 0x855e24
    void x_25();                                                        // 0x8551fc
    // A 4-byte angle index (sead::Mathf::atan2Idx result) returned through x8, so not trivially
    // copyable in the original; the same type as 0x710092dba4's result (ksys::util placeholder).
    using Unk1 = util::Unk_7101EC6BAC;
    Unk1 x_5();                                                         // 0x85ed1c
    // 0x8679fc: takes an angle index (the stack temporary is at sp+8: a struct in the original).
    void x_53(const Unk1& angle);
    // 0x7100877bd8: stores the anim-driven speed (ASList::sub_710115D2D4) in _20bc / _20c0 and its
    // direction relative to x_5() in _1c68 (~18 player actions call it).
    void sub_7100877BD8();
    f32 x_39();                                                         // 0x867cd4
    void someFloatCalc(f32 a1, const sead::Vector3f& a2);               // 0x868990
    // 0x71008697e4: clears _20bc / _20c0 and the character controller velocity.
    void sub_71008697E4();
    f32 getStatusEffectSpeed();                                         // 0x869a8c
    f32 getStatusEffectMovingSpeed(s32 level);
    f32 getStatusEffectSwimingSpeed(s32 level);
    f32 getStatusEffectClimbingSpeed(s32 level);
    void updateResistHotVal();
    void updateResistColdVal();
    void updateStatusEffectAttackUp();
    void m69_x_1();
    void showRuntimeTipForColdHotStatusEffects();
    void actionCommon();                                                // 0x86aa94
    // 0x7100877f00 (declared only): anim-driven movement helper used by PlayerSitEnd::calc_ (takes the
    // direction to move in; 0 for none).
    void sub_7100877F00(const sead::Vector3f& dir);
    // Declared only (placeholder member functions of the player; all take the player as `this`):
    void sub_710086800C(f32 a1);       // 0x710086800c
    void sub_71008824AC(bool a1);      // 0x71008824ac
    void sub_71008893B8(bool a1);      // 0x71008893b8
    void sub_71008931C4();             // 0x71008931c4
    void sub_71008B5B8();              // 0x71008b5b8
    // 0x710086952c (declared only; lane3 s22): finds the body "..." of the physics set and passes its rigid body to InstanceSet 0xfbd918.
    void sub_710086952C();
    // 0x7100887ac4 (lane3 s22): whether the AS of slot 1 / bank 1 is "GrabThrow".
    bool sub_7100887AC4();
    // 0x71008550e4 (declared only; lane3 s22; 280 B).
    void sub_71008550E4();
    // 0x710086faac: empty (the original keeps an out-of-line copy).
    void sub_710086FAAC();
    // 0x710084ad5c (declared only; lane3 s22): adds `value` (scaled) to one of the three slots at +0xe7c (stamina recovery).
    void sub_710084AD5C(f32 value, bool a2);
    void x_37();  // 0x71008efa0
    void sub_7100856A7C();             // 0x7100856a7c (declared only)
    // 0x710086fab0 (CSV nullsub_2601): empty.
    void nullsub_2601();
    // Targets of the slot thunks m256 / m257 / m268 / m270 / m287 / m295 / m296 / m298 (declared only;
    // placeholder names).
    bool x_32();  // 0x88c1ec
    bool sub_7100881EDC();
    bool isASItemBombReadyOrStart();
    bool sub_710088873C();
    bool sub_71008921A8();
    // 0x710086d5b8 (declared only; unnamed in the CSV, 1.3 KB): called by PlayerHellNoFade::enter_.
    void sub_710086D5B8();
    bool sub_7100892724();
    s32 sub_7100892824();
    s32 sub_71008923B0(int a1);
    // 0x7100857014 (declared only): turns the player towards the angle index `*target` (speed -1: 0.5; the
    // two limits default to 0x20000000 / 0x200000 for -1); true when the turn is finished.
    // 0x71084ba90 (declaration only; placeholder name): called with the warp effect ratio by
    // PlayerWarpEffectValueSetter.
    void sub_710084BA90(f32 value);
    // 0x710085ecf4 (declaration only; placeholder name): `if (auto* cc = getCharacterController())
    // cc->sub_7100F5EECC(<constant>)`; called by PlayerAction::enter_ outside events.
    void sub_710085ECF4();
    bool sub_7100857014(f32 speed, Unk1* target, int limit_a, int limit_b);
    // 0x710086843c: forwards to sub_7100857014 (out of line in another TU in the original; ~7 Player actions).
    bool sub_710086843C(f32 speed, Unk1* target, int limit_a, int limit_b);
    // 0x7100859edc (declared only): sets the look-at / turn target state (_2d30 = a1, _2d34 = mode, _2d48 =
    // link; mode 1 with a link that can be acquired copies `*pos` / `*pos2` to _2d38 / _2d58 and returns true).
    bool sub_7100859EDC(bool a1, int mode, const sead::Vector3f* pos, BaseProcLink* link,
                        const sead::Vector3f* pos2);
    // 0x7100859fc0 (declared only; CSV ai::action::PlayerLookAtObject::x): sets _2d30 = a1 and, when a1 and
    // _2d30 was not set, _2d34 = (the first resident link has a proc ? 4 : 0); resets _2d48 and copies the
    // zero vector to _2d38 / _2d58. Always true.
    bool sub_7100859FC0(bool a1);
    // 0x7100868d7c (declared only): turns the player towards `dir` (XZ) with the given speed factor.
    void sub_7100868D7C(f32 speed, const sead::Vector3f* dir);
    // 0x7100888294 (declared only): true when the player's _d30 equipment type is checked against type 1 (used
    // by PlayerCutFall / PlayerSpAttack leave_ before x_7).
    bool sub_7100888294();
    // 0x7100888278: `if (_c40 & 0x10) { _c40 &= ~0x10; x_18(true); }` (declared only).
    void sub_7100888278();
    // 0x710088a854 (declared only): sets a flag byte at +0x30 of the object of vslot 0x310, clears _c40 bit 3,
    // calls sub_7100888278() and a singleton method.
    void sub_710088A854();
    // 0x7100869814 (declared only): classifies the turn from angle `a` towards `b` (0-3; 2 = negative direction);
    // the callers pass `mask & diff` and `mask & 0x20000000`.
    u8 sub_7100869814(Unk1 a, Unk1 b);
    bool isSurfingOnGround() const;                                     // 0x87f290
    // 0x7e70f4 (CSV): an inline function, emitted out of line in the PlayerDemoAirWait TU.
    bool isShootingBow() const {
        return getASList()->x_1(1, 1) == "BowShoot" || getASList()->x_1(1, 1) == "SquatBowShoot" ||
               getASList()->x_1(0, 0) == "WallBowShootL" ||
               getASList()->x_1(0, 0) == "WallBowShootR";
    }
    bool stillAlive();                                                  // 0x884510
    bool x_44();                                                        // 0x885090
    // 0x710086ca68 (placeholder name; static, no arguments): true while the E3 demo's RidDemo state
    // is active, else the IsGet_PlayerStole2 flag.
    static bool sub_710086CA68();
    // 0x7100881104 (declared only): clears _c40/_c44/_c48/_c4c bits (_c44 &= 0xfffbffe5, _c40 &= ~(1 << 22),
    // _c4c &= ~(1 << 12), _c48 &= ~(1 << 11)) and resets _1e9c (u64), _1ea4 (-1.0f) and _20b4.
    void sub_7100881104();
    void x_34(f32 value, bool a2);                                      // 0x885bb4
    void decreaseStaminaForActionMaybe(f32 value);                      // 0x885bd0
    f32 x_67();                                                         // 0x86cad4 (not decompiled)
    bool x_21();                                                        // 0x887a20
    bool isMasterSwordEquipped_();                                      // 0x86d024
    bool x_35();                                                        // 0x8886f4
    void x_7();                                                         // 0x88a048
    // All ~45 callers pass (0, 0); x_8 does not read them (types a guess).
    void x_8(bool a1, bool a2);                                         // 0x88a8a8
    void x_33();                                                        // 0x88c900
    // 0x874514: acquires links to the resident actors (ResidentActorMgr::getActorByName).
    void initResidentActors();
    // World ray casts (uking::Unk_71024739d0) from `start` to `end`; on a hit the position and the
    // normal are written to the non-null outputs.
    // 0x87f168: ground layers; `wall` NoClimb rejects the wall codes NoClimb and
    // NoDashUpAndNoClimb, NoDashUpAndNoClimb rejects itself, any other value requires that code.
    bool sub_710087F168(const sead::Vector3f& start, const sead::Vector3f& end, phys::WallCode wall,
                        sead::Vector3f* hit_pos, sead::Vector3f* hit_normal);
    // 0x87f360: sub_710072E928(start, end, hit_pos, hit_normal, nullptr, 0).
    bool sub_710087F360(const sead::Vector3f& start, const sead::Vector3f& end,
                        sead::Vector3f* hit_pos, sead::Vector3f* hit_normal);
    // 0x87f43c: ground and water layers.
    bool sub_710087F43C(const sead::Vector3f& start, const sead::Vector3f& end,
                        sead::Vector3f* hit_pos, sead::Vector3f* hit_normal);
    // 0x87f4f8: water only (not Water_Ice / Water_Poison).
    bool sub_710087F4F8(const sead::Vector3f& start, const sead::Vector3f& end,
                        sead::Vector3f* hit_pos, sead::Vector3f* hit_normal);
    // 0x88d564: called when _d30 differs from getEquipmentTypeName(type) (PlayerStepAttack: type 1).
    void x_38(u32 type);
    // 0x8922c4 (CSV playerWeapons_return0, ~45 player AI callers): a weapon slot index (always 0).
    s32 playerWeapons_return0();
    // 0x8883b0 / 0x881ff8 (CSV playerWeapons_return1 / _return2): weapon slot indices 1 / 2.
    s32 playerWeapons_return1();
    // 0x71008859ec (declared only; unnamed in the CSV): an armor-dependent integer (base _2038 + _201c, +2 with the
    // PlayerArmors flag 0x2, clamped to 3), read by PlayerForkDropWeaponWithSpeed::calc_.
    s32 sub_71008859EC();
    s32 playerWeapons_return2();
    // 0x7100892100: sets the character controller velocity towards `pos` (from _1770, scaled by
    // 30 / _20f0) and its matrix to _1b18 (ladder actions).
    void sub_7100892100(const sead::Vector3f& pos);
    void x_40();                                                        // 0x8922cc
    // 0x710088f57c (CSV name): syncs the status effect flags.
    void syncStatusEffectFlags(bool a);
    bool x_49();                                                        // 0x849424
    bool x_17();                                                        // 0x892bf0
    void x_16();                                                        // 0x892e18

    /* 0x17f0 */ u8 _17f0;  // cleared by PlayerDrown::enter_
    /* 0x17f1 */ bool _17f1;  // set by PlayerHorseGetOff::enter_
    /* 0x17f2 */ bool _17f2;  // cleared by PlayerAtnWait::enter_
    /* 0x17f3 */ u8 _17f3[0x17f8 - 0x17f3];
    /* 0x17f8 */ s32 _17f8;  // state copied from _1cb0 (PlayerDisplayWait::enter_)
    /* 0x17fc */ u8 _17fc[0x1800 - 0x17fc];
    /* 0x1800 */ f32 _1800;  // copy of _1770.y (PlayerSuperJump::enter_)
    /* 0x1804 */ f32 _1804;  // zeroed by PlayerGlide::enter_
    /* 0x1808 */ f32 _1808;
    /* 0x180c */ u8 _180c[0x1810 - 0x180c];
    /* 0x1810 */ sead::Vector3f _1810;  // compared with _1770 by PlayerSuperJumpCharge::calc_
    /* 0x181c */ sead::Vector3f _181c;  // ladder climb displacement (PlayerLadderToClimb::calc_)
    /* 0x1828 */ sead::Vector3f _1828;  // ladder start displacement (PlayerLadderUpStart::calc_)
    /* 0x1834 */ Unk1 _1834;  // x_5() angle index, copied to _1c68 (PlayerCutHorseJump::enter_)
    /* 0x1838 */ u8 _1838[0x1844 - 0x1838];
    /* 0x1844 */ ksys::Timer _1844;  // set to CleaningTime by PlayerCleaningAround::enter_
    /* 0x1850 */ ksys::Timer _1850;  // set to min(WaitTime, 5) by PlayerSkin::enter_
    /* 0x185c */ ksys::Timer _185c;  // set to Timer(3, 3) by PlayerFall::enter_
    /* 0x1868 */ s32 _1868;  // max life (PlayerInfo::setMaxLifeForPlayerActor)
    /* 0x186c */ f32 _186c;  // max stamina (PlayerInfo)
    /* 0x1870 */ Unk_71024ef4e8* _1870;  // created by prepareInit_ (0x7100eb16a0); the attached-target object
    /* 0x1878 */ AITerror _1878{this};
    /* 0x1930 */ AITerror _1930{this};
    /* 0x19e8 */ u8 _19e8[0x19f0 - 0x19e8];
    /* 0x19f0 */ sead::SafeArray<gsys::BoneAccessKey, 0x4a> _19f0;
    /* 0x1b18 */ sead::Matrix34f _1b18;
    /* 0x1b48 */ u8 _1b48[0x1b6c - 0x1b48];
    /* 0x1b6c */ sead::Matrix33f _1b6c;  // rotation around the x_5() angle (PlayerSwimMove::enter_)
    /* 0x1b90 */ void* _1b90;
    /* 0x1b98 */ u8 _1b98[0x1c68 - 0x1b98];
    /* 0x1c68 */ Unk1 _1c68;  // angle index of the anim-driven movement (sub_7100877BD8)
    /* 0x1c6c */ u8 _1c6c[0x1c70 - 0x1c6c];
    /* 0x1c70 */ u32 _1c70;  // an angle index (0x80000000 = reset by PlayerLadderDownStart::leave_)
    /* 0x1c74 */ u32 _1c74;  // an angle index (PlayerLand::enter_)
    /* 0x1c78 */ u8 _1c78[0x1c84 - 0x1c78];
    /* 0x1c84 */ u32 _1c84;  // angle index (ladder direction)
    /* 0x1c88 */ u8 _1c88[0x1ca4 - 0x1c88];
    /* 0x1ca4 */ s32 _1ca4;
    /* 0x1ca8 */ s32 _1ca8;
    /* 0x1cac */ u8 _1cac[0x1cb0 - 0x1cac];
    /* 0x1cb0 */ s32 _1cb0;  // a ui tip type (PlayerCutFall::enter_)
    /* 0x1cb4 */ u8 _1cb4[0x1cbe - 0x1cb4];
    /* 0x1cbe */ u8 _1cbe;
    /* 0x1cbf */ u8 _1cbf;
    /* 0x1cc0 */ u8 _1cc0[0x1cc8 - 0x1cc0];
    /* 0x1cc8 */ s32 _1cc8;
    /* 0x1ccc */ s32 _1ccc;
    /* 0x1cd0 */ s32 _1cd0;
    /* 0x1cd4 */ s32 _1cd4;
    /* 0x1cd8 */ s32 _1cd8;
    /* 0x1cdc */ u8 _1cdc[0x1cec - 0x1cdc];
    /* 0x1cec */ f32 _1cec;
    /* 0x1cf0 */ u8 _1cf0[0x1cf8 - 0x1cf0];
    /* 0x1cf8 */ f32 _1cf8;
    /* 0x1cfc */ u8 _1cfc[0x1d34 - 0x1cfc];
    /* 0x1d34 */ f32 _1d34;  // set by m372 (EnergyAutoRecoverInvalidTime1)
    /* 0x1d38 */ f32 _1d38;
    /* 0x1d3c */ f32 _1d3c;  // set to -1 by m372
    /* 0x1d40 */ u8 _1d40[0x1d64 - 0x1d40];
    /* 0x1d64 */ f32 _1d64;  // reset by x_40 / x_16
    /* 0x1d68 */ f32 _1d68;
    /* 0x1d6c */ f32 _1d6c;  // set to 1 by x_40 / x_16
    // Reset with Timer(0, 0) by PlayerCutAfterJust::leave_.
    /* 0x1d70 */ ksys::Timer _1d70;
    /* 0x1d7c */ u8 _1d7c[0x1dd0 - 0x1d7c];
    /* 0x1dd0 */ ksys::Timer _1dd0;  // set by PlayerFall::enter_
    /* 0x1ddc */ u8 _1ddc[0x1de8 - 0x1ddc];
    // Reset with Timer(5, 5) by PlayerCutTurnLSword::leave_.
    /* 0x1de8 */ ksys::Timer _1de8;
    /* 0x1df4 */ f32 _1df4;
    /* 0x1df8 */ f32 _1df8;
    /* 0x1dfc */ f32 _1dfc;
    /* 0x1e00 */ f32 _1e00;
    /* 0x1e04 */ f32 _1e04;
    /* 0x1e08 */ f32 _1e08;
    /* 0x1e0c */ f32 _1e0c;
    /* 0x1e10 */ f32 _1e10;
    /* 0x1e14 */ f32 _1e14;
    /* 0x1e18 */ f32 _1e18;
    /* 0x1e1c */ f32 _1e1c;
    /* 0x1e20 */ f32 _1e20;
    /* 0x1e24 */ u8 _1e24[0x1e9c - 0x1e24];
    /* 0x1e9c */ f32 _1e9c;
    /* 0x1ea0 */ f32 _1ea0;
    /* 0x1ea4 */ f32 _1ea4;
    /* 0x1ea8 */ u8 _1ea8[0x1ec0 - 0x1ea8];
    /* 0x1ec0 */ ksys::Timer _1ec0;  // set to Timer(4, 4) by PlayerTwiceJump::enter_
    /* 0x1ecc */ u8 _1ecc[0x1f84 - 0x1ecc];
    /* 0x1f84 */ s32 _1f84;
    /* 0x1f88 */ s32 _1f88;
    /* 0x1f8c */ s32 _1f8c;
    /* 0x1f90 */ u8 _1f90[0x1fbc - 0x1f90];
    /* 0x1fbc */ f32 _1fbc;
    /* 0x1fc0 */ u8 _1fc0[0x1ffc - 0x1fc0];
    /* 0x1ffc */ s32 _1ffc;
    /* 0x2000 */ f32 _2000;
    /* 0x2004 */ s32 _2004;
    /* 0x2008 */ u8 _2008[0x200c - 0x2008];
    /* 0x200c */ s32 _200c;
    /* 0x2010 */ s32 _2010;
    /* 0x2014 */ u8 _2014[0x201c - 0x2014];
    /* 0x201c */ s32 _201c;  // sub_71008859EC
    /* 0x2020 */ u8 _2020[0x2028 - 0x2020];
    /* 0x2028 */ s32 _2028;
    /* 0x202c */ s32 _202c;
    /* 0x2030 */ u8 _2030[0x2038 - 0x2030];
    /* 0x2038 */ s32 _2038;  // sub_71008859EC
    /* 0x203c */ u8 _203c[0x2040 - 0x203c];
    /* 0x2040 */ s32 _2040;
    /* 0x2044 */ s32 _2044;  // armor charge-attack status index, passed to Ecosystem
    /* 0x2048 */ u8 _2048[0x2074 - 0x2048];
    /* 0x2074 */ f32 _2074;
    /* 0x2078 */ u8 _2078[0x207e - 0x2078];
    /* 0x207e */ bool _207e;
    /* 0x207f */ bool _207f;
    /* 0x2080 */ u8 _2080[0x2081 - 0x2080];
    /* 0x2081 */ bool _2081;
    /* 0x2082 */ u8 _2082[0x2084 - 0x2082];
    /* 0x2084 */ f32 _2084;
    /* 0x2088 */ f32 _2088;
    /* 0x208c */ f32 _208c;  // getAtkMultiplier: base multiplier
    /* 0x2090 */ f32 _2090;  // getAtkMultiplier: factor applied while the Master Sword is equipped
    /* 0x2094 */ f32 _2094;
    /* 0x2098 */ f32 _2098;  // set to 1 by PlayerSitWait::leave_
    /* 0x209c */ f32 _209c;  // PlayerSwimWait::isFinished: > 0.05
    /* 0x20a0 */ u8 _20a0[0x20b4 - 0x20a0];
    /* 0x20b4 */ f32 _20b4;
    /* 0x20b8 */ u8 _20b8[0x20bc - 0x20b8];
    /* 0x20bc */ ksys::VFRValue _20bc;  // PlayerSuperBlow::calc_ calls VFRValue::chase on it
    /* 0x20c8 */ f32 _20c8;  // initial guard-slip speed (PlayerGuardSlip::enter_)
    /* 0x20cc */ u8 _20cc[0x20d0 - 0x20cc];
    /* 0x20d0 */ f32 _20d0;
    /* 0x20d4 */ f32 _20d4;  // water surface height (PlayerSwimJump)
    /* 0x20d8 */ u8 _20d8[0x20f0 - 0x20d8];
    /* 0x20f0 */ f32 _20f0;
    /* 0x20f4 */ u8 _20f4[0x2100 - 0x20f4];
    /* 0x2100 */ f32 _2100;  // PlayerLadderUpEnd::enter_
    /* 0x2104 */ u8 _2104[0x211c - 0x2104];
    /* 0x211c */ f32 _211c;  // cleared by PlayerLand::enter_
    /* 0x2120 */ u8 _2120[0x2158 - 0x2120];
    /* 0x2158 */ f32 _2158;  // copy of _1770.y (PlayerClimb::leave_)
    /* 0x215c */ u8 _215c[0x2184 - 0x215c];
    /* 0x2184 */ sead::Vector3f _2184;
    /* 0x2190 */ u8 _2190[0x21b8 - 0x2190];
    // Three lock-guarded positions (m245 / getPosCopyMagnesis / m244 return a pointer to `mPos`).
    struct LockedPos {
        sead::CriticalSection mLock;
        sead::Vector3f mPos;
        u32 _4c;
    };
    KSYS_CHECK_SIZE_NX150(LockedPos, 0x50);
    /* 0x21b8 */ LockedPos _21b8;
    /* 0x2208 */ LockedPos _2208;
    /* 0x2258 */ LockedPos _2258;
    /* 0x22a8 */ sead::Vector3f _22a8;
    /* 0x22b4 */ sead::Vector3f _22b4;
    /* 0x22c0 */ sead::Vector3f _22c0;
    /* 0x22cc */ u8 _22cc[0x22e8 - 0x22cc];
    /* 0x22e8 */ sead::Vector3f _22e8;
    /* 0x22f4 */ sead::Vector3f _22f4;  // ladder related (PlayerLadderDownStart / PlayerLadderUpStart)
    /* 0x2300 */ u8 _2300[0x230c - 0x2300];
    /* 0x230c */ sead::Vector3f _230c;
    /* 0x2318 */ u8 _2318[0x23e0 - 0x2318];
    /* 0x23e0 */ PlayerArmors _23e0;
    /* 0x2550 */ uking::act::Unk_71008502cc _2550{this};  // m159; _2550._8 (BitFlag16): bit 5 is tested by PlayerShock::calc_
    /* 0x26a0 */ BaseProcLink _26a0;
    /* 0x26b0 */ RideInfo _26b0{this};  // getPlayerRideInfo
    /* 0x29a8 */ u8 _29a8[0x2c28 - 0x29a8];
    /* 0x2c28 */ BaseProcLink _2c28;  // woken/put to sleep by PlayerSuperJump / PlayerLand / PlayerFall
    /* 0x2c38 */ BaseProcLink _2c38;
    /* 0x2c48 */ BaseProcLink _2c48;  // isRevivalFairyActive
    /* 0x2c58 */ u8 _2c58[0x2c78 - 0x2c58];
    /* 0x2c78 */ BaseProcLink _2c78;  // set up and woken by PlayerSuperJumpCharge::calc_
    /* 0x2c88 */ BaseProcLink _2c88;  // isZoraHeroActive
    /* 0x2c98 */ BaseProcLink _2c98;
    /* 0x2ca8 */ u8 _2ca8[0x2d64 - 0x2ca8];
    /* 0x2d64 */ bool _2d64;  // set by PlayerTurnAndLookToObjectNow::leave_
    /* 0x2d65 */ u8 _2d65[0x2ec0 - 0x2d65];
};
KSYS_CHECK_SIZE_NX150(Player, 0x2ec0);

// 0x8777b8 / 0x8779c8 / 0x882178 (CSV names): checks of the player's current AS (bow reload / charge /
// reload, charge or shoot).
bool playerIsReloadingBow(Player* player);
bool playerIsChargingBow(Player* player);
bool playerIsReloadingOrChargingOrShootingBow(Player* player);

}  // namespace ksys::act

// 0x7100a95270: equipped arrow name/count query; declaration only, namespace unknown.
bool sub_7100A95270(sead::BufferedSafeString* out);
