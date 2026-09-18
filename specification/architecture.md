# Architecture Specification

## 1. Shell

The C# layer owns:

- application lifecycle
- workspace lifecycle
- project tree
- editor documents
- tabs
- commands
- menus
- panels
- settings
- build/run orchestration
- diagnostics presentation

## 2. Native core

The C++ layer owns:

- process creation
- process termination
- process I/O
- filesystem primitives
- file watching
- terminal process attachment
- PE inspection
- binary readers
- native debugger adapter boundary
- memory-safe ownership at the native boundary

## 3. Bridge

The bridge exposes a narrow ABI.

Operations:

CreateProcess
TerminateProcess
ReadProcessOutput
WriteProcessInput
ReadFile
WriteFile
WatchPath
InspectPE
GetArchitecture
GetSections

No UI logic belongs in the native layer.

## 4. Semantic model

Every operation produces a typed result:

Observation
    -> Validation
    -> Semantic Operation
    -> Result
    -> Diagnostic
    -> Provenance

The system must distinguish:

- source text
- parsed representation
- semantic model
- binary representation
- execution result
- visualization

## 5. Workspace

Workspace state is represented as deterministic documents:

workspace
projects
files
run configurations
toolchains
terminal sessions
diagnostics
artifacts

## 6. IDE panels

Initial panels:

1. Project
2. Editor
3. Terminal
4. Problems
5. Build
6. Run
7. Debug
8. Binary Inspector
9. Artifact/Provenance
10. Settings
