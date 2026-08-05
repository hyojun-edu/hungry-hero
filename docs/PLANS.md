# Plans

## 목적

이 문서는 현재 진행 중인 단계 상태와 최근 작업 흐름을 빠르게 확인하기 위한 기록 문서입니다.
<!-- 새 프로젝트 시작 시 작업리스트와 최근 작업 로그의 기록을 초기화한다. -->

## 작업리스트
| 단계 | Task 문서 | 해야 할 항목 | 상태 |
| --- | --- | --- | --- |
| 01-1 | [Tasks/01-1_room_and_fixed_camera.md](../Tasks/01-1_room_and_fixed_camera.md) | 플레이어가 움직일 수 있는 사각형 방과 고정 카메라 준비 | 완료 |
| 01-2 | [Tasks/01-2_player_movement_and_knife_attack.md](../Tasks/01-2_player_movement_and_knife_attack.md) | 플레이어 이동과 단발 칼 공격 입력 확인 | 완료 |
| 01-3 | [Tasks/01-3_mouse_facing_and_spacebar_attack.md](../Tasks/01-3_mouse_facing_and_spacebar_attack.md) | 마우스 기준 플레이어 회전과 칼 공격 입력 정리 | 완료 |
| 01-4 | [Tasks/01-4_movement_facing_priority.md](../Tasks/01-4_movement_facing_priority.md) | 마우스 이동 방향 회전 유지 | 완료 |
| 01-5 | [Tasks/01-5_player_blueprint_setup.md](../Tasks/01-5_player_blueprint_setup.md) | 플레이어 Blueprint 관리 준비 | 완료 |
| 01-6 | [Tasks/01-6_player_health_and_game_over.md](../Tasks/01-6_player_health_and_game_over.md) | 플레이어 체력 감소와 게임오버 | 완료 |

## 상태 범례

- `예정`: 아직 시작 전
- `진행중`: 구현 중이거나, 구현 후 사용자 수동 작업 또는 결과 확인을 기다리는 상태
- `완료`: 구현 및 현재 확인 모드 기준 확인 완료

## 최근 작업 로그
- 2026-08-05: 01-6 결과 확인 완료. 사용자 확인에 따라 체력바와 체력 숫자 표시, 체력 감소, 약 30초 후 체력 0, `GAME OVER` 문구, 범위 밖 요소 미생성을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-6 체력 감소와 게임오버 구현. `HungryHeroHealthComponent`와 `HungryHeroHealthHud`를 추가하고 `HungryHeroPlayerCharacter`에 체력 컴포넌트를 연결했다. `BP_HungryHeroGameMode` HUD Class 설정 및 PIE 결과 확인 대기 중.
- 2026-08-05: 사용자 요청 템플릿을 기준으로 01-6 플레이어 체력 감소와 게임오버 task를 추가했다. 01-5 다음 순서로 적합하고, 적·음식·점수·보스를 제외해 한 단계 범위로 유지했다.
- 2026-08-05: 01-5 결과 확인 완료. 사용자 확인에 따라 `BP_PlayerCharacter` 생성과 `BP_HungryHeroGameMode` 연결, PIE 이동·마우스 회전·공격 표시, inherited component 확인, 범위 밖 동작 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-5 Character 전환 구현. 기존 플레이어 Pawn 클래스를 제거하고 `HungryHeroPlayerCharacter`를 추가했으며, GameMode가 C++에서 기본 플레이어 클래스를 직접 지정하지 않도록 분리했다. `BP_PlayerCharacter`와 `BP_HungryHeroGameMode` 생성 및 맵 설정 수동 확인 대기 중.
- 2026-08-05: 01-5 범위 조정. 플레이어 Blueprint 관리 준비에 새 `ACharacter` 계열 C++ 클래스 생성을 포함하기로 했다.
- 2026-08-05: 사용자 요청 템플릿을 기준으로 01-5 플레이어 Blueprint 관리 준비 task를 추가했다. 01-4 다음 순서로 적합하고, 최종 모델·애니메이션·체력·적·음식·점수를 제외해 한 단계 범위로 유지했다.
- 2026-08-05: 01-3/01-4 결과 확인 완료. 사용자 확인에 따라 마우스 왼쪽 클릭과 SpaceBar 공격, 이동 중 자동 회전 미발생, 마우스 이동 방향 기준 회전, 범위 밖 동작 미발생 확인 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-4 이동 방향 자동 회전 제거. 사용자 요청에 따라 이동 입력 방향으로 자동 회전하는 처리를 제외하고, 마우스 이동 방향만 플레이어 정면 방향으로 쓰도록 task와 Pawn 코드를 갱신했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-05: 01-3/01-4 공격 입력 변경. 사용자 요청에 따라 `KnifeAttack`에 마우스 왼쪽 클릭 매핑을 다시 추가하고, 01-3의 SpaceBar 전용 공격 조건을 SpaceBar 또는 마우스 왼쪽 클릭 공격 조건으로 갱신했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-05: 01-4 마우스 방향 정의 변경. 마우스 좌우 누적 회전 대신 `MouseX`/`MouseY` 이동 벡터가 플레이어 정면 방향이 되도록 입력 매핑과 Pawn 회전 처리를 변경했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-05: 01-4 이동 방향 회전 보정. 이동 입력 방향 자동 회전을 즉시 회전에서 점진 보간 회전으로 변경했다. 수동 컴파일과 PIE 결과 확인 대기 중.
