# Clean-Room Boundary

The reference executable is used only to establish observable facts and behavioral requirements.

Do not:

- copy JetBrains source code
- extract or redistribute proprietary assets
- reproduce proprietary keys or signatures
- translate proprietary implementation line-for-line
- represent inferred internals as observed facts

Do:

- implement independent interfaces
- implement independent data structures
- implement independent Windows-native operations
- document observable behavior
- test the recreated IDE against its own contracts
- preserve a distinction between observation and inference

The target is functional and architectural equivalence at the public/observable behavior level, not source-code duplication.
