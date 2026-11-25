# Project report: English–Russian Dictionary

## 1. Goal and scope
Console dictionary for EN⇄RU lookup, prefix search and editable data stored in a text file.

## 2. Team and process
Three members, roles in `CONTRIBUTING.md`. Work through GitHub: branches, pull requests, review, CI. Iterations: (1) model, (2) storage + lookup, (3) CLI, (4) tests and docs.

## 3. Architecture
See `docs/ARCHITECTURE.md` (class diagram, concepts used).

## 4. Implementation details
- Entry hierarchy and factory parsing
- `Repository<T>` template
- Reverse index for RU→EN
- UTF-8 Cyrillic lower-casing

## 5. Testing
14 unit tests: text utils, parsing, polymorphic formatting, repository, dictionary operations, load/save round trip. Run with CTest and in GitHub Actions.

## 6. Results
Insert screenshots of the CLI session and the passing test run.

## 7. Problems and solutions
- Case-insensitive Russian search without locales → custom `toLower`.
- Ambiguous Russian words (друг → friend, mate) → reverse index stores a list.

## 8. Conclusions and future work
Fuzzy search, quiz mode, larger imported dictionaries, GUI.
