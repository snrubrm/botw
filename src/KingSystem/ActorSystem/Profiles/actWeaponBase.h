#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace ksys::eco {
enum class WeaponModifier;
}

namespace ksys::act {

class InstParamPack;

// 0x0000007100ef2808
eco::WeaponModifier getRandomWeaponModifier(eco::WeaponModifier modifier,
                                            const sead::SafeString& actor_name);

// TODO
class WeaponBase : public Actor {
    SEAD_RTTI_OVERRIDE(WeaponBase, Actor)
public:
    bool areExtraActorsReady() const;

    // FIXME: figure out return types, parameters and names
    virtual Actor* getParentActor();
    virtual bool hasParentActor_() { return _938.hasProc(); }
    virtual bool hasParentActor() { return hasParentActor_(); }
    virtual bool isParentEqualToById(BaseProc* proc) { return _938.hasProcById(proc); }
    virtual bool isParentEqual(const BaseProcLink& link) { return _938 == link; }
    virtual bool m153() { return false; }
    // 0x7100ef5e3c: the actor linked at +0x938 passes ActorConstDataAccess::sub_7100D12E64.
    virtual bool m154();
    virtual bool m155() { return false; }
    virtual bool m156() { return false; }
    virtual bool isParentPlayer() { return false; }
    virtual bool isParentNpc() { return false; }
    virtual const sead::SafeString& m159() const;
    virtual const sead::SafeString& m160() const;
    virtual bool m161() { return _958.hasProc(); }
    // The OptionalWeapon linked at +0x958 (two getProc variants: m162 passes the other-proc argument).
    virtual Actor* m162();
    virtual Actor* m163();
    virtual const sead::SafeString& m164();
    virtual void m165();
    virtual void m166();
    virtual void m167();
    virtual void m168();
    virtual void m169();
    virtual void m170();
    virtual void m171();
    virtual void m172();
    virtual void m173();
    virtual void m174();
    // 0x7100ef61c4. Stores the position at _910 (+ _91c = -1, _920 = 2) and the three flags (a2 -> _924,
    // a3 -> _922, a5 -> _923) under _840; returns false if _925 is set. `a4` is an object of a class
    // whose RTTI is at 0x71025b1538 (Weapon::x_4 casts it; callers pass nullptr; the base ignores it).
    virtual bool m175(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5);
    virtual void m176();
    virtual void m177();
    virtual void m178();
    virtual void m179();
    virtual void m180();
    virtual void m181() {}
    virtual bool m182();
    virtual bool m183() { return false; }
    virtual bool m184() { return false; }
    // Public accessors for the two fields Enemy::m141 reads directly (inline-only in the original).
    u8 get920() const { return _920; }
    bool get921() const { return _921; }
    virtual bool m185() { return _920 == 0; }
    virtual bool m186() { return _921; }
    virtual bool m187() { return _925; }
    virtual bool m188() { return _920 == 1; }
    virtual bool m189() { return _920 == 2; }
    virtual bool m190() { return _920 == 3; }
    virtual bool m191() { return _920 == 4; }
    virtual bool m192() { return _922; }
    virtual bool m193() { return _923; }
    virtual bool m194() { return false; }
    virtual bool m195() { return false; }
    virtual bool m196();
    virtual bool m197();
    virtual void m198();
    virtual void m199();
    virtual void m200();
    virtual void m201();
    virtual void m202(bool on) { _9f4.change(1, on); }
    virtual bool m203() { return _9f4.isOn(1); }
    virtual bool m204() { return false; }
    virtual bool m205() { return false; }
    virtual void m206();
    virtual void m207();
    virtual void m208();
    virtual void m209();
    virtual bool m210() { return false; }
    virtual bool m211() { return false; }
    virtual bool m212() { return false; }
    virtual bool m213() { return false; }
    virtual bool m214() { return true; }
    virtual void m215() {}
    virtual bool m216() { return false; }
    virtual bool m217();
    virtual bool m218() { return false; }
    virtual bool isMasterSword() { return false; }
    virtual void masterSwordReturnToForest() {}
    virtual void m221();
    virtual bool m222() { return false; }
    virtual bool m223();
    virtual void m224(sead::Vector3f* out) { *out = sead::Vector3f::ones; }
    virtual bool m225() { return false; }
    virtual bool m226() { return false; }
    virtual bool m227() { return false; }
    virtual void m228() {}
    virtual void m229() {}
    virtual bool isWeaponType0Or1Or2() const;
    virtual bool m231() const;
    virtual bool m232() const;
    virtual bool m233() const;
    virtual bool isWeaponType4() const;
    virtual bool isWeaponType3() const;
    virtual bool isBoomerang() { return false; }
    virtual void m237();
    virtual void m238();
    virtual bool m239() { return false; }
    virtual void m240();
    virtual void m241();
    virtual void m242();
    virtual void m243();
    virtual void m244();
    virtual void m245();
    virtual void m246();
    virtual void m247();
    virtual void m248();
    virtual void m249();
    virtual bool m250();

    static void requestCreateWeaponActor(const char* actor, const sead::Matrix34f& matrix,
                                         f32 scale, sead::Heap* heap,
                                         ksys::act::BaseProcHandle* handle, s32 life,
                                         ksys::act::InstParamPack* params, s32 task_lane_id);

protected:
    // TODO
    sead::CriticalSection _840;
    BaseProcLink _880;
    BaseProcLink _890;
    sead::FixedSafeString<32> _8a0;
    sead::FixedSafeString<32> _8d8;
    u8 _910[0x920 - 0x910];
    u8 _920;
    bool _921;
    bool _922;
    bool _923;
    u8 _924;
    bool _925;
    u8 _926[0x938 - 0x926];
    BaseProcLink _938;
    BaseProcLink _948;
    BaseProcLink _958;
    sead::FixedSafeString<32> _968;
    sead::FixedSafeString<32> _9a0;
    u8 _9d8[0x9f4 - 0x9d8];
    sead::BitFlag8 _9f4;
    u8 _9f5[0xaa0 - 0x9f5];
    BaseProcHandle mExtraActorHandle;
    u8 _ab0;
};
KSYS_CHECK_SIZE_NX150(WeaponBase, 0xab8);

}  // namespace ksys::act
