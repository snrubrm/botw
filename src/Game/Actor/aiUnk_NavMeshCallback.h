#pragma once

// Interface of the path-query callbacks of the nav mesh code (name unknown). It has no vtable of its own in the
// binary: the vtables of its two known implementations (Unk_71023e7178 in aiEnemyEscapeMove.h, vtable 0x71023e7178,
// and the group at 0x710243c238 next to GameSceneSubsys4's Unk_710243c208) hold their own m0 (0x7100389680 /
// 0x710066a30c) followed by the shared defaults m1 (0x710038aca8: returns null) and m2 (0x710038acb0: returns true).
// Placeholder name.
class Unk_NavMeshCallback {
public:
    // Visits one node of the query (the parameter type is unknown: a pointer to the node).
    virtual bool m0(const void* node) = 0;
    virtual void* m1();
    virtual bool m2();
};
