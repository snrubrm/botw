#pragma once

namespace sead {
class Heap;
}

namespace ksys {
namespace act {
class PlayerLink;
}

struct InitParams {
    sead::Heap* king_sys_heap;
};

// 0x0000007100f3a4e4
bool isGameOver();
// 0x0000007100f3a4f0
void setIsGameOver(bool is_game_over);

void initBaseProcMgr(sead::Heap* heap);

// 0x0000007100f3a8d8
void preInitializeApp(const InitParams& params);

// 0x0000007100f3b1bc: true while the starter packs, the layout fonts / version or the DLC version
// parsing are not ready yet.
bool checkPreInitializeResourcesStillLoading();

// 0x0000007100f40370
void setPlayerLink(act::PlayerLink* link);

// 0x7100F40B3C stores the caller's demo-name pointer; TitleStage passes a string literal.
void setStartingDemoName(const char* name);

// 0x7100f3ed80 / 0x7100f3ee94 (placeholder names): forward to the placement manager and the world
// manager when they exist.
// 0x7100f3ed50 (placeholder name): calls the UI handler 0x7102606a90 unless ActorDebug exists without flag 0x200000.
// Per-frame calc steps run by the MCMgr jobs (declared only).
void CalcQuestAndEventAndActorDeleteOrPreload();
void CalcWorldMgr();
void CalcParticleAndBaseProcMgr();
void CalcPlayReportAndStatsMgr();
void CalcAttentionAndVibration();
void CalcView1();
// 0x7100f3ed98 / 0x7100f41a54: the placement manager's per-frame calc and its thunk.
void CalcPlacementMgr();
void callCalcPlacementMgr();
// 0x7100f419dc / 0x7100f41a18 / 0x7100f41acc (placeholder names): run one of the placement
// manager's per-frame steps when it exists.
void sub_7100F419DC();
void sub_7100F41A18();
void sub_7100F41ACC();
// 0x7100f41c7c (placeholder name): the world manager's LOD step, gated on an ActorDebug flag.
void sub_7100F41C7C();

void sub_7100F3ED50();
void sub_7100F3ED80();
void sub_7100F3EE94();
// 0x7100f3f00c (placeholder name): the flag set by setInitBeforeStageGenDone (initially true).
bool sub_7100F3F00C();

// 0x0000007100f40428: stores `camera` (a Camera actor pointer or null) in the camera-using singletons.
void sub_7100F40428(void* camera);

}  // namespace ksys

// 0x7100f40360 (CSV name; global namespace).
void setInitBeforeStageGenDone(bool done);
