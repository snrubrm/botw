#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::xlink {
class XLink;
}

struct DamageReactionRequest;

namespace ksys::act {
class Actor;
class BaseProcLink;

// Placeholder name: an actor given either directly or through a proc link (the reaction code keeps one at
// +0xa8 of its request objects; 0x7100ec545c / 0x7101284954 read it). Accessors 0x7100ebf9e4..0x7100ebfad4.
struct Unk_7100ebf9e4 {
    xlink::XLink* getXLink() const;
    // Chemical::_c0 of the actor's chemical (0 if none).
    s32 getChemicalState() const;
    const sead::SafeString& getName() const;

    Actor* mActor;
    BaseProcLink* mLink;
};

// Partial declaration. Reaction::createInstance (0x7100ec0138) stores the
// singleton at 0x71026064c0; its 0x180-byte allocation and members remain unrecovered.
class Reaction {
public:
    // Placeholder: the object at _a8 (class unknown). 0x7100ec66fc sets its _110 to 2; the actor
    // argument is unused. Called by OctarockOptionRoot::calc_ when the player touches the rock.
    struct Unk1 {
        void sub_7100EC66FC(Actor* actor);
        // Constant getters (0.7f / 7 / 5); placeholder names.
        f32 sub_7100EC877C() const;
        s32 sub_7100EC87A4() const;
        s8 sub_7100EC89BC() const;

        u8 _0[0x110];
        /* 0x110 */ s32 _110;
    };

    static Reaction* instance() { return sInstance; }
    // 0x7100ec10b8 (CSV __auto6): passes `request` on to the reaction targets when the instance's
    // +0xb0 flag is set (bits 2 / 1 of request->_c4 select 0x7101284954 / 0x7100ec313c); true.
    bool sub_7100EC10B8(::DamageReactionRequest* request);
    static Reaction* sInstance;
    // Surface raycast/XLink update called by GolemRootBase::calc_; declaration only.
    void sub_7100EC29D0(Actor* actor);
    // 0x7100ec2278 (placeholder name): size class 0-4 of the actor from the local AABB of its main body
    // (2 or 3 from the height alone without one). `is_long` (optional) is set when the body is longer than
    // 4.5 and much thinner in the other two directions.
    s32 sub_7100EC2278(Actor* actor, bool* is_long);

    // EC04D0 stores an Actor cast from the released handle; EC0D20 deletes the same actor.
    // EC04D0 releases the first handle and dynamically casts it to Actor here.
    u8 _0[0x28];
    Actor* _28;
    Actor* _30;
    Actor* _38;
    u8 _40[0xa8 - 0x40];
    Unk1* _a8;
};
}  // namespace ksys::act
