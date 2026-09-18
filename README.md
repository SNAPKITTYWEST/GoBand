<p align="center">
  <img src="goband.png" alt="GoBand - The Reverse Engineered GoLand" width="500" height="500">
</p>

<p align="center">
  <a href="https://github.com/SNAPKITTYWEST/GoBand/releases"><img src="https://img.shields.io/github/v/release/SNAPKITTYWEST/GoBand?label=release&color=00FFFF&style=for-the-badge" alt="Release"></a>
  <img src="https://img.shields.io/badge/version-2026.2.2.1-7000FF?style=for-the-badge" alt="Version">
  <img src="https://img.shields.io/badge/platform-Windows%2010%2F11-FF00FF?style=for-the-badge" alt="Platform">
  <img src="https://img.shields.io/badge/stack-C%23%20%2B%20C%2B%2B-00FF9D?style=for-the-badge" alt="Stack">
  <img src="https://img.shields.io/badge/license-GPL--3.0-FF3B30?style=for-the-badge" alt="License">
  <img src="https://img.shields.io/badge/build-early-FFD60A?style=for-the-badge&labelColor=1a1a1a" alt="Build">
</p>



<p align="center">
  <b>GoLand reverse-engineered and rebuilt as a native Windows IDE.</b><br>
  No JVM. No Java. Native WPF shell + C++ core.<br>
  <i>Not affiliated with JetBrains. JetBrains and GoLand are trademarks of JetBrains s.r.o.</i>
</p>

---

## What this is

This is **GoLand reverse-engineered and reimplemented from scratch**.

The reference was the **GoLand 2026.2.2.1** installer. We observed the binary structure, filesystem behavior, process model, and UI workflow, then rebuilt those contracts as a clean native Windows application.

This is not a plugin, theme, wrapper, or fork. It is a standalone IDE that implements the same class of functionality as GoLand, written in C# and C++.

## Why

GoLand runs on the JVM. This does not.

- **C# (WPF)** - workspace, project model, editor, tabs, panels, settings, build/run orchestration
- **C++** - process execution, filesystem, terminal, PE/binary inspection, debugger boundary
- **P/Invoke bridge** - narrow ABI between managed and native

Goal: same IDE semantics, native Windows execution.

## How it was built

```
[1] Binary observation  -> PE headers, sections, imports
[2] Behavior observation -> projects, processes, filesystem, terminals
[3] Semantic contract   -> typed operations and results
[4] Clean rewrite       -> independent C# + C++ , no copied source/assets/keys
```

> No JetBrains source, binaries, assets, or license keys are included or copied.

## Architecture

```mermaid
%%{init: {'theme':'base', 'themeVariables': {'primaryColor':'#00FFFF','primaryTextColor':'#000','primaryBorderColor':'#FF00FF','lineColor':'#7000FF','secondaryColor':'#FFD60A','tertiaryColor':'#1a1a1a'}}}%%
flowchart TB
    A[🖥️ Windows Shell] --> B[💎 C# WPF IDE<br/>workspace · editor · project · UI]
    B --> C[🔗 P/Invoke Bridge<br/>NativeBridge.cs]
    C --> D[⚙️ C++ Native Core<br/>process · filesystem · PE · terminal]
    D --> E[🧱 Win32 APIs<br/>CreateProcess · ReadFile · InspectPE]

    style A fill:#00FFFF,stroke:#FF00FF,stroke-width:3px,color:#000
    style B fill:#7000FF,stroke:#00FFFF,stroke-width:3px,color:#fff
    style C fill:#FF00FF,stroke:#FFD60A,stroke-width:3px,color:#fff
    style D fill:#1a1a1a,stroke:#00FF9D,stroke-width:3px,color:#00FF9D
    style E fill:#FFD60A,stroke:#FF3B30,stroke-width:3px,color:#000
```

**Bridge ABI**

```
CreateProcess  │ TerminateProcess │ ReadProcessOutput │ WriteProcessInput
ReadFile       │ WriteFile        │ WatchPath         │ InspectPE
GetArchitecture│ GetSections
```

No UI logic lives in the native layer.

## Project layout

```
src/managed/     - C# WPF application (Program.cs, MainWindow, project model)
src/native/      - C++ native core (native_core.cpp/hpp - process + PE logic)
src/bridge/      - P/Invoke bridge (NativeBridge.cs)
build/           - CMake build for native library
specification/   - Architecture and boundary docs
goband.png       - Hero image
```

## Reference artifact

Observations are from the installer container only, not source reconstruction:

| Field | Value |
|---|---|
| Product | GoLand |
| Product Version | 2026.2.2.1 |
| File Version | 262.10315.160 |
| Size | 917,514,392 bytes |
| PE Machine | 0x014C (I386) |
| PE Format | PE32 |
| Sections | .text, .rdata, .data, .ndata, .rsrc |

## Build

Prerequisites: Windows 10/11, .NET 8 SDK, CMake 3.25+, C++20 compiler (MSVC).

```powershell
# Build native core
cmake -S build -B build/out
cmake --build build/out --config Release

# Build and run IDE
dotnet build src/managed/WinZipIde.csproj -c Release
dotnet run --project src/managed/WinZipIde.csproj
```

Output: `winzip_native.dll` must sit alongside the managed executable for P/Invoke.

## Releases

| Version | Date | Notes |
|---|---|---|
| `v0.1.0-alpha` | 2026-09-18 | Initial clean-room shell + native PE/process core |

- Latest: [Releases page](https://github.com/SNAPKITTYWEST/GoBand/releases)
- Changelog: [CHANGELOG.md](CHANGELOG.md) if present
- Create a release: `git tag v0.1.0 && git push origin v0.1.0`

## Status

Early implementation.

- [x] WPF shell and main window
- [x] Native process execution (CreateProcessW)
- [x] File byte reading
- [x] PE inspection (DOS/NT headers, section table)
- [ ] Full editor, project tree, and panels
- [ ] Terminal and file watcher
- [ ] Debugger adapter
- [ ] Go toolchain integration

See `specification/architecture.md` for the intended panel and workspace model.

## Legal

Clean-room implementation. Built by observing public behavior of the GoLand installer and IDE, then writing new code to match the observed contracts.

No JetBrains code, binaries, branding assets, or proprietary implementation is redistributed here.
```
╔════════════════════════════════════════════════════════════╗
║                                                          ║
║   ██████╗  ██████╗ ██████╗  █████╗ ███╗   ██╗██████╗      ║
║  ██╔════╝ ██╔═══██╗██╔══██╗██╔══██╗████╗  ██║██╔══██╗     ║
║  ██║  ███╗██║   ██║██████╔╝███████║██╔██╗ ██║██║  ██║     ║
║  ██║   ██║██║   ██║██╔══██╗██╔══██║██║╚██╗██║██║  ██║     ║
║  ╚██████╔╝╚██████╔╝██████╔╝██║  ██║██║ ╚████║██████╔╝     ║
║   ╚═════╝  ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝      ║
║                                                          ║
║   THE REVERSE ENGINEERED GOLAND  //  C# + C++  //  NO JVM ║
║   ── SAME POWER. MORE FREEDOM. ──                        ║
║                                                          ║
╚════════════════════════════════════════════════════════════╝
```
## License

GPL-3.0-or-later + Sovereign Source License v1.0. See `LICENSE`.

Copyright (c) 2026 SnapKittyWest / Bel Esprit D'Accord Trust.
