# Contributing

## Team (max 3 people)

| Role | Owns |
|---|---|
| A – Domain | `entry.*`, entry subclasses, parsing |
| B – Core | `repository.hpp`, `dictionary.*`, file I/O |
| C – Quality & UX | `main.cpp`, tests, docs, CI, board |

## Workflow

1. Pick a card from the board and move it to *In progress*.
2. Branch from `main`: `feature/<short-name>` or `fix/<short-name>`.
3. Commit small and often: `Add Cyrillic lower-casing`, not `update`.
4. Open a **pull request**; at least one teammate reviews. CI must be green.
5. Squash-merge, delete the branch, move the card to *Done*.
6. Never push directly to `main`.

## Definition of done

- Code compiles without warnings (`-Wall -Wextra -pedantic`).
- New behaviour has a unit test; all tests pass.
- Docs (`README.md`, `docs/`) updated when behaviour changes.
