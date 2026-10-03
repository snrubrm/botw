# Agent guide for this fork

This is a **private fork** (`snrubrm/botw`) of the Breath of the Wild decompilation (Switch v1.5.0, Clang 4.0.1,
AArch64). It is never merged upstream.

- Never open upstream PRs, post code to decomp.me, Discord or anywhere else, or suggest doing so.
- No AI attribution of any kind in commits or PR descriptions (no `Co-Authored-By`, no "Generated with", no model
  disclosure).
- Don't push or rewrite pushed history unless the user asks.

# Building and checking

- Build: `ninja -C build` (or `/home/snrub/botw-tools/bin/lb` from inside a worktree — shared ccache, `-j4`).
- Check one function: `./tools/check <mangled-or-demangled name>`. It prints OK or an asm diff and **rewrites that
  function's status in `data/uking_functions.csv`**. A full `./tools/check` must print OK before every commit; it also
  rewrites statuses of everything that currently matches, so review `git diff data/uking_functions.csv`.
- `tools/check` does not compare string literal contents, literal-pool values (floats) or unlisted data references.
  Before committing also run, from the repo root:
  - `/home/snrub/botw-tools/bin/strcheck <base commit>` — every added string literal must exist in the original.
  - `/home/snrub/botw-tools/bin/datarefs` — data references, vtables and constants vs the original; must exit 0.
    Known/accepted issues live in `/home/snrub/botw-tools/datarefs-known.txt`.
  - `/home/snrub/botw-tools/bin/rodatacheck` — values of read-only constants (floats, vectors, integer literals)
    loaded by matched functions; must report 0 mismatches.
  - `/home/snrub/botw-tools/bin/gate <base commit>` runs the build and all four checks and prints `GATE OK`.
- Original asm: `/home/snrub/botw-tools/bin/fnasm <name|0xaddr>`; strings/u64 at an address:
  `/home/snrub/botw-tools/bin/fstr <vaddr> | q:<vaddr>`; Ghidra pseudo-C:
  `/home/snrub/botw-tools/research/ghidra-c/<address>.c`.
- When you identify a global, vtable or RTTI object, add `<address>,<mangled name>` to `data/data_symbols.csv`
  (sorted; the first line is a header) so `tools/check` verifies references to it.

# Function list

`data/uking_functions.csv` is the symbol map: `Address,Quality,Size,Name` with Quality O (matching), m (minor
mismatch), M (major), W (stub/WIP), U (undecompiled), L (library). A function matches only if our build defines its
exact mangled name, so when you give a placeholder entry (`Class::m34`, `AI_AI_X::ctor`, an informal IDA name) its real
signature, rename the CSV entry to the new mangled symbol — also for functions that are declared but not defined yet,
or their callers can't match.

# Matching rules (the user rejects workarounds — honest non-matching beats a hack)

Write plausible original source. Never use:

- inline asm (including `asm("")` barriers);
- `goto` only to steer codegen;
- invented globals, helpers or stand-in functions;
- pointer punning (`*(T*)&x`, `reinterpret_cast` struct overlays);
- casts that only change codegen;
- register-steering locals;
- invented calls (calls that are not in the target asm);
- self-assignments, `volatile`;
- pragmas, attributes or compiler flags without evidence.

Allowed, with evidence:

- A call whose result is discarded, when that call really is in the target asm. Log it.
- A cast, local or inline helper when natural code would contain it, or when matched human-written code (this repo,
  sead/agl, other Nintendo decomps) uses the same form in the same situation.
- A named local for a value used more than once, or holding a getter's by-value result, or copied straight from a
  parameter (`const T x = *mParam_s;`) even if used once.
- An inline-only helper (the original has no out-of-line copy) when the same inlined sequence repeats in several
  functions. Mark it `// inline-only in the original; name is a guess` with the evidence, and log it.
- `{ ; }` as a destructor body where the original keeps the vtable store a defaulted dtor drops (precedent: upstream's
  `GameDataFlagSelector::~GameDataFlagSelector() { ; }`, commit 96101229). Comment it.

If only a trick makes a function match: keep the natural version, mark it `m`/`M` in the CSV, add
`// NON_MATCHING: <reason>` above it, and record the trick as "borderline" for the user to decide. Decisions and the
review backlog are in `/home/snrub/botw-tools/research/decisions.md` and `REVIEW.md`.

# Names

Real names come first: names from the CSV's mangled symbols, existing headers, aidef/status data (`data/*.yml`),
strings in the binary, RTTI, or sead/agl/NintendoSDK headers. Never replace one of those with a guess.

Descriptive names are allowed (user decision 2026-10-03, as in other decomps) when you understand what the thing
does from the code — what it reads and writes, its callers and callees, nearby strings. Follow the codebase's style
(`mCamelCase` members, `camelCase` methods, `PascalCase` classes, `sCamelCase` globals). If you are unsure, add the
upstream hedge suffix `Maybe` (`crashMaybe`, `getHorseOptionsMaybe`) or keep a placeholder: `mNN` (virtual slot),
`sub_<ADDR>` (function), `_xx` (field at offset xx), `Unk_<vtable or ctor address>` (class), `sUnk_<address>` (global).

Renaming something that already has a name elsewhere in the tree (a placeholder in a shared header, a CSV entry other
code uses) is done only by the lane that owns that class, and is logged, so parallel lanes don't collide.

# Code style

- No assembly or disassembly in code, comments or commit messages.
- Follow the surrounding code's naming and formatting (`.clang-format`).
- Keep class sizes and offsets right; add `KSYS_CHECK_SIZE_NX150` when you learn a size.
- Shared headers (Actor, ActionBase, listener/sender headers, ...): additive edits; grep for an existing declaration
  before adding one.
- Don't edit `lib/` (submodules) or tooling.

# Commits

One class (or one logical batch) per commit, subject like `Decompile <class>` / `Match <class>::<fn>`, body listing
what matches and what is left non-matching. Stage specific files. No AI attribution lines.
