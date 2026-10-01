#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace ksys::act {

class ActorConstDataAccess;

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

    // FIXME: name for x
    void setExtraLife(s32 extra_life, f32 x);

    bool m140() override { return _cf0.isOnBit(25) || m180(); }

    // FIXME: figure out return types, parameters and names
    /* 177 */ bool isRidingHorse() override;
    /* 178 */ bool m178() override { return _c40.isOnBit(1); }
    /* 179 */ void m179() override;
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
    /* 228 */ virtual void m228();
    /* 229 */ virtual void m229() {}
    /* 230 */ virtual bool m230() { return false; }
    /* 231 */ virtual f32 m231() { return 1.0f; }
    /* 232 */ virtual f32 getAncientAttackRate() { return 1.0f; }
    /* 233 */ virtual f32 m233(int) { return 1.0f; }
    /* 234 */ virtual bool m234() { return false; }
    /* 235 */ virtual f32 m235() { return 0.0f; }
    /* 236 */ virtual f32 getBoneAttackRate() { return 1.0f; }
    /* 237 */ void m237() override;
    /* 238 */ void m238() override;
    /* 239 */ void m239() override;
    /* 240 */ void m240() override;
    /* 241 */ virtual bool m241() { return true; }
    /* 242 */ virtual bool m242() { return false; }
    /* 243 */ virtual bool m243() { return false; }
    /* 244 */ virtual const sead::Vector3f& m244() { return sead::Vector3f::zero; }
    /* 245 */ virtual const sead::Vector3f& m245() { return sead::Vector3f::zero; }
    /* 246 */ virtual const sead::Vector3f& getPosCopyMagnesis() { return sead::Vector3f::zero; }
    /* 247 */ virtual const sead::Vector3f& m247() { return sead::Vector3f::zero; }
    /* 248 */ virtual f32 m248() { return 0.0f; }
    /* 249 */ virtual bool m249() { return false; }
    /* 250 */ virtual const sead::Vector3f& m250() { return sead::Vector3f::zero; }
    /* 251 */ virtual const sead::Vector3f& m251() { return sead::Vector3f::zero; }
    /* 252 */ virtual const sead::Vector3f& m252() { return sead::Vector3f::zero; }
    /* 253 */ virtual const sead::Vector3f& m253() { return sead::Vector3f::zero; }
    /* 254 */ virtual bool m254() { return false; }
    /* 255 */ virtual const sead::Vector3f& m255() { return sead::Vector3f::zero; }
    /* 256 */ virtual bool m256() { return false; }
    /* 257 */ virtual bool m257() { return false; }
    /* 258 */ virtual void m258();
    /* 259 */ void m259() override { _c50.setBit(22); }
    /* 260 */ virtual bool m260() { return false; }
    /* 261 */ virtual void m261();
    /* 262 */ bool isGroundForEvent() override;
    /* 263 */ void getAttachedTargetActor2() override;
    /* 264 */ void getAttachedTargetActor() override;
    /* 265 */ virtual const sead::Vector3f& m265() { return sead::Vector3f::zero; }
    /* 266 */ virtual void m266();
    /* 267 */ virtual void m267();
    /* 268 */ virtual bool m268() { return false; }
    /* 269 */ virtual bool m269() { return false; }
    /* 270 */ virtual bool m270() { return false; }
    /* 271 */ virtual s32 m271() { return _d24; }
    /* 272 */ void m272() override;
    /* 273 */ void m273() override;
    /* 274 */ void m274() override;
    /* 275 */ void m275() override;
    /* 276 */ void m276() override;
    /* 277 */ virtual void m277(ActorConstDataAccess* accessor, int idx) {}
    /* 278 */ virtual void m278();
    /* 279 */ virtual bool getArmorDyeStuff() { return false; }
    /* 280 */ virtual bool m280() { return false; }
    /* 281 */ virtual bool isEquipedDyedArmor() { return false; }
    /* 282 */ virtual void getArmorSeriesType(sead::BufferedSafeString* out) {}
    /* 283 */ virtual void getEnemyTeam(sead::BufferedSafeString* out) {}
    /* 284 */ virtual bool ArmorSeriesTypeStuff() { return false; }
    /* 285 */ virtual void armorSeriesStuff();
    /* 286 */ virtual void getMaskType(sead::BufferedSafeString* out) {}
    /* 287 */ virtual bool m287() { return false; }
    /* 288 */ virtual bool m288() { return false; }
    /* 289 */ virtual bool m289() { return false; }
    /* 290 */ virtual bool m290() { return false; }
    /* 291 */ virtual bool m291() { return false; }
    /* 292 */ bool m292() override { return _c40.isOnBit(31); }
    /* 293 */ virtual void m293();
    /* 294 */ virtual void m294();
    /* 295 */ virtual bool m295() { return false; }
    /* 296 */ virtual bool m296() { return false; }
    /* 297 */ virtual s32 m297() { return 0; }
    /* 298 */ virtual bool m298() { return false; }
    /* 299 */ bool m299() override { return _c44.isOnBit(2); }
    /* 300 */ virtual f32 m300() { return 1.0f; }
    /* 301 */ virtual f32 m301() { return 1.0f; }
    /* 302 */ virtual bool m302() { return false; }
    /* 303 */ virtual bool m303() { return false; }
    /* 304 */ virtual bool m304() { return false; }
    /* 305 */ virtual f32 m305() { return 0.0f; }
    /* 306 */ bool m306() override { return false; }
    /* 307 */ void m307() override;
    /* 308 */ void m308() override;
    /* 309 */ virtual void m309(f32) {}
    /* 310 */ virtual void m310(f32) {}
    /* 311 */ virtual void m311();
    /* 312 */ virtual s32 m312(int idx);
    /* 313 */ void getActorDirect() override;
    /* 314 */ void m314() override;
    /* 315 */ void m315() override { m139(); }
    /* 316 */ f32 m316() override { return _1654; }
    /* 317 */ f32 m317() override;
    /* 318 */ virtual void m318();
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
    /* 357 */ virtual void m357();
    /* 358 */ void m358() override;
    /* 359 */ virtual bool m359() { return false; }

protected:
    /* 0xc40 */ sead::BitFlag32 _c40;
    /* 0xc44 */ sead::BitFlag32 _c44;
    /* 0xc48 */ sead::BitFlag32 _c48;
    /* 0xc4c */ sead::BitFlag32 _c4c;
    /* 0xc50 */ sead::BitFlag64 _c50;
    /* 0xc58 */ u8 _c58[0xcec - 0xc58];
    /* 0xcec */ sead::BitFlag32 _cec;
    /* 0xcf0 */ sead::BitFlag32 _cf0;
    /* 0xcf4 */ sead::BitFlag32 _cf4;
    /* 0xcf8 */ sead::BitFlag32 _cf8;
    /* 0xcfc */ u8 _cfc[0xd24 - 0xcfc];
    /* 0xd24 */ s32 _d24;
    /* 0xd28 */ u8 _d28[0xe58 - 0xd28];
    /* 0xe58 */ f32 _e58;
    /* 0xe5c */ u8 _e5c[0x1654 - 0xe5c];
    /* 0x1654 */ f32 _1654;
    /* 0x1658 */ u8 _1658[0x17f0 - 0x1658];
};
KSYS_CHECK_SIZE_NX150(PlayerBase, 0x17f0);

}  // namespace ksys::act
