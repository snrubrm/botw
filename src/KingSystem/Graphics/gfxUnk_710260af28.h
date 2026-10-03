#pragma once

namespace gsys {
class Model;
}

// Placeholder name: an unnamed model effects manager (instance pointer 0x710260af28; its methods are
// in 0x7100f1e100 - 0x7100f1f000, e.g. the CSV names uk_proc_discard_stuff / uk_damage_color_stuff;
// ~56 callers: Weapon, Horse, Swarm, MoonMove, GanonBeastRoot, ...). Declaration only (lane4 s23).
class Unk_710260af28 {
public:
    static Unk_710260af28* instance() { return sInstance; }

    // 0x7100f1ece8: clears bit 2 of the flags halfword (+0x12) of every element of the model's list.
    void sub_7100F1ECE8(gsys::Model* model);

private:
    static Unk_710260af28* sInstance;
};
