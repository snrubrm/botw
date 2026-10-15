#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>

namespace gsys {
class Model;
class ModelUnit;
}

// Placeholder name: an unnamed model effects manager (instance pointer 0x710260af28; its methods are
// near 0x7100f1c77c - 0x7100f1f000, e.g. the CSV names uk_proc_discard_stuff / uk_damage_color_stuff;
// ~56 callers: Weapon, Horse, Swarm, MoonMove, GanonBeastRoot, ...). The remaining state is opaque.
class Unk_710260af28 {
public:
    static Unk_710260af28* instance() { return sInstance; }

    // Actor forwards its stasis mask and an optional opaque actor record address.
    void sub_7100F1D058(gsys::Model* model, u32 flags);
    void sub_7100F1C77C(gsys::Model* model, const void* user_data);
    // Complete native callees operate on one unit / material; their bodies remain U.
    void sub_7100F1D0BC(gsys::ModelUnit* unit, u32 flags);
    void sub_7100F1C824(gsys::ModelUnit* unit, s32 material, const void* user_data);
    // Complete native F1DFF0 clamps opacity and updates one material; body remains U.
    void sub_7100F1DFF0(gsys::ModelUnit* unit, s32 material, f32 opacity, bool fade);

    // 0x7100f1cd88 / 0x7100f1ce68: preserves the model's material user data and object attribute.
    u64 sub_7100F1CD88(gsys::Model* model);
    f32 sub_7100F1CE68(gsys::Model* model);
    // 0x7100f1cc38 / 0x7100f1cef4: restores them after clearing material animation.
    void sub_7100F1CC38(gsys::Model* model, u64 value);
    // 0x7100f1cacc: changes the material flag selected by Actor's bit 11.
    void sub_7100F1CACC(gsys::Model* model, bool on);
    // 0x7100f1dca8: applies the model opacity to each model unit, with the fade flag.
    void sub_7100F1DCA8(gsys::Model* model, f32 opacity, bool fade);
    void sub_7100F1CEF4(gsys::Model* model, f32 value);

    // 0x7100f1ece8: clears bit 2 of the flags halfword (+0x12) of every element of the model's list.
    void sub_7100F1ECE8(gsys::Model* model);
    // Forwards the numeric render mode to every model unit (SunAI::enter_ passes 0).
    void sub_7100F1ED28(gsys::Model* model, int mode);
    // Full F1ED8C handles numeric modes; ForestRenderer also calls it for one unit.
    void sub_7100F1ED8C(gsys::ModelUnit* unit, int mode);
    // 0x7100f1e2f4 (CSV: uk_damage_color_stuff; declaration only; lane4 s28): HorseReins::initMaybe
    // passes a zeroed 16 byte value (a colour) by reference.
    void sub_7100F1E2F4(gsys::Model* model, const sead::Color4f& color);
    // 0x7100f1e1f8 (CSV: uk_proc_discard_stuff; declaration only; lane4 s31): Actor::x_3 calls it with the actor's model
    // after changing `_4f4`.
    void sub_7100F1E1F8(gsys::Model* model);
    // 0x7100f1eaf8 (declaration only; lane4 s28): HorseReins::initMaybe passes 0.0.
    void sub_7100F1EAF8(gsys::Model* model, f32 value);
    // Bullet and GolemRootBase pass their model and an unsigned value converted to float.
    void sub_7100F1E4DC(gsys::Model* model, f32 value);
    // 0x7100f1e8a4 (declaration only): scene661a58 passes the ingredient model and opacity value.
    void sub_7100F1E8A4(gsys::Model* model, f32 value);
    // 0x7100f1ebf0 (declaration only): ItemRoot::enter_ passes the actor's model.
    void sub_7100F1EBF0(gsys::Model* model);

private:
    static Unk_710260af28* sInstance;
};
