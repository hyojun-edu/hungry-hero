# Plans

## 목적

이 문서는 현재 진행 중인 단계 상태와 최근 작업 흐름을 빠르게 확인하기 위한 기록 문서입니다.
<!-- 새 프로젝트 시작 시 작업리스트와 최근 작업 로그의 기록을 초기화한다. -->

## 작업리스트
| 단계 | Task 문서 | 해야 할 항목 | 상태 |
| --- | --- | --- | --- |
| 01-1 | [Tasks/01-1_room_and_fixed_camera.md](../Tasks/01-1_room_and_fixed_camera.md) | 플레이어가 움직일 수 있는 사각형 방과 고정 카메라 준비 | 완료 |

## 상태 범례

- `예정`: 아직 시작 전
- `진행중`: 구현 중이거나, 구현 후 사용자 수동 작업 또는 결과 확인을 기다리는 상태
- `완료`: 구현 및 현재 확인 모드 기준 확인 완료

## 최근 작업 로그
- 2026-08-05: 01-1 구현 코드 추가. `PrototypeRoom`과 `FixedRoomCamera`를 분리하고, 큐브 플레이어 Pawn 및 기본 GameMode/Input 설정을 추가했다. 수동 에디터 배치와 PIE 결과 확인 대기 중.
- 2026-08-05: 01-1 컴파일 오류 대응. `ConstructorHelpers.h` include 경로를 `UObject/ConstructorHelpers.h`로 수정했다.
- 2026-08-05: 01-1 결과 확인 보정. 조명이 없어 확인이 불가능해 `PrototypeRoom`에 방 내부 확인용 기본 PointLight를 추가했다.
- 2026-08-05: 01-1 화면 미표시 원인 대응. `FixedRoomCamera` 기본 위치와 회전을 방 중심을 바라보도록 수정했다.
- 2026-08-05: 01-1 카메라 시점 확인 보정. PIE 시작 시 `FixedRoomCamera`가 즉시 ViewTarget이 되도록 전환 파라미터를 명시했다.
- 2026-08-05: 01-1 조명 단순화. 확인용 기본 조명을 PointLight에서 DirectionalLight로 변경했다.
- 2026-08-05: 01-1 카메라 방향 보정. `FixedRoomCamera`가 에디터 배치 중에도 `TargetLocation`을 바라보도록 `OnConstruction` 회전 갱신을 추가했다.
- 2026-08-05: 01-1 결과 확인 완료. 사용자 확인에 따라 PlayerStart 배치와 PIE 결과 확인 항목을 완료 처리하고 단계 상태를 완료로 변경했다.
