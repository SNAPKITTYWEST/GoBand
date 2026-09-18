# WinZip Electron IDE

Clean-room C# + C++ Windows IDE architecture derived from observable executable structure and behavior.

## Boundary

The supplied GoLand installer is treated as an external reference artifact. This project does not copy JetBrains source, assets, keys, or proprietary implementation.

Architecture:

Windows Shell
    |
C# IDE Application
    |
C# / Native Bridge
    |
C++ Native Core
    |
Windows APIs / process / filesystem / terminal / binary services

The implementation separates IDE semantics from native machine-facing operations.

## Languages

- C#: application shell, workspace, project model, editor, UI state, orchestration
- C++: native process execution, filesystem primitives, terminal, binary inspection, debugger-facing primitives
- Electron-style shell concepts are represented at the application boundary without requiring Java/JVM.

## Reference observations

The analyzed artifact:

- Product: GoLand
- Product version: 2026.2.2.1
- File version: 262.10315.160
- Size: 917,514,392 bytes
- PE machine reported by the outer executable: 0x014C
- PE format: PE32
- Sections: .text, .rdata, .data, .ndata, .rsrc

These observations describe the installer/container only. They are not treated as source-code reconstruction.

## Design principle

Binary representation -> observable behavior -> semantic contract -> independent implementation.
