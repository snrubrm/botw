# The Legend of Zelda: Breath of the Wild

This is a personal fork of [zeldaret/botw](https://github.com/zeldaret/botw). Most of the decompilation here is the great work of the zeldaret contributors, and full credit goes to them. I was curious how far AI-assisted decompilation could take the rest of the game, so this fork is where I've been trying that out. Nothing here is submitted upstream.

Feel free to use this repository, or not; if you'd rather work only from human-written code, use [zeldaret/botw](https://github.com/zeldaret/botw) instead.

This is an experimental, WIP decompilation of *The Legend of Zelda: Breath of the Wild* v1.5.0 (Switch).

**This repository does not contain game assets or RomFS content and *cannot* be used to play *Breath of the Wild*.**

The goal of this project is to better understand game internals, aid with glitch hunting and document existing knowledge in a permanent, unambiguous form which helps further reverse engineer the game.

## Progress

Functions marked matching in `data/uking_functions.csv` (byte-identical to the original after compilation):

| | Matching functions | Code size |
|---|---|---|
| zeldaret/botw at the fork point | 32,071 / 113,490 (28.26%) | 15.51% |
| This fork | 42,644 / 113,490 (37.58%) | 18.73% |

For more information about the original project, see https://botw.link
