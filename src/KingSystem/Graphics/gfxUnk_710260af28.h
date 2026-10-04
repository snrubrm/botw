#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>

namespace gsys {
class Model;
}

// Placeholder name: an unnamed model effects manager (instance pointer 0x710260af28; its methods are
// in 0x7100f1e100 - 0x7100f1f000, e.g. the CSV names uk_proc_discard_stuff / uk_damage_color_stuff;
// ~56 callers: Weapon, Horse, Swarm, MoonMove, GanonBeastRoot, ...). Declaration only (lane4 s23).
class Unk_710260af28 {
public:
    static Unk_710260af28* instance() { return sInstance; }

    // 0x7100f1cd88 / 0x7100f1ce68: preserves the model's material user data and object attribute.
    u64 sub_7100F1CD88(gsys::Model* model);
    f32 sub_7100F1CE68(gsys::Model* model);
    // 0x7100f1cc38 / 0x7100f1cef4: restores them after clearing material animation.
    void sub_7100F1CC38(gsys::Model* model, u64 value);
    void sub_7100F1CEF4(gsys::Model* model, f32 value);

    // 0x7100f1ece8: clears bit 2 of the flags halfword (+0x12) of every element of the model's list.
    void sub_7100F1ECE8(gsys::Model* model);
    // 0x7100f1ed28 (declaration only; lane2 s21): calls the unnamed 0x7100f1ed8c with every element of the
    // model's list and `a2` (SunAI::enter_ passes false).
    void sub_7100F1ED28(gsys::Model* model, bool a2);
    // 0x7100f1e2f4 (CSV: uk_damage_color_stuff; declaration only; lane4 s28): HorseReins::initMaybe
    // passes a zeroed 16 byte value (a colour) by reference.
    void sub_7100F1E2F4(gsys::Model* model, const sead::Color4f& color);
    // 0x7100f1e1f8 (CSV: uk_proc_discard_stuff; declaration only; lane4 s31): Actor::x_3 calls it with the actor's model
    // after changing `_4f4`.
    void sub_7100F1E1F8(gsys::Model* model);
    // 0x7100f1eaf8 (declaration only; lane4 s28): HorseReins::initMaybe passes 0.0.
    void sub_7100F1EAF8(gsys::Model* model, f32 value);
    // 0x7100f1e8a4 (declaration only): scene661a58 passes the ingredient model and opacity value.
    void sub_7100F1E8A4(gsys::Model* model, f32 value);

private:
    static Unk_710260af28* sInstance;
};
