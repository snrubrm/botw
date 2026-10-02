@AGENTS.md

# Claude sessions in this fork

- Work happens on the integration branch `decomp`; parallel lanes work in worktrees `~/Repos/botw-lanes/laneN` on
  branches `laneN`, driven by `~/botw-tools/prompts/laneN.md`. A coordinator session cherry-picks lane commits onto
  `decomp` (`~/botw-tools/harvest.sh`) and resets lanes between sessions — lanes don't merge `decomp` themselves.
- Work outside a lane's own queue (helper TUs, shared classes) is claimed in `~/botw-tools/claims.md` first.
- Shared knowledge: `~/botw-tools/research/TIPS.md`; per-lane logs `~/botw-tools/research/laneN-log.md`.
- Never use `git stash` in worktrees (the stash is shared); use WIP commits.
