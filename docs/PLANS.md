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

## 상태 범례

- `예정`: 아직 시작 전
- `진행중`: 구현 중이거나, 구현 후 사용자 수동 작업 또는 결과 확인을 기다리는 상태
- `완료`: 구현 및 현재 확인 모드 기준 확인 완료

## 최근 작업 로그
- 2026-08-05: 01-13 점수 증가량 수정 결과 확인 완료. 사용자 확인에 따라 음식 1개 획득 시 현재 점수가 100 증가하는 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-13 점수 증가량 수정. 사용자 요청에 따라 음식 1개 획득 시 점수 증가 기본값을 100으로 변경했다. `BP_PlayerCharacter`의 `ScoreComponent` 값 확인과 PIE 결과 확인 대기 중.
- 2026-08-05: 01-13 결과 확인 완료. 사용자 확인에 따라 음식 획득, 체력 20 회복, 최대 체력 100 초과 방지, 현재 점수 증가와 표시, 범위 밖 요소 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-13 음식 획득과 체력 회복 점수 코드 구현. 사용자 선택에 따라 점수 책임을 `HungryHeroScoreComponent`로 분리하고, `FoodPickup`이 플레이어와 겹치면 체력 20 회복, 점수 증가, 음식 제거를 처리하도록 했다. 기존 Canvas HUD에 현재 점수 표시를 추가했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-05: 사용자 요청 템플릿을 기준으로 01-13 음식 획득과 체력 회복 점수 task를 추가했다. 01-10에서 음식 드롭이 준비되어 있고 01-6에서 체력 흐름이 준비되어 있어 01-12 다음 순서로 적합하며, 음식 획득 이펙트·효과음·밸런싱·최종 UI 디자인·최종 모델 연동을 제외해 한 단계 범위로 유지했다.
- 2026-08-05: 01-12 결과 확인 완료. 사용자 확인에 따라 일반 동물 스폰과 접근 유지, 칼 공격 시 넉백 직후 약 1초 정지, 스턴 중 접근·돌진 예고·돌진 중단, 스턴 종료 후 기존 행동 복귀, 범위 밖 요소 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-12 일반 동물 피격 스턴 코드 구현. `RegularAnimal`에 피격 스턴 상태와 1초 대기 시간을 추가하고, `RegularAnimalCombatComponent`가 칼 피격 시 스턴 상태로 전환하도록 했다. 스턴 중 접근, 돌진 예고, 돌진, 자체 분리 이동을 멈추며 시간이 지나면 접근 상태로 복귀한다. 수동 컴파일과 PIE 결과 확인 대기 중.
