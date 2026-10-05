#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking {
class Unk_710246d058;
}

namespace uking::act {
class Weapon;
}

namespace ksys::act {

namespace acc {
class PlayerBase;
}
class PlayerInfo;

// TODO: incomplete. The vtable has 360 slots (177-359 are new); PlayerLink is at 0xc38.
// Size 0x17f0 (Player's first member).
class PlayerBase : public PlayerOrEnemy, public PlayerLink {
    SEAD_RTTI_OVERRIDE(PlayerBase, PlayerOrEnemy)
public:
    explicit PlayerBase(const CreateArg& arg);
    ~PlayerBase() override;

    // FIXME: name for x and name+type for y
    void switchEquipment(const sead::SafeString& slot, int frames, int x = -1,
                         const uintptr_t& y = {});
    // 0x7100848efc (CSV name; ~70 callers): the name of equipment type `type` (an entry of a table
    // of SafeStrings in the PlayerBase TU's static data; `this` is unused).
    const sead::SafeString& getEquipmentTypeName(u32 type) const;

    // FIXME: name for x
    void setExtraLife(s32 extra_life, f32 x);
    void addExtraStamina(f32 x, f32 y);
    // 0x710084ae08 (CSV Player::setStaminaDelta): adds `delta` to the current core's stamina delta (_e7c).
    void setStaminaDelta(f32 delta);
    // 0x710084ac00 / 0x710084ac68 / 0x710084ae78 (placeholder names): add `delta` / the player's maximum life / the
    // maximum stamina to the current core's life delta (_e70) / life delta / stamina delta (_e7c).
    void addLifeDelta(s32 delta);
    void sub_710084AC68();
    void sub_710084AE78();
    // 0x710084aa0c (placeholder name): clears _1278, _1280 and _1290 under _1238.
    void sub_710084AA0C();
    // 0x710084b62c / 0x710084b680 / 0x710084b6d4 / 0x710084b7c0 (CSV Player::setItemVel / setItemSwimVel; the
    // other two are placeholder names): store (f32(type), value) under _1140.
    void setItemVel(s32 type, f32 vel);
    void setItemSwimVel(s32 type, f32 vel);
    void sub_710084B6D4(s32 type, f32 vel);
    void sub_710084B7C0(s32 type, f32 value);
    void sub_710084B810(s32 type, f32 value);
    void sub_710084B860(s32 type, f32 value);
    void sub_710084B8B0(s32 type, f32 value);
    void sub_710084B900(s32 type, f32 value);
    void sub_710084B950(s32 type, f32 value);
    void sub_710084B9A0(s32 type, f32 value);
    void sub_710084B9F0(s32 type, f32 value);
    void sub_710084BA40(s32 type, f32 value);
    // 0x710084b5c4 (CSV Player::x_12): zeroes the item velocities (and the extra life / stamina unless
    // `keep_extra`) and the block at _11a8.
    void x_12(bool keep_extra);
    // 0x710084aa9c (placeholder name): copies the link _1280 to `out` if _c40 bit 14 is set.
    bool sub_710084AA9C(BaseProcLink* out);
    // 0x710084aef8 (placeholder name; no `this`): resets the player info's current maximum stamina.
    static void sub_710084AEF8();
    // 0x710084ab8c (CSV Player::setNewPlayerMtx): stores the matrix under _1700 and sets _ce0 bit 7.
    void setNewPlayerMtx(const sead::Matrix34f& mtx);

    // FIXME: takes a phys::RigidBody* (calls RigidBody::getPosition on it), like Actor::m92
    void m92(phys::RigidBody* body) override;
    bool m140() override { return _cf0.isOnBit(25) || m180(); }

    // FIXME: figure out return types, parameters and names
    /* 177 */ bool isRidingHorse() override;
    /* 178 */ bool m178() override { return _c40.isOnBit(1); }
    /* 179 */ bool m179() override;
    /* 180 */ virtual bool m180() { return false; }
    /* 181 */ virtual bool m181() { return false; }
    /* 182 */ virtual bool m182() { return false; }
    /* 183 */ virtual bool m183() { return false; }
    /* 184 */ bool m184() override { return _c50.isOnBit(7); }
    /* 185 */ bool m185() override { return _cec.isOnBit(6); }
    /* 186 */ bool m186() override { return _cec.isOnBit(7); }
    /* 187 */ bool m187() override { return _cf0.isOnBit(21); }
    /* 188 */ bool m188() override { return _cec.isOnBit(10); }
    /* 189 */ virtual bool m189() { return _cec.isOnBit(11); }
    /* 190 */ virtual bool m190() { return _cf0.isOnBit(13); }
    /* 191 */ bool m191() override { return _cf0.isOnBit(14); }
    /* 192 */ f32 m192() override { return _e58; }
    /* 193 */ virtual bool m193() { return _cf0.isOnBit(16); }
    /* 194 */ bool m194() override { return _cec.isOnBit(15); }
    /* 195 */ virtual bool m195() { return _cf8.isOnBit(4); }
    /* 196 */ bool m196() override { return _cec.isOnBit(16); }
    /* 197 */ bool m197() override { return _cf0.isOnBit(24); }
    /* 198 */ virtual bool isNoShieldDamageFloor() { return false; }
    /* 199 */ bool m199() override { return _cec.isOnBit(2); }
    /* 200 */ bool m200() override { return _cec.isOnBit(1); }
    /* 201 */ virtual bool m201() { return _cec.isOnBit(26); }
    /* 202 */ bool m202() override;
    /* 203 */ bool m203() override { return false; }
    /* 204 */ bool m204() override { return _cf4.isOnBit(8); }
    /* 205 */ virtual bool m205() { return _cf4.isOn(0x900); }
    /* 206 */ bool m206() override { return _cf4.isOnBit(10); }
    /* 207 */ virtual bool m207() { return _cf4.isOnBit(11); }
    /* 208 */ virtual bool m208() { return false; }
    /* 209 */ bool m209() override { return _c48.isOnBit(2); }
    /* 210 */ bool m210() override { return _c48.isOnBit(4); }
    /* 211 */ bool m211() override { return _c48.isOnBit(5); }
    /* 212 */ virtual bool m212() { return _cf4.isOnBit(12); }
    /* 213 */ virtual bool isMasterSwordEquipped() { return false; }
    /* 214 */ virtual bool m214() { return false; }
    /* 215 */ virtual bool m215() { return false; }
    /* 216 */ virtual bool armorEffectHasWakeWindEffect() { return false; }
    /* 217 */ virtual bool m217() { return false; }
    /* 218 */ virtual bool m218() { return false; }
    /* 219 */ virtual bool m219() { return false; }
    /* 220 */ bool m220() override { return _c48.isOnBit(17); }
    /* 221 */ bool m221() override { return _c4c.isOnBit(12); }
    /* 222 */ bool m222() override { return _c4c.isOnBit(18); }
    /* 223 */ void m223() override;
    /* 224 */ virtual bool m224() { return false; }
    /* 225 */ virtual bool m225() { return false; }
    /* 226 */ virtual bool m226() { return false; }
    /* 227 */ virtual bool m227() { return false; }
    /* 228 */ virtual void m228(bool a1);
    /* 229 */ virtual void m229() {}
    /* 230 */ virtual bool m230() { return false; }
    /* 231 */ virtual f32 m231() { return 1.0f; }
    /* 232 */ virtual f32 getAncientAttackRate() { return 1.0f; }
    /* 233 */ virtual f32 m233(int) { return 1.0f; }
    /* 234 */ virtual s32 m234() { return 0; }  // the upper armor's mantle type for the player
    /* 235 */ virtual f32 m235() { return 0.0f; }
    /* 236 */ virtual f32 getBoneAttackRate() { return 1.0f; }
    /* 237 */ bool m237() override;
    /* 238 */ bool m238() override;
    /* 239 */ bool m239() override;
    /* 240 */ bool m240() override;
    /* 241 */ virtual bool m241() { return true; }
    /* 242 */ virtual bool m242() { return false; }
    /* 243 */ virtual bool m243() { return false; }
    /* 244 */ virtual const sead::Vector3f* m244() { return &sead::Vector3f::zero; }
    /* 245 */ virtual const sead::Vector3f* m245() { return &sead::Vector3f::zero; }
    /* 246 */ virtual const sead::Vector3f* getPosCopyMagnesis() { return &sead::Vector3f::zero; }
    /* 247 */ virtual const sead::Vector3f* m247() { return &sead::Vector3f::zero; }
    /* 248 */ virtual f32 m248() { return 0.0f; }
    /* 249 */ virtual bool m249() { return false; }
    /* 250 */ virtual const sead::Vector3f* m250() { return &sead::Vector3f::zero; }
    /* 251 */ virtual const sead::Vector3f* m251() { return &sead::Vector3f::zero; }
    /* 252 */ virtual const sead::Vector3f* m252() { return &sead::Vector3f::zero; }
    /* 253 */ virtual const sead::Vector3f* m253() { return &sead::Vector3f::zero; }
    /* 254 */ virtual bool m254() { return false; }
    /* 255 */ virtual const sead::Vector3f* m255() { return &sead::Vector3f::zero; }
    /* 256 */ virtual bool m256() { return false; }
    /* 257 */ virtual bool m257() { return false; }
    /* 258 */ virtual bool m258(f32* out) { return false; }
    /* 259 */ void m259() override { _c50.setBit(22); }
    /* 260 */ virtual bool m260() { return false; }
    /* 261 */ virtual bool m261(f32* out) { return false; }
    /* 262 */ bool isGroundForEvent() override;
    /* 263 */ Unk_71024ef4e8* getAttachedTargetActor2() override;
    /* 264 */ Unk_71024ef4e8* getAttachedTargetActor() override;
    /* 265 */ virtual const sead::Vector3f* m265() { return &sead::Vector3f::zero; }
    /* 266 */ virtual void m266(const sead::SafeString& slot, int frames);
    /* 267 */ virtual void m267();
    /* 268 */ virtual bool m268() { return false; }
    /* 269 */ virtual bool m269() { return false; }
    /* 270 */ virtual bool m270() { return false; }
    /* 271 */ virtual s32 m271() { return _d24; }
    /* 272 */ void getArmorPartName(u8 idx, sead::BufferedSafeString* out) override {}
    /* 273 */ uking::act::Weapon* m273() override { return nullptr; }
    /* 274 */ uking::act::Weapon* m274() override { return nullptr; }
    /* 275 */ uking::act::Weapon* m275() override { return nullptr; }
    /* 276 */ Actor* m276(int idx) override { return nullptr; }
    /* 277 */ virtual void m277(ActorConstDataAccess* accessor, int idx) {}
    /* 278 */ virtual s32 m278(u8 idx) { return -1; }
    /* 279 */ virtual s32 getArmorDyeStuff() { return 0; }
    /* 280 */ virtual bool m280() { return false; }
    /* 281 */ virtual bool isEquipedDyedArmor() { return false; }
    /* 282 */ virtual void getArmorSeriesType(sead::BufferedSafeString* out) {}
    /* 283 */ virtual void getEnemyTeam(sead::BufferedSafeString* out) {}
    /* 284 */ virtual bool ArmorSeriesTypeStuff() { return false; }
    /* 285 */ virtual bool armorSeriesStuff(u8 idx, const sead::SafeString& series) { return false; }
    /* 286 */ virtual void getMaskType(sead::BufferedSafeString* out) {}
    /* 287 */ virtual bool m287() { return false; }
    /* 288 */ virtual s32 m288() { return 0; }
    /* 289 */ virtual s32 m289() { return 0; }
    /* 290 */ virtual bool m290() { return false; }
    /* 291 */ virtual s32 m291() { return 0; }
    /* 292 */ bool m292() override { return _c40.isOnBit(31); }
    /* 293 */ virtual void m293();
    /* 294 */ virtual void m294();
    /* 295 */ virtual bool m295() { return false; }
    /* 296 */ virtual s32 m296() { return 0; }
    /* 297 */ virtual s32 m297() { return 0; }
    /* 298 */ virtual s32 m298(int) { return 0; }
    /* 299 */ bool m299() override { return _c44.isOnBit(2); }
    /* 300 */ virtual f32 m300() { return 1.0f; }
    /* 301 */ virtual f32 m301() { return 1.0f; }
    /* 302 */ virtual bool m302() { return false; }
    /* 303 */ virtual bool m303() { return false; }
    /* 304 */ virtual bool m304() { return false; }
    /* 305 */ virtual f32 m305() { return 0.0f; }
    /* 306 */ bool m306() override { return false; }
    /* 307 */ void m307() override {
        const auto lock = sead::makeScopedLock(_c58);
        _c98.set(0x40);
    }

    // inline-only in the original; name is a guess. Evidence: m266 / m307 and SwitchPlayerEquipment::calc_
    // inline it with a constant.
    void setC98Locked(u32 bits) {
        const auto lock = sead::makeScopedLock(_c58);
        _c98.set(bits);
    }
    // inline-only in the original; name is a guess. Evidence: PlayerHell::calc_, PlayerHellNoFade::calc_,
    // PlayerHellStartWait::calc_ and PlayerEventStartWait::calc_ (and acc::PlayerBase accessors) lock
    // _ca0 around an update of _ce0.
    void setCE0Locked(u32 bits) {
        const auto lock = sead::makeScopedLock(_ca0);
        _ce0.set(bits);
    }
    /* 308 */ void m308() override;
    /* 309 */ virtual void m309(f32) {}
    /* 310 */ virtual void m310(f32) {}
    /* 311 */ virtual void m311();
    /* 312 */ virtual gsys::BoneAccessKey m312(int idx);
    /* 313 */ void getActorDirect() override;
    /* 314 */ void* m314() override;
    /* 315 */ void m315() override { m139(); }
    /* 316 */ f32 m316() override { return _1654; }
    /* 317 */ f32 m317() override;
    /* 318 */ virtual void m318(sead::Matrix34f* out) {}
    /* 319 */ f32 m319() override { return 1.0f; }
    /* 320 */ virtual f32 m320() { return 1.0f; }
    /* 321 */ virtual s32 m321() { return 0; }
    /* 322 */ virtual s32 m322() { return 0; }
    /* 323 */ virtual void m323() {}
    /* 324 */ virtual void m324(int) {}
    /* 325 */ virtual void m325(f32) {}
    /* 326 */ virtual f32 m326() { return 0.0f; }
    /* 327 */ virtual f32 m327() { return 0.0f; }
    /* 328 */ virtual bool m328() { return false; }
    /* 329 */ virtual bool isRevivalFairyActive(ActorConstDataAccess* accessor) { return false; }
    /* 330 */ virtual bool isZoraHeroActive(ActorConstDataAccess* accessor) { return false; }
    /* 331 */ virtual bool canUseRevaliGale() { return false; }
    /* 332 */ virtual bool canUseDarukProtection() { return false; }
    /* 333 */ virtual bool canUseUrbosaFury() { return false; }
    /* 334 */ virtual bool canUseMiphaGrace() { return false; }
    /* 335 */ virtual f32 getRevaliGaleTime() { return 0.0f; }
    /* 336 */ virtual f32 m336() { return 0.0f; }
    /* 337 */ virtual f32 m337() { return 0.0f; }
    /* 338 */ virtual f32 m338() { return 0.0f; }
    /* 339 */ virtual f32 m339() { return 1.0f; }
    /* 340 */ virtual f32 m340() { return 1.0f; }
    /* 341 */ virtual f32 m341() { return 1.0f; }
    /* 342 */ virtual f32 m342() { return 1.0f; }
    /* 343 */ virtual s32 m343() { return 0; }
    /* 344 */ virtual s32 m344() { return 0; }
    /* 345 */ virtual s32 m345() { return 0; }
    /* 346 */ virtual void updateSupportTimerRates() {}
    /* 347 */ virtual bool isDarukProtectionEnabled() { return false; }
    /* 348 */ virtual bool m348() { return false; }
    /* 349 */ sead::Vector3f& getPlayerPosForPostCalc() override;
    /* 350 */ virtual f32 getNoDeathDamage() { return 0.0f; }
    /* 351 */ virtual BaseProcLink& getSpAttackTarget() { return getDummyBaseProcLink(); }
    /* 352 */ virtual bool m352(sead::Vector3f* out) { return false; }
    /* 353 */ bool m353() override { return false; }
    /* 354 */ virtual f32 getAtkMultiplier() { return 1.0f; }
    /* 355 */ bool getActorViaAccessor(ActorLinkConstDataAccess* accessor) override;
    /* 356 */ PlayerBase* getPlayer() override;
    /* 357 */ virtual sead::Vector3f* m357();
    /* 358 */ SeadController* m358() override;
    /* 359 */ virtual bool m359() { return false; }

    // Non-virtual member functions defined in PlayerBase's TU (CSV names, prefix "Player::").
    bool isSlowTime() const;                 // 0x848f10 (reads a global slow-time object)
    bool x_51();                             // 0x848f34 (controller object at 0x17d0, check 3)
    uking::Unk_710246d058* get17d0() const { return _17d0; }
    BaseProcLink& get1280() { return _1280; }
    bool x_50();                             // 0x848f4c
    bool x_48();                             // 0x84a988
    bool x_2();                              // 0x84bce8
    bool checkCanUseRuneCommon();            // 0x84c04c
    bool x_13();                             // 0x84c378
    // Called by RuneMgr::checkCanUseRune (CSV names Player::checkCanUse*, but the player is
    // passed as a PlayerBase).
    bool checkCanUseMagnesis();              // 0x84c320
    bool checkCanUseCamera();                // 0x84c7b4
    bool checkCanUseMotorcycle();            // 0x84c8e4
    bool checkCanUseAmiibo();                // 0x84c924
    bool runeMgrCheckCanUseRoundBomb();      // 0x84ccc0
    bool runeMgrCheckCanUseSquareBomb();     // 0x84ccdc
    bool runeMgrCheckCanUseMagnesis();       // 0x84ccf8
    bool runeMgrCheckCanUseCryonis();        // 0x84cd14
    bool runeMgrCheckCanUseCamera();         // 0x84cd30
    bool runeMgrCheckIsCameraSelected();     // 0x84cd4c
    bool sub_710084A6B8();                   // 0x84a6b8 (RuneMgr flag bit 5; unnamed in the CSV)

protected:
    friend class acc::PlayerBase;
    friend class PlayerInfo;

public:
    // State flags; also read and written directly by action code (inlined accesses).
    /* 0xc40 */ sead::BitFlag32 _c40;
    /* 0xc44 */ sead::BitFlag32 _c44;
    /* 0xc48 */ sead::BitFlag32 _c48;
    /* 0xc4c */ sead::BitFlag32 _c4c;
    /* 0xc50 */ sead::BitFlag64 _c50;

protected:
    /* 0xc58 */ sead::CriticalSection _c58;
public:
    // Public: PlayerLand::enter_ tests a bit without locking _c58.
    /* 0xc98 */ sead::BitFlag32 _c98;

protected:
    /* 0xca0 */ sead::CriticalSection _ca0;
    /* 0xce0 */ sead::BitFlag32 _ce0;
    /* 0xce4 */ u8 _ce4[4];

public:
    // Public: cleared by PlayerAction::enter_.
    /* 0xce8 */ s32 _ce8;
    // Public: AI actions reset bits directly (PlayerGuardBreak::calc_).
    /* 0xcec */ sead::BitFlag32 _cec;
    // Public: AI actions set bits directly (PlayerStepAttack::enter_).
    /* 0xcf0 */ sead::BitFlag32 _cf0;
    // Public: AI actions set bits directly (PlayerDrown::enter_).
    /* 0xcf4 */ sead::BitFlag32 _cf4;
    // Public: AI actions set bits directly (PlayerCutHorseJump::enter_).
    /* 0xcf8 */ sead::BitFlag32 _cf8;

public:
    // Public: AI actions reset bits directly (PlayerSuperJump::enter_).
    /* 0xcfc */ sead::BitFlag32 _cfc;

protected:
    /* 0xd00 */ u8 _d00[0xd10 - 0xd00];
public:
    // Public: read by PlayerStepGuardJust::calc_.
    /* 0xd10 */ u8 _d10;
    // Public: read by PlayerLand::calc_.
    /* 0xd11 */ u8 _d11;

protected:
    /* 0xd12 */ u8 _d12[0xd18 - 0xd12];
public:
    // Public: written by PlayerDrown::leave_ / PlayerHellStartWait::enter_.
    /* 0xd18 */ s32 _d18;
    /* 0xd1c */ u8 _d1c;  // 1-3 select the CutAfterJump turn angle (PlayerCutAfterJump::enter_)

protected:
    /* 0xd1d */ u8 _d1d[0xd24 - 0xd1d];

public:
    // Public: read by PlayerCutFall / PlayerSpAttack leave_ (x_7 is called when it is 0).
    /* 0xd24 */ s32 _d24;

protected:
    /* 0xd28 */ u8 _d28[0xd30 - 0xd28];

public:
    // Written directly by AI code (PlayerBeetle::leave_: equipment type name 0).
    /* 0xd30 */ sead::FixedSafeString<64> _d30;

protected:
    /* 0xd88 */ u8 _d88[0xda0 - 0xd88];
    /* 0xda0 */ sead::FixedSafeString<64> _da0;
    /* 0xdf8 */ sead::FixedSafeString<64> _df8;
    /* 0xe50 */ u8 _e50[0xe54 - 0xe50];
    /* 0xe54 */ f32 _e54;
    /* 0xe58 */ f32 _e58;
    /* 0xe5c */ s32 _e5c;
    /* 0xe60 */ u8 _e60[0xe70 - 0xe60];
    /* 0xe70 */ sead::SafeArray<s32, 3> _e70;  // per core: life delta
    /* 0xe7c */ sead::SafeArray<f32, 3> _e7c;  // per core: stamina delta (setStaminaDelta)
    /* 0xe88 */ BaseProcLink _e88;
    /* 0xe98 */ BaseProcLink _e98;
public:  // read by PlayerLookAtObject::m38
    /* 0xea8 */ BaseProcLink _ea8;
protected:
    /* 0xeb8 */ u8 _eb8[0x1140 - 0xeb8];
    /* 0x1140 */ sead::CriticalSection _1140;
    /* 0x1180 */ f32 _1180;  // item velocity type (setItemVel)
    /* 0x1184 */ f32 _1184;  // item velocity
    /* 0x1188 */ f32 _1188;  // item swim velocity type (setItemSwimVel)
    /* 0x118c */ f32 _118c;
    /* 0x1190 */ f32 _1190;  // (sub_710084B6D4)
    /* 0x1194 */ f32 _1194;
    /* 0x1198 */ s32 _1198;
    /* 0x119c */ f32 _119c;
    /* 0x11a0 */ f32 _11a0;
    /* 0x11a4 */ f32 _11a4;
    // Nine (type, value) pairs written by sub_710084B7C0 / B810 / ... / BA40 (one setter each) under _1140.
    struct TypeValue {
        s32 type;
        f32 value;
    };
    /* 0x11a8 */ TypeValue _11a8[9];
    /* 0x11f0 */ u8 _11f0[0x1238 - 0x11f0];
    /* 0x1238 */ sead::CriticalSection _1238;
    /* 0x1278 */ bool _1278;
    /* 0x1280 */ BaseProcLink _1280;
    /* 0x1290 */ sead::FixedSafeString<32> _1290;
    /* 0x12c8 */ u8 _12c8[0x1358 - 0x12c8];
    /* 0x1358 */ sead::CriticalSection _1358;
    /* 0x1398 */ bool _1398;
    /* 0x1399 */ u8 _1399[0x1478 - 0x1399];
    /* 0x1478 */ sead::CriticalSection _1478;
    /* 0x14b8 */ bool _14b8;
    /* 0x14b9 */ u8 _14b9[0x14c0 - 0x14b9];
public:
    /* 0x14c0 */ bool _14c0;  // cleared by ~30 player action leave_ functions

protected:
    /* 0x14c1 */ u8 _14c1[0x1530 - 0x14c1];
    /* 0x1530 */ sead::CriticalSection _1530;
    /* 0x1570 */ BaseProcLink _1570;
    /* 0x1580 */ u8 _1580[0x1610 - 0x1580];
    /* 0x1610 */ sead::CriticalSection _1610;
    /* 0x1650 */ bool _1650;  // set under _1610 together with _1654 (Player::sub_710084BA90)
    /* 0x1651 */ u8 _1651[3];
    /* 0x1654 */ f32 _1654;
    /* 0x1658 */ sead::CriticalSection _1658;
    /* 0x1698 */ bool _1698;
    /* 0x169c */ sead::Vector3f _169c;
    /* 0x16a8 */ f32 _16a8;
    /* 0x16ac */ u8 _16ac[0x1700 - 0x16ac];
    /* 0x1700 */ sead::CriticalSection _1700;
    /* 0x1740 */ sead::Matrix34f _1740;
public:
    /* 0x1770 */ sead::Vector3f _1770;  // a position (Player::sub_7100892100, PlayerSuperJumpCharge)

protected:
    /* 0x177c */ u8 _177c[0x178c - 0x177c];
public:
    // Public: compared with _1770.y by PlayerFall::calc_.
    /* 0x178c */ f32 _178c;

protected:
    /* 0x1790 */ u8 _1790[0x17a0 - 0x1790];
    /* 0x17a0 */ sead::Vector3f _17a0;
    /* 0x17ac */ u8 _17ac[0x17d0 - 0x17ac];
public:
    /* 0x17d0 */ uking::Unk_710246d058* _17d0;  // controller (Player::initControllerMaybe)

protected:
    /* 0x17d8 */ u8 _17d8[0x17f0 - 0x17d8];
};
KSYS_CHECK_SIZE_NX150(PlayerBase, 0x17f0);

namespace acc {

// Read/write access to a PlayerBase through an ActorConstDataAccess (CSV: act::acc::PlayerBase).
// TODO: incomplete
class PlayerBase : public ActorConstDataAccess {
public:
    bool getPlayerFromPlayerInfo();
    bool isMainWeaponHitEnemy() const;
    // 0x710084d958 (declared only, CSV name `act::acc::PlayerBase::x_5`; lane2 s20: called by
    // RemainsFireRoot::calc_)
    bool x_5();

    void x_0(BaseProc* proc) const;
    void x_1(bool a, const sead::SafeString& name, BaseProc* proc) const;
    void setExtraEnergy(f32 energy) const;
    void setExtraLife(f32 life) const;
    void setMtx(const sead::Matrix34f& mtx) const;
    bool x_2() const;
    // 0x710084d54c / 0x710084d59c: const spelling follows the existing accessor convention.
    bool x_3() const;
    bool x_4() const;
    // 0x710084e0bc (CSV x_23)
    bool x_23() const;
    bool runeMgrCheckCanUseSquareBomb() const;  // CSV name (0x710084f3d4)
    bool getLastDamageAttacker(sead::BufferedSafeString* name) const;
    bool setRestartBuf(const sead::Vector3f& pos, f32 angle) const;
    bool isRidingThisSandSeal(BaseProc* proc) const;
    bool getSandSealActor(ActorConstDataAccess* accessor) const;
    bool getAttachedTargetActor(ActorConstDataAccess* accessor) const;
    bool reserveParashawlStart() const;
    const sead::Vector3f& getPosCopyMagnesis() const;
    const sead::Vector3f& getPosCopyMagnesis2() const;
    void getMaskType(sead::BufferedSafeString* out) const;
    void getArmorSeriesType(sead::BufferedSafeString* out) const;
    void getEnemyTeam(sead::BufferedSafeString* out) const;
    bool ArmorSeriesTypeStuff() const;
    bool armorSeriesStuff(u8 idx, const sead::SafeString& series) const;
    bool isEquipedDyedArmor() const;
    s32 getArmorDyeStuff() const;
    bool m280() const;
    bool x_14() const;
    bool m328() const;
    bool x_15() const;
    bool x_16() const;
    bool x_17() const;
    bool x_18() const;
    bool x_19() const;
    bool isClimbingStep() const;
    bool m212() const;
    bool m190() const;
    bool x_20() const;
    // 0x710084de94 (CSV name).
    bool x_21() const;
    f32 getBowSlowRateDiam() const;
    bool x_22() const;
    f32 getStopTimerReloadTime() const;
    f32 getStopTimerBlowAngle() const;
    f32 getStopTimerBlowSpeedLimit() const;
    s32 getStopTimerImpulseMaxCountSmallSword() const;
    s32 getStopTimerImpulseMaxCountLargeSword() const;
    s32 getStopTimerImpulseMaxCountSpear() const;
    f32 m232() const;
    bool setPlayerStateToUnequipAndWait() const;
    bool isNoStandSquat() const;
    bool forbidComebackMaybe() const;
    bool x_24() const;
    bool isBgCrossFoot() const;
    bool isBgCrossSlideFoot() const;
    bool isGroundForEvent() const;
    bool isHitRoof() const;
    bool isShieldRideOnGround() const;
    bool isNoShieldDamageFloor() const;
    bool isOnRaft() const;
    bool isOnIceMakerBlock() const;
    BaseProcLink& getSpAttackTarget() const;
    const sead::Vector3f& getLookAtPosForCamera() const;
    bool isSlowStartInterval() const;
    // 0x710084ead0 (CSV slowTimeStuff): false while time is slowed, otherwise whether the slow start interval flag
    // (_c4c bit 15) is clear.
    bool slowTimeStuff() const;
    // 0x710084e728: whether the character controller reports being in water (bit 2 of _116).
    bool isInWater() const;
    // 0x710084ef78: whether controller key 0x25 is pressed.
    bool checkControllerX() const;
    // 0x710084f35c / 0x710084f398.
    bool runeMgrCheckCanUseStasis() const;
    bool runeMgrCheckCanUseRoundBomb() const;
    bool x_25() const;
    bool x_26() const;
    bool x_27() const;
    bool x_28() const;
    f32 m301() const;
    bool m179() const;
    bool m180() const;
    bool m181() const;
    bool x_29() const;
    bool m182_213() const;
    bool m194() const;
    s32 m322() const;
    s32 m321() const;
    f32 getHitSlowRate() const;
    bool x_30() const;
    bool x_31() const;
    bool x_32() const;
    bool x_6() const;
    bool isRidingSandSeal() const;
    bool x_8() const;
    s32 x_9() const;
    bool x_10() const;
    f32 m248() const;
    bool m200() const;
    bool m226() const;
    bool x_11() const;
    bool x_12() const;
    bool x_13() const;
    bool m205() const;
    bool isRisingInAirMaybe() const;
    bool m186() const;
    bool groundedCheckStuff() const;
    bool m188() const;
    bool x_33() const;
    bool m199() const;
    bool x_34() const;
    bool m178() const;
    bool x_35() const;
    bool m191() const;
    bool x_36() const;
    bool x_37() const;
    bool m204() const;
    bool m193() const;
    bool x_7() const;
    bool m224() const;
    bool x_38() const;
    bool m302() const;
    bool x_39() const;
    bool x_40() const;
    s32 m297() const;
    s32 m298_271() const;
    bool x_41() const;
    bool m304() const;
    f32 m305() const;
    bool checkActionX() const;
    bool m185() const;
    bool checkActionX_0() const;
    bool checkActionX_1() const;
    bool x_42() const;
    bool m187() const;
    bool isRidingHorse() const;
    Actor* x_43() const;
    f32 m231() const;
    f32 x_44() const;

protected:
    act::PlayerBase* getPlayerBase() const;
};
KSYS_CHECK_SIZE_NX150(PlayerBase, 0x18);

}  // namespace acc

}  // namespace ksys::act
