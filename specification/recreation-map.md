# Recreation Map

| Reference capability | Independent implementation |
|---|---|
| Application shell | C# WPF shell |
| Workspace | C# workspace model |
| Editor | C# editor subsystem |
| Project tree | C# project model |
| Process execution | C++ native core |
| Terminal | C++ process/I/O |
| Filesystem | C++ native filesystem layer |
| Binary inspection | C++ PE parser |
| Debug boundary | C++ adapter + C# presentation |
| Diagnostics | C# diagnostic model |
| Artifact tracking | C# provenance model |
| Native bridge | narrow P/Invoke ABI |

The implementation is intentionally layered:

C# UI
  ↓
semantic services
  ↓
native bridge
  ↓
C++
  ↓
Windows
