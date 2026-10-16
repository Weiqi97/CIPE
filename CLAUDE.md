# LibPFE for agents

Header-only C++20 functional encryption over LibRBP: six inner-product (IPFE) and two quadratic (QFE) schemes, one
header each in `include/PFE/`, each a template over a LibRBP curve. `README.md` is the user-facing overview. The local
checkout directory is `LibRIPFE`.

## Commands

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug -DPFE_ENABLE_COVERAGE=ON -DFETCHCONTENT_SOURCE_DIR_RBP=../LibRBP
cmake --build build --parallel
ctest --test-dir build --output-on-failure
cmake -B build-release -S . -DCMAKE_BUILD_TYPE=Release -DPFE_BUILD_BENCH=ON && cmake --build build-release --parallel \
    && ./build-release/bench/pfe_bench 1 4
```

Without `FETCHCONTENT_SOURCE_DIR_RBP`, an installed LibRBP is used, else its `main` is fetched. CI requires 100% line
coverage of `include/PFE/`, passing tests in Release, the bench smoke test, and the demo built against the install.

## Invariants

- Every scheme has `setup`, `keygen`, `enc`, `prepare`, and a `dec` accepting both `Sk` and `PreparedSk`. A new scheme
  joins the tests through one adapter in `test/schemes.hpp`.
- `setup` rejects a dimension of 0, and every shape mismatch throws `rbp::ShapeError`, from LibRBP or the helpers in
  `ipfe.hpp` and `qfe.hpp`.
- Keys, prepared keys and `rbp::DlogTable` are immutable and shared across threads; `test/test_concurrency.cpp` is the
  contract.
- LibPFE, GoPFE and RustPFE keep the same constructions, test cases and benchmark inputs; change a scheme in one only
  with the others in view.
- Coverage comes from tests that reach a branch, never from reshaping code. No comments in code.
