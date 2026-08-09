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
| 01-7 | [Tasks/01-7_regular_animal_spawn_and_dash.md](../Tasks/01-7_regular_animal_spawn_and_dash.md) | 일반 동물 스폰과 돌진 | 완료 |
| 01-8 | [Tasks/01-8_regular_animal_separation.md](../Tasks/01-8_regular_animal_separation.md) | 일반 동물 겹침 방지 | 완료 |
| 01-9 | [Tasks/01-9_knife_attack_cone_targeting.md](../Tasks/01-9_knife_attack_cone_targeting.md) | 칼 공격 부채꼴 대상 판정 | 완료 |
| 01-10 | [Tasks/01-10_regular_animal_health_and_food_drop.md](../Tasks/01-10_regular_animal_health_and_food_drop.md) | 일반 동물 체력과 음식 드롭 | 완료 |
| 01-11 | [Tasks/01-11_regular_animal_knockback.md](../Tasks/01-11_regular_animal_knockback.md) | 일반 동물 피격 넉백 | 완료 |
| 01-12 | [Tasks/01-12_regular_animal_hit_stun.md](../Tasks/01-12_regular_animal_hit_stun.md) | 일반 동물 피격 스턴 | 완료 |
| 01-13 | [Tasks/01-13_food_pickup_health_and_score.md](../Tasks/01-13_food_pickup_health_and_score.md) | 음식 획득과 체력 회복 점수 | 완료 |
| 01-14 | [Tasks/01-14_game_over_stops_play.md](../Tasks/01-14_game_over_stops_play.md) | 게임오버 시 플레이 정지 | 완료 |
| 01-15 | [Tasks/01-15_animal_player_collision.md](../Tasks/01-15_animal_player_collision.md) | 동물과 플레이어 충돌 처리 정리 | 완료 |
| 01-16 | [Tasks/01-16_auto_attack_cooldown_visualization.md](../Tasks/01-16_auto_attack_cooldown_visualization.md) | 자동 공격 전환과 쿨타임 시각화 | 완료 |

## 상태 범례

- `예정`: 아직 시작 전
- `진행중`: 구현 중이거나, 구현 후 사용자 수동 작업 또는 결과 확인을 기다리는 상태
- `완료`: 구현 및 현재 확인 모드 기준 확인 완료

## 최근 작업 로그
- 2026-08-09: 01-16 결과 확인 완료. 사용자 확인에 따라 WASD 이동과 마우스 이동 방향 회전, 범위 내 자동 공격, 1초 쿨타임, 쿨타임 HUD 표시, 수동 공격 미발동, 게임오버 후 자동 공격 정지, 범위 밖 요소 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-09: 01-16 마우스 방향 전환 책임 분리. `HungryHeroMouseFacingComponent`를 추가해 마우스 방향 전환 입력 저장, 입력 모드 보장, 마우스 델타 fallback, 회전 적용을 전담하게 하고, `HungryHeroPlayerCharacter`는 축 입력 전달과 컴포넌트 호출만 하도록 정리했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 01-16 자동 공격과 마우스 회전 회귀 대응. 자동 공격 갱신을 컴포넌트 Tick 의존에서 플레이어 Tick 직접 호출로 바꾸고, 마우스 회전은 축 바인딩 값이 없을 때 PlayerController의 마우스 델타를 직접 읽는 fallback을 추가했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 01-16 마우스 방향 전환 입력 보강. 수동 공격 입력 매핑 제거 뒤에도 PIE에서 마우스 이동 축이 게임 입력으로 들어오도록 플레이어 BeginPlay에서 PlayerController 입력 모드를 GameOnly로 설정하고 마우스 커서를 숨기도록 했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 01-16 자동 공격 전환과 쿨타임 시각화 코드 구현. `HungryHeroKnifeAttackComponent`가 범위 안 일반 동물을 자동 탐지해 공격하고 1초 쿨타임을 적용하도록 했으며, `HungryHeroHealthHud`에 공격 준비/쿨타임 표시를 추가하고 `KnifeAttack` 입력 바인딩과 입력 매핑을 제거했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 사용자 요청 템플릿을 기준으로 01-16 자동 공격 전환과 쿨타임 시각화 task를 추가했다. 01-9 공격 범위 판정, 01-10 일반 동물 체력, 01-14 게임오버 정지, 01-15 동물과 플레이어 충돌 처리 흐름이 준비되어 있어 보스전 전 단계로 적합하며, 모바일 터치 UI·가상 조이스틱·새 공격 종류·공격 콤보·보스전·결과 화면·최종 UI 디자인을 제외해 한 단계 범위로 유지했다.
