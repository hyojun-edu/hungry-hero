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

## 상태 범례

- `예정`: 아직 시작 전
- `진행중`: 구현 중이거나, 구현 후 사용자 수동 작업 또는 결과 확인을 기다리는 상태
- `완료`: 구현 및 현재 확인 모드 기준 확인 완료

## 최근 작업 로그
- 2026-08-05: 01-9 결과 확인 완료. 사용자 확인에 따라 노란색 부채꼴 공격 범위 표시, 정면 근접 대상의 초록색 후보 표시, 각도 밖·거리 밖 대상 제외, 범위 밖 요소 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-9 칼 공격 부채꼴 대상 판정 코드 구현. 기존 큐브형 공격 표시를 제거하고, 공격 시 플레이어 정면 60도와 근접 거리 안의 일반 동물만 후보로 찾도록 했다. 공격 범위는 노란색 부채꼴 선으로, 후보 동물은 초록색 구로 표시한다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-05: 사용자 요청 템플릿을 기준으로 01-9 칼 공격 부채꼴 대상 판정 task를 추가했다. 01-8 다음 순서로 적합하고, 동물 체력 감소·처치·음식 생성·점수 계산·공격 애니메이션 교체·최종 모델 연동을 제외해 한 단계 범위로 유지했다.
- 2026-08-05: 01-8 결과 확인 완료. 사용자 확인에 따라 일반 동물 스폰 위치 겹침 방지, 이동 중 분리 표시, 돌진 데미지 10 유지, 방 벽 충돌 유지, 범위 밖 요소 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-05: 01-8 일반 동물 겹침 방지 코드 구현. `RegularAnimal`에 주변 일반 동물과의 수평 분리 보정을 추가하고, `RegularAnimalSpawner`에 기존 동물과 떨어진 스폰 위치 재시도 및 실패 시 스폰 건너뛰기를 추가했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-05: 사용자 요청 템플릿을 기준으로 01-8 일반 동물 겹침 방지 task를 추가했다. 01-7 다음 순서로 적합하고, 복잡한 무리 이동 AI·길찾기·동물 회피 알고리즘·동물 체력 감소·처치·음식 생성을 제외해 한 단계 범위로 유지했다.
