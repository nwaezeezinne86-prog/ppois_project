# Contributing

## Branch Naming

| Prefix | Use |
|---|---|
| `feature/` | New features |
| `bugfix/` | Bug fixes |
| `docs/` | Documentation |
| `test/` | Test additions |
| `chore/` | Build, config |

## Commit Messages

Conventional commits:<type>(<scope>): <summary>

Closes #<issue> 
Types: `feat`, `fix`, `docs`, `test`, `refactor`, `chore`, `ci`

## Workflow

1. Sync: `git checkout develop && git pull`
2. Branch: `git checkout -b feature/my-feature`
3. Code + tests
4. Build: `cmake --build build -j`
5. Test: `cd build && ctest --output-on-failure`
6. Commit with a clear message
7. Push: `git push -u origin feature/my-feature`
8. Open PR to `develop`
9. Wait for CI green
10. Merge + delete branch

## Code Style

- C++17
- 4 spaces
- `camelCase` methods, `snake_case_` members
- `#pragma once`
- Prefer `const` and `noexcept`
