# Contributing

## Content

| Role | Owns |
|---|---|
| A – Domain | `entry.*`, entry subclasses, parsing |
| B – Core | `repository.hpp`, `dictionary.*`, file I/O |
| C – Quality & UX | `main.cpp`, tests, docs, CI, board |

| Роль | Зона ответственности |
|---|---|
| A – Предметная область | `entry.*`, подклассы `entry`, парсинг |
| B – Ядро | `repository.hpp`, `dictionary.*`, файловый ввод-вывод |
| C – Качество и UX | `main.cpp`, тесты, документация, CI, доска задач |

## Workflow

1. Pick a card from the board and move it to *In progress*.
2. Branch from `main`: `feature/<short-name>` or `fix/<short-name>`.
3. Commit small and often: `Add Cyrillic lower-casing`, not `update`.
4. Open a **pull request**; at least one teammate reviews. CI must be green.
5. Squash-merge, delete the branch, move the card to *Done*.
6. Never push directly to `main`.

1. Возьмите карту с доски и переместите ее в *В процессе*.
2. Ответвление от `main`: `feature/<короткое имя>` или `fix/<короткое имя>`.
3. Делайте помаленьку и часто: `Добавить кириллицу в нижнем регистре`, а не `обновить`.
4. Откройте **pull request**; хотя бы один отзыв товарища по команде. CI должен быть зеленым.
5. Сквош-слияние, удаление ветки, перемещение карты в *Готово*.
6. Никогда не нажимайте напрямую на `main`.

## Definition of done

- Code compiles without warnings (`-Wall -Wextra -pedantic`).
- New behaviour has a unit test; all tests pass.
- Docs (`README.md`, `docs/`) updated when behaviour changes.

- Код компилируется без предупреждений (`-Wall -Wextra -pedantic`).
- Для нового поведения предусмотрен модульный тест; все тесты проходят успешно.
- Документация (`README.md`, `docs/`) обновлена ​​в соответствии с изменениями в поведении.
