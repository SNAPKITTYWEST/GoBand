# Binary Semantics

Binary semantics is the representation boundary between an abstract computational operation and machine state.

It is modeled using:

- state
- value
- encoding
- memory location
- operation
- transition
- control flow
- observation

Example:

LOAD address
ADD value
STORE address
BRANCH condition

is represented semantically as:

state(S)
 -> read(S,address)
 -> compute(S,value)
 -> write(S,address)
 -> transition(S,next)

The IDE must never confuse source-language syntax with binary semantics.

The Binary Inspector therefore exposes:

- architecture
- executable format
- entry point
- sections
- imports
- exports
- relocations
- symbols when available
- raw offsets
- virtual addresses
- permissions
- hashes
- embedded-resource boundaries

The inspector is an analytical subsystem, not a code-copying subsystem.
