---
name: game-gdd-planner
description: Create, continue, or revise Korean game design documents for Unreal Engine 5.8 class projects. Use when the user starts from a one-line game idea, wants step-by-step beginner-friendly GDD planning, needs feasibility scoping for a short Unreal project, asks to resume from GDD_PROGRESS.md, or asks to update an existing Game_GDD.md with visible change notes.
---

# Game GDD Planner

## Core Rules

Use this skill to help a non-design-major user turn a one-line game idea into an executable Korean GDD for an Unreal Engine 5.8 class project.

Follow these rules strictly:

- Start from one line describing the game idea.
- Ask exactly one question at a time.
- Avoid planning jargon. If a term is necessary, explain it in plain Korean.
- After every user answer, briefly summarize confirmed decisions, update `GDD_PROGRESS.md`, then ask the next single question.
- If the user says they do not know, asks you to decide, or asks for a recommendation, choose a beginner-friendly default and record it.
- Keep scope feasible for Unreal Engine 5.8 and the confirmed class-project constraints.
- If the user proposes a scope that is too large, shrink it to a buildable version and explain the tradeoff briefly.
- Do not finish while important sections are empty. Ask the next missing question first.
- Write the final GDD in Korean Markdown as `Game_GDD.md`.
- When revising an existing GDD, preserve useful existing content and add a short `변경 기록` note under each changed section.

## Files

Create one folder per GDD project inside the current workspace unless the user specifies a different path. Put all GDD files for that game inside that folder.

Recommended folder naming:

- If the game title is known, create `GDD_[game-title]`.
- If the title is not known yet, create `GDD_Project_YYYYMMDD_HHMM`, then keep using that folder for the session.

Use these files inside the project folder:

- `GDD_PROGRESS.md`: working state, confirmed decisions, open questions, and next question.
- `Game_GDD.md`: final or revised GDD.

At the start of a request:

1. Check whether a relevant GDD project folder already exists in the workspace.
2. If a matching folder exists, read its `GDD_PROGRESS.md` or `Game_GDD.md` and continue from the next missing item.
3. If starting fresh and the user already gave a one-line game idea, create a new GDD project folder and treat that idea as the first confirmed answer.
4. If starting fresh and the user did not give an idea yet, ask for the one-line game idea before creating detailed content.
5. If revising, read the target folder's `Game_GDD.md`, identify the requested section, and ask one clarifying question only if the edit would otherwise be unsafe or ambiguous.

## Question Flow

Use this stable order, adapting small follow-up wording to the user's answers:

1. Game idea: "어떤 게임을 만들고 싶나요? 한 줄로 말해 주세요."
2. Project constraints: ask team size, class period, Unreal experience, and required deliverable. If the user asks for a recommendation, use: solo or small team, 3-4 weeks, beginner Unreal skill, one playable prototype.
3. Player fantasy: what the player should feel or do most often.
4. Core action: the one repeated action that defines play.
5. Genre and camera: only enough to guide implementation.
6. Controls: keyboard/mouse, gamepad, or other expected input.
7. Goal and end condition: how the player succeeds, fails, or finishes.
8. Level or play space: one room, one arena, short course, small map, or menu-based flow.
9. Main objects: player, enemies, NPCs, items, obstacles, interactables.
10. Rules and numbers: health, score, timer, resource, cooldown, win/loss values.
11. UI: only the screens and HUD elements needed for the prototype.
12. Art and sound: available assets, placeholder style, and minimum sound needs.
13. Implementation priority: must-have, should-have, optional.
14. Exclusions: explicitly list what will not be built.
15. Schedule: small milestone plan for the confirmed period.

## Feasibility Defaults

Use these defaults when the user asks you to decide:

- Prefer one playable level or one repeatable gameplay loop.
- Prefer one controllable character.
- Prefer one to two enemy or obstacle types.
- Prefer three to five interactable/item types at most.
- Prefer simple win/loss conditions over branching stories.
- Prefer placeholder art and free/engine-provided assets unless the user already has assets.
- Avoid multiplayer, open world, complex AI, procedural generation, large inventories, branching narrative, advanced physics, and large custom animation sets unless the user has a clear reason and enough time.

When shrinking scope, keep the user's core fantasy and remove content volume first.

## Progress File Format

Keep `GDD_PROGRESS.md` concise and easy to resume:

```markdown
# GDD Progress

## Current Summary
- ...

## Confirmed Decisions
- ...

## Open Questions
- ...

## Next Question
...
```

Update it after every answered question.

## Final GDD

When enough information is confirmed, write `Game_GDD.md` using the structure in `references/gdd-structure.md`.

Before finalizing, check that:

- The production scope matches the confirmed team, time, and skill level.
- Every required GDD section has concrete content.
- Must-have features are smaller than the full idea.
- Optional features can be removed without breaking the game.
- Excluded features are clearly named.

End by telling the user that `Game_GDD.md` is ready and mention the next practical step, such as building a prototype task list.

## Revising Existing GDDs

When the user asks to revise an existing GDD:

1. Read `Game_GDD.md`.
2. Apply only the requested change unless feasibility requires a linked adjustment.
3. If changing scope, also update implementation priority, exclusions, and schedule as needed.
4. Under each changed section, add:

```markdown
**변경 기록:** YYYY-MM-DD: 변경 내용을 한 문장으로 요약.
```

5. Keep the document Korean by default.
