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
| 01-17 | [Tasks/01-17_android_mobile_build_verification.md](../Tasks/01-17_android_mobile_build_verification.md) | Android 모바일 빌드 전환과 기기 실행 확인 | 완료 |

## 상태 범례

- `예정`: 아직 시작 전
- `진행중`: 구현 중이거나, 구현 후 사용자 수동 작업 또는 결과 확인을 기다리는 상태
- `완료`: 구현 및 현재 확인 모드 기준 확인 완료

## 최근 작업 로그
- 2026-08-10: 01-17 결과 확인 완료. 사용자 확인에 따라 Android 패키징과 기기 실행, 모바일 HUD 표시, Android 가상 스틱 이동과 방향 전환, PC/Android 입력 경로 분리, 자동 공격과 1초 쿨타임 표시, 체력·음식·점수·게임오버 흐름, 범위 밖 기능 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-10: 01-17 Android 오른쪽 스틱 Y축 반전. Android 기기에서 방향 전환 좌우는 맞지만 위아래가 뒤집혀 `DefaultInput.ini`의 `MobileFaceForward` `Gamepad_RightY` 스케일을 `-1.0`으로 변경했다. 이동 입력과 좌우 방향 전환 입력은 유지했다. 수동 Android 컴파일과 기기 방향 확인 대기 중.
- 2026-08-10: 01-17 Android 방향 전환 90도 회전 문제 대응. Mac 입력 경로가 정상화된 뒤 Android 오른쪽 스틱만 90도 어긋나는 문제가 남아, 이동이 정상인 왼쪽 스틱과 같은 축 의미를 쓰도록 `Android Landscape Input Yaw Offset Degrees` 기본값을 `0.0`으로 변경했다. 수동 Android 컴파일과 기기 방향 확인 대기 중.
- 2026-08-10: 01-17 Mac 방향 전환 입력 경로 수정. PC/모바일 축 이름만 분리하고 양쪽을 동시에 바인딩한 상태가 Mac 빌드에서 방향 전환 입력을 방해할 수 있어, `SetupPlayerInputComponent`에서 Android 빌드에만 `Mobile*` 축을 바인딩하고 그 외 빌드에는 `MouseFace*` 축만 바인딩하도록 변경했다. Android 오른쪽 스틱은 두 축 값을 플레이어에서 합쳐 보정 후 한 번에 방향 컴포넌트에 전달한다. 수동 Mac 컴파일과 방향 전환 확인 대기 중.
- 2026-08-10: 01-17 Mac 마우스 방향 전환 원복. 마우스 델타와 화면 위치 추적 fallback 방식이 기대 동작을 만들지 못해 `HungryHeroMouseFacingComponent`를 저장소의 기존 마우스 방향 전환 방식으로 되돌렸다. PC/모바일 축 이름 분리는 유지하되 Mac 마우스 방향 전환은 기존 컴포넌트 동작 확인 대기 중.
- 2026-08-10: 01-17 Mac 마우스 방향 전환 fallback 보정. 중앙으로 마우스를 강제 복귀시키는 방식이 다음 프레임에 반대 방향 입력을 만들어 특정 방향으로 되돌아가는 현상을 유발해, 마지막 마우스 화면 위치와 현재 위치의 차이를 추적하는 방식으로 변경했다. 수동 Mac 컴파일과 방향 전환 확인 대기 중.
- 2026-08-10: 01-17 Mac 마우스 방향 전환 fallback 추가. Mac 빌드에서 축 입력과 `GetInputMouseDelta`가 모두 0으로 들어오는 상황에 대응하기 위해, 데스크톱 빌드에서 마우스 화면 위치의 중앙 기준 오프셋을 회전 입력으로 읽고 다시 중앙으로 되돌리는 보조 경로를 추가했다. Android에서는 해당 경로를 사용하지 않는다. 수동 Mac 컴파일과 방향 전환 확인 대기 중.
- 2026-08-10: 01-17 Mac 방향 전환 회귀 대응. PC/모바일 입력 경로 분리 후 Mac 빌드에서 마우스 방향 전환이 동작하지 않는 문제를 줄이기 위해, 데스크톱 빌드에서는 축 바인딩 값 여부와 관계없이 PlayerController의 마우스 델타 fallback을 매 프레임 누적하도록 조정했다. Android에서는 해당 fallback을 계속 비활성화한다. 수동 Mac 컴파일과 방향 전환 확인 대기 중.
- 2026-08-10: 01-17 PC와 Android 입력 경로 분리. `DefaultInput.ini`에서 PC 키보드/마우스 축과 Android 기본 가상 조이스틱 축을 `Move*`/`MouseFace*`, `MobileMove*`/`MobileFace*`로 분리하고, Android에서는 마우스 델타 fallback이 방향 전환을 건드리지 않도록 제한했다. 수동 Android 컴파일과 기기 방향 재확인 대기 중.
- 2026-08-10: 01-17 Android landscape 방향 전환 입력 보정 대응. `HungryHeroMobileInputOrientationComponent`를 추가해 Android 패키지에서만 가상 조이스틱 방향 전환 입력에 yaw offset을 적용하도록 하고, 이동 입력은 기존 월드 방향 입력을 유지했다. `HungryHeroMouseFacingComponent`는 같은 프레임의 보정된 축 입력을 누적하도록 조정했다. 수동 Android 컴파일과 기기 방향 확인 대기 중.
- 2026-08-10: 01-17 Android 방향 전환 보정값 재조정. 이동 입력 원복 이후 `90.0` 보정이 방향 전환을 180도 뒤집는 것으로 확인되어, 음수값 저장 이슈를 피하기 위해 `Android Landscape Input Yaw Offset Degrees` 기본값을 `270.0`으로 변경했다. 수동 Android 컴파일과 기기 방향 재확인 대기 중.
- 2026-08-10: 01-17 Android 모바일 빌드 전환 설정 구현. `DefaultEngine.ini`에 Android 런타임 설정과 Mobile/Scalable 하드웨어 타깃을 추가하고, `DefaultInput.ini`에 기본 가상 조이스틱 확인용 Gamepad 축 매핑을 추가했으며, `HungryHeroHealthHud`에 모바일 화면 비율 대응 HUD 스케일 보정을 추가했다. 수동 Android 패키징과 기기 실행 확인 대기 중.
- 2026-08-10: 사용자 요청 템플릿을 기준으로 01-17 Android 모바일 빌드 전환과 기기 실행 확인 task를 추가했다. 01-16 자동 공격 전환과 쿨타임 시각화가 완료되어 보스전 전 단계로 적합하며, Google Play 출시·광고·결제·최종 최적화·모바일 전용 터치 UI 대개편·보스전 추가·그래픽 품질 세부 튜닝을 제외해 한 단계 범위로 유지했다.
- 2026-08-09: 01-16 결과 확인 완료. 사용자 확인에 따라 WASD 이동과 마우스 이동 방향 회전, 범위 내 자동 공격, 1초 쿨타임, 쿨타임 HUD 표시, 수동 공격 미발동, 게임오버 후 자동 공격 정지, 범위 밖 요소 미발생 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
- 2026-08-09: 01-16 마우스 방향 전환 책임 분리. `HungryHeroMouseFacingComponent`를 추가해 마우스 방향 전환 입력 저장, 입력 모드 보장, 마우스 델타 fallback, 회전 적용을 전담하게 하고, `HungryHeroPlayerCharacter`는 축 입력 전달과 컴포넌트 호출만 하도록 정리했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 01-16 자동 공격과 마우스 회전 회귀 대응. 자동 공격 갱신을 컴포넌트 Tick 의존에서 플레이어 Tick 직접 호출로 바꾸고, 마우스 회전은 축 바인딩 값이 없을 때 PlayerController의 마우스 델타를 직접 읽는 fallback을 추가했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 01-16 마우스 방향 전환 입력 보강. 수동 공격 입력 매핑 제거 뒤에도 PIE에서 마우스 이동 축이 게임 입력으로 들어오도록 플레이어 BeginPlay에서 PlayerController 입력 모드를 GameOnly로 설정하고 마우스 커서를 숨기도록 했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 01-16 자동 공격 전환과 쿨타임 시각화 코드 구현. `HungryHeroKnifeAttackComponent`가 범위 안 일반 동물을 자동 탐지해 공격하고 1초 쿨타임을 적용하도록 했으며, `HungryHeroHealthHud`에 공격 준비/쿨타임 표시를 추가하고 `KnifeAttack` 입력 바인딩과 입력 매핑을 제거했다. 수동 컴파일과 PIE 결과 확인 대기 중.
- 2026-08-09: 사용자 요청 템플릿을 기준으로 01-16 자동 공격 전환과 쿨타임 시각화 task를 추가했다. 01-9 공격 범위 판정, 01-10 일반 동물 체력, 01-14 게임오버 정지, 01-15 동물과 플레이어 충돌 처리 흐름이 준비되어 있어 보스전 전 단계로 적합하며, 모바일 터치 UI·가상 조이스틱·새 공격 종류·공격 콤보·보스전·결과 화면·최종 UI 디자인을 제외해 한 단계 범위로 유지했다.
