#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

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
    explicit Player(const CreateArg& arg);
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
    /*  41 */ void m41() override;
    /*  42 */ void m42(const sead::Matrix34f& mtx) override;
    /*  47 */ bool m47() override;
    /*  50 */ bool m50() override;
    /*  62 */ bool shouldUnload() override { return false; }
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
    /*  99 */ void getArmors() override;
    /* 109 */ int m109() override { return 0x30; }
    /* 114 */ void m114() override;
    /* 115 */ void m115() override;
    /* 116 */ void m116() override;
    /* 117 */ void m117() override;
    /* 119 */ void m119() override;
    /* 129 */ void m129() override;
    /* 130 */ uking::act::HorseRideInfo* getPlayerRideInfo() override;
    /* 145 */ void m145() override {}
    /* 146 */ bool m146() override;
    /* 147 */ void m147() override;
    /* 148 */ f32 m148() override { return _20d0; }
    /* 151 */ bool m151(u16 bit) override;
    /* 157 */ void m157() override;
    /* 158 */ void m158() override;
    /* 159 */ uking::act::Unk_71025ae680* m159() override;
    /* 160 */ void m160() override;
    /* 161 */ void m161() override;
    /* 165 */ void m165() override;
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
    /* 219 */ bool m219() override { return _2559 >> 1 & 1; }
    /* 224 */ bool m224() override { return _1f84 == 3 || _1f84 == 4; }
    /* 225 */ bool m225() override;
    /* 226 */ bool m226() override;
    /* 227 */ bool m227() override;
    /* 228 */ void m228() override;
    /* 229 */ void m229() override;
    /* 230 */ bool m230() override;
    /* 231 */ f32 m231() override;
    /* 232 */ f32 getAncientAttackRate() override;
    /* 233 */ f32 m233(int) override;
    /* 234 */ bool m234() override;
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
    /* 258 */ void m258() override;
    /* 261 */ void m261() override;
    /* 263 */ void getAttachedTargetActor2() override;
    /* 264 */ void getAttachedTargetActor() override;
    /* 265 */ const sead::Vector3f* m265() override { return &_230c; }
    /* 267 */ void m267() override;
    /* 268 */ bool m268() override;
    /* 269 */ bool m269() override;
    /* 270 */ bool m270() override;
    /* 272 */ void m272() override;
    /* 273 */ void m273() override;
    /* 274 */ void m274() override;
    /* 275 */ void m275() override;
    /* 276 */ void m276() override;
    /* 277 */ void m277(ActorConstDataAccess* accessor, int idx) override;
    /* 278 */ void m278() override;
    /* 279 */ bool getArmorDyeStuff() override;
    /* 280 */ bool m280() override;
    /* 281 */ bool isEquipedDyedArmor() override;
    /* 282 */ void getArmorSeriesType(sead::BufferedSafeString* out) override;
    /* 283 */ void getEnemyTeam(sead::BufferedSafeString* out) override;
    /* 284 */ bool ArmorSeriesTypeStuff() override;
    /* 285 */ void armorSeriesStuff() override;
    /* 286 */ void getMaskType(sead::BufferedSafeString* out) override;
    /* 287 */ bool m287() override;
    /* 288 */ bool m288() override;
    /* 289 */ bool m289() override;
    /* 290 */ bool m290() override;
    /* 291 */ bool m291() override;
    /* 295 */ bool m295() override;
    /* 296 */ bool m296() override;
    /* 297 */ s32 m297() override { return _1f8c; }
    /* 298 */ bool m298(int) override;
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
    /* 312 */ s32 m312(int idx) override;
    /* 318 */ void m318() override;
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
    /* 378 */ bool m378() override;
    /* 379 */ void m379() override;
    /* 380 */ void m380() override;
    /* 381 */ void m381() override;
    /* 382 */ void m382() override;
    /* 383 */ bool m383() override { return _c50.isOnBit(18); }
    /* 384 */ int m384() override { return _1cd4; }
    /* 385 */ int m385() override { return _1cd8; }
    /* 386 */ virtual void m386() {}

    // Non-virtual member functions (CSV names; placeholder names x_NN are the CSV's).
    // Parameter names are unknown; the order of float vs. integer parameters is a guess.
    void switchToAnimSequenceMaybe(const char* name, bool a2, f32 a3);  // 0x855608
    void x_23(const char* name, bool a2, f32 a3);                       // 0x85588c
    void x_18(bool a1);                                                 // 0x855a6c
    // All 33 callers pass -1.0f in s0, which x_19 does not use.
    void x_19(f32 a1);                                                  // 0x855d40
    void x_24();                                                        // 0x855e24
    void x_25();                                                        // 0x8551fc
    void x_53(int* a1);                                                 // 0x8679fc
    // A 4-byte angle index (sead::Mathf::atan2Idx result) returned through x8, so not trivially
    // copyable in the original; the same type as 0x710092dba4's result (ksys::util placeholder).
    using Unk1 = util::Unk_7101EC6BAC;
    Unk1 x_5();                                                         // 0x85ed1c
    f32 x_39();                                                         // 0x867cd4
    void someFloatCalc(f32 a1, const sead::Vector3f& a2);               // 0x868990
    f32 getStatusEffectSpeed();                                         // 0x869a8c
    void actionCommon();                                                // 0x86aa94
    bool isSurfingOnGround() const;                                     // 0x87f290
    bool stillAlive();                                                  // 0x884510
    bool x_44();                                                        // 0x885090
    void x_34(f32 value, bool a2);                                      // 0x885bb4
    void decreaseStaminaForActionMaybe(f32 value);                      // 0x885bd0
    bool x_21();                                                        // 0x887a20
    bool isMasterSwordEquipped_();                                      // 0x86d024
    bool x_35();                                                        // 0x8886f4
    void x_7();                                                         // 0x88a048
    // All ~45 callers pass (0, 0); x_8 does not read them (types a guess).
    void x_8(bool a1, bool a2);                                         // 0x88a8a8
    void x_33();                                                        // 0x88c900
    void x_38();                                                        // 0x88d564
    // 0x8922c4 (CSV playerWeapons_return0, ~45 player AI callers): a weapon slot index (always 0).
    s32 playerWeapons_return0();
    void x_40();                                                        // 0x8922cc
    bool x_17();                                                        // 0x892bf0
    void x_16();                                                        // 0x892e18

    /* 0x17f0 */ u8 _17f0[0x1868 - 0x17f0];
    /* 0x1868 */ s32 _1868;  // max life (PlayerInfo::setMaxLifeForPlayerActor)
    /* 0x186c */ f32 _186c;  // max stamina (PlayerInfo)
    /* 0x1870 */ void* _1870;
    /* 0x1878 */ u8 _1878[0x1b18 - 0x1878];
    /* 0x1b18 */ sead::Matrix34f _1b18;
    /* 0x1b48 */ u8 _1b48[0x1b90 - 0x1b48];
    /* 0x1b90 */ void* _1b90;
    /* 0x1b98 */ u8 _1b98[0x1ca4 - 0x1b98];
    /* 0x1ca4 */ s32 _1ca4;
    /* 0x1ca8 */ u8 _1ca8[0x1cbe - 0x1ca8];
    /* 0x1cbe */ u8 _1cbe;
    /* 0x1cbf */ u8 _1cbf[0x1cc8 - 0x1cbf];
    /* 0x1cc8 */ s32 _1cc8;
    /* 0x1ccc */ s32 _1ccc;
    /* 0x1cd0 */ s32 _1cd0;
    /* 0x1cd4 */ s32 _1cd4;
    /* 0x1cd8 */ s32 _1cd8;
    /* 0x1cdc */ u8 _1cdc[0x1d70 - 0x1cdc];
    // Reset with Timer(0, 0) by PlayerCutAfterJust::leave_.
    /* 0x1d70 */ ksys::Timer _1d70;
    /* 0x1d7c */ u8 _1d7c[0x1de8 - 0x1d7c];
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
    /* 0x1e24 */ u8 _1e24[0x1f84 - 0x1e24];
    /* 0x1f84 */ s32 _1f84;
    /* 0x1f88 */ s32 _1f88;
    /* 0x1f8c */ s32 _1f8c;
    /* 0x1f90 */ u8 _1f90[0x1ffc - 0x1f90];
    /* 0x1ffc */ s32 _1ffc;
    /* 0x2000 */ f32 _2000;
    /* 0x2004 */ u8 _2004[0x2074 - 0x2004];
    /* 0x2074 */ f32 _2074;
    /* 0x2078 */ u8 _2078[0x207e - 0x2078];
    /* 0x207e */ bool _207e;
    /* 0x207f */ u8 _207f[0x2081 - 0x207f];
    /* 0x2081 */ bool _2081;
    /* 0x2082 */ u8 _2082[0x2084 - 0x2082];
    /* 0x2084 */ f32 _2084;
    /* 0x2088 */ f32 _2088;
    /* 0x208c */ u8 _208c[0x2094 - 0x208c];
    /* 0x2094 */ f32 _2094;
    /* 0x2098 */ u8 _2098[0x20d0 - 0x2098];
    /* 0x20d0 */ f32 _20d0;
    /* 0x20d4 */ u8 _20d4[0x20f0 - 0x20d4];
    /* 0x20f0 */ f32 _20f0;
    /* 0x20f4 */ u8 _20f4[0x22a8 - 0x20f4];
    /* 0x22a8 */ sead::Vector3f _22a8;
    /* 0x22b4 */ u8 _22b4[0x22e8 - 0x22b4];
    /* 0x22e8 */ sead::Vector3f _22e8;
    /* 0x22f4 */ u8 _22f4[0x230c - 0x22f4];
    /* 0x230c */ sead::Vector3f _230c;
    /* 0x2318 */ u8 _2318[0x23e0 - 0x2318];
    /* 0x23e0 */ u8 _23e0[0x2550 - 0x23e0];  // armors (CSV PlayerArmors::*; Actor::getArmors returns it)
    /* 0x2550 */ u8 _2550[0x2559 - 0x2550];
    /* 0x2559 */ u8 _2559;
    /* 0x255a */ u8 _255a[0x26b0 - 0x255a];
    /* 0x26b0 */ u8 _26b0[0x2c98 - 0x26b0];  // ride info (CSV Player::RideInfo::*)
    /* 0x2c98 */ BaseProcLink _2c98;
    /* 0x2ca8 */ u8 _2ca8[0x2ec0 - 0x2ca8];
};
KSYS_CHECK_SIZE_NX150(Player, 0x2ec0);

}  // namespace ksys::act
