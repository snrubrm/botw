#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys {
class SeadController;
}

namespace uking::act {
class Weapon;
}

namespace ksys::act {

class Actor;
class ActorLinkConstDataAccess;
class PlayerBase;
class Unk_71024ef4e8;

// Interface implemented by the player actor (PlayerBase is-a PlayerLink at offset 0xc38;
// see ksys::setPlayerLink). Its vtable has 83 slots and no destructor.
//
// Slots overridden by PlayerBase are pure here. They are named after the PlayerBase vtable slot
// of the overrider (or the CSV name); the default implementations of the other slots are named
// after the Player vtable slot of their overrider when there is one.
// FIXME: figure out return types, parameters and names
class PlayerLink {
public:
    /*  0 */ virtual bool getActorViaAccessor(ActorLinkConstDataAccess* accessor) = 0;
    /*  1 */ virtual SeadController* m358() = 0;
    /*  2 */ virtual void m2() {}
    /*  3 */ virtual void m3() {}
    /*  4 */ virtual void m4() {}
    /*  5 */ virtual void m379();
    /*  6 */ virtual void m380();
    /*  7 */ virtual void m381();
    /*  8 */ virtual void getArmorPartName(u8 idx, sead::BufferedSafeString* out) = 0;
    /*  9 */ virtual uking::act::Weapon* m273() = 0;
    /* 10 */ virtual uking::act::Weapon* m274() = 0;
    /* 11 */ virtual uking::act::Weapon* m275() = 0;
    /* 12 */ virtual Actor* m276(int idx) = 0;
    /* 13 */ virtual Unk_71024ef4e8* getAttachedTargetActor2() = 0;
    /* 14 */ virtual Unk_71024ef4e8* getAttachedTargetActor() = 0;
    /* 15 */ virtual Actor* m382();
    /* 16 */ virtual bool m378() { return false; }
    /* 17 */ virtual bool m17() { return false; }
    /* 18 */ virtual bool isRidingHorse() = 0;
    /* 19 */ virtual bool m178() = 0;
    /* 20 */ virtual bool m200() = 0;
    /* 21 */ virtual bool isGroundForEvent() = 0;
    /* 22 */ virtual bool m202() = 0;
    /* 23 */ virtual bool m199() = 0;
    /* 24 */ virtual bool m184() = 0;
    /* 25 */ virtual bool m179() = 0;
    /* 26 */ virtual bool m188() = 0;
    /* 27 */ virtual bool m194() = 0;
    /* 28 */ virtual bool m196() = 0;
    /* 29 */ virtual bool m203() = 0;
    /* 30 */ virtual bool m187() = 0;
    /* 31 */ virtual bool m197() = 0;
    /* 32 */ virtual bool m191() = 0;
    /* 33 */ virtual f32 m192() = 0;
    /* 34 */ virtual void m377() {}
    /* 35 */ virtual bool m383() { return false; }
    /* 36 */ virtual f32 m360() { return 1.0f; }
    /* 37 */ virtual bool m237() = 0;
    /* 38 */ virtual bool m238() = 0;
    /* 39 */ virtual bool m239() = 0;
    /* 40 */ virtual bool m240() = 0;
    /* 41 */ virtual bool m292() = 0;
    /* 42 */ virtual bool m221() = 0;
    /* 43 */ virtual bool m222() = 0;
    /* 44 */ virtual void m223() = 0;
    /* 45 */ virtual bool m299() = 0;
    /* 46 */ virtual bool m209() = 0;
    /* 47 */ virtual bool m210() = 0;
    /* 48 */ virtual bool m211() = 0;
    /* 49 */ virtual void m369(int) {}
    /* 50 */ virtual void m370(f32) {}
    /* 51 */ virtual void m371(f32) {}
    /* 52 */ virtual void m372() {}
    /* 53 */ virtual bool m306() = 0;
    /* 54 */ virtual bool m374() { return false; }
    /* 55 */ virtual bool m375() { return false; }
    /* 56 */ virtual bool m204() = 0;
    /* 57 */ virtual bool m206() = 0;
    /* 58 */ virtual bool hasFairy() { return false; }
    /* 59 */ virtual bool m185() = 0;
    /* 60 */ virtual bool m186() = 0;
    /* 61 */ virtual f32 m364() { return 1.0f; }
    /* 62 */ virtual void m259() = 0;
    /* 63 */ virtual void m366() {}
    /* 64 */ virtual void showCannotGoAnyFarther() {}
    /* 65 */ virtual void showCannotGoAnyFarther2() {}
    /* 66 */ virtual bool m365() { return false; }
    /* 67 */ virtual bool m376() { return false; }
    /* 68 */ virtual bool m373() { return false; }
    /* 69 */ virtual bool m220() = 0;
    /* 70 */ virtual sead::Vector3f& getPlayerPosForPostCalc() = 0;
    /* 71 */ virtual void getActorDirect() = 0;
    /* 72 */ virtual void m308() = 0;
    /* 73 */ virtual f32 m319() = 0;
    /* 74 */ virtual void m314() = 0;
    /* 75 */ virtual void m315() = 0;
    /* 76 */ virtual f32 m316() = 0;
    /* 77 */ virtual f32 m317() = 0;
    /* 78 */ virtual bool m353() = 0;
    /* 79 */ virtual void m307() = 0;
    /* 80 */ virtual int m384() { return 0; }
    /* 81 */ virtual int m385() { return 0; }
    /* 82 */ virtual PlayerBase* getPlayer() = 0;
};

}  // namespace ksys::act
