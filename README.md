# RedPoint [![Cyber - Stuff](https://img.shields.io/badge/Cyber-Stuff-indianred)](https://13-05.github.io)
Have you ever wanted a tool to exploit multiple services? A single program to perform all the cool programming stuff you need? Well, that's what RedPoint aims to be.

## About
RedPoint rose from my need of a better, more stable, and more powerful version of [dsc.red](https://github.com/13-05/discord.RED). So, I archived *dsc.red*, and started from scratch. One command at a time.

## What's With the Name, Anyway?
- `redpoint`: a cooler name alternative for `dsc.red` I had lying around.
- `.m`: mobile; it works on multiple platforms, and is [optimized for mobile](https://github.com/13-05/redpoint/blob/main/etc/mobile_wait_what.md)!
- `.tool`: it's a multitool!

## Current Commands ~~excluding clear & exit~~
1) Discord Webhook Spammer
2) Discord Webhook Deleter
3) Discord UserID Lookup Tool
4) Discord Token Checker
5) Discord ANSI Codeblock Gen
6) Generic Webpage Cloner
7) Reverse IPV4 Lookup Tool (relies on [ip-api.com](https://ip-api.com))
8) Image Search Tool
9) Current Crypto Prices
10) [pastie.io](https://pastie.io) Paste CLI Interface (kinda crappy lmfao)

## TODOs
1) Discord Token Logger Generator
2) Discord Commandline Client Mode
3) Discord Token Lookup (gathers info on someone by their token)
4) Discord Server Cloner

## Community
Join us on the matrix [here](https://matrix.to/#/!mgpMhaBWHrPHIuRdRC:matrix.org?via=matrix.org)!

Or, join our [Discord](https://dsc.gg/unwelcome)!

## Use
Download a precompiled windows 64 bit exe [here](https://github.com/13-05/redpoint/releases/tag/win64)!

## Building From Source
### LINUX (debian & [debian-based](https://en.wikipedia.org/wiki/Category:Debian-based_distributions))
```bash
$ sudo apt update && sudo apt upgrade
$ sudo apt install build-essential
$ sudo apt install cmake
$ git clone https://github.com/13-05/redpoint
$ cd redpoint
$ git clone https://github.com/libcpr/cpr.git
$ cd cpr
$ mkdir build && cd build
$ sudo cmake ..
$ sudo make
$ sudo make install
$ cd ..
$ cd ..
$ sudo cp -r /usr/local/lib/libcpr.so* /usr/lib/
$ sudo cp /usr/local/lib/libcurl* /usr/lib/
$ git clone https://github.com/nlohmann/json.git
$ cd json
$ mkdir build && cd build
$ sudo cmake ..
$ sudo make
$ sudo make install
$ cd ..
$ cd ..
$ cd src
$ g++ redpoint.m.tool.cpp -o redpoint.m -lcpr
$ ./redpoint.m
```

## The Future
I'll add as many features as I can to this thing, so stay tuned!
