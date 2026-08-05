# Task 01-5 - 플레이어 Blueprint 관리 준비

## 설명
기존 플레이어 C++ 동작은 유지하면서, 테스트 맵에서 플레이어를 Blueprint 기반으로 관리할 수 있게 준비한다. 플레이어 기반 클래스는 모델과 애니메이션 연결에 적합한 `ACharacter` 계열 C++ 클래스로 전환하고, GameMode는 플레이어 클래스 직접 지정 책임과 분리한다. 이후 모델, 머티리얼, 애니메이션, 컴포넌트 연결은 Blueprint에서 조정할 수 있어야 하며, 핵심 입력과 기본 동작은 C++ 책임으로 유지한다.

## 구현 항목
- [x] 기존 플레이어 C++ 이동, 회전, 공격 입력 동작이 새 플레이어 Character에서 유지된다.
- [x] 플레이어 기반 C++ 클래스가 `ACharacter` 계열 클래스로 준비된다.
- [x] 기존 플레이어 Pawn 클래스는 제거된다.
- [x] GameMode는 기본 플레이어 클래스를 C++에서 직접 지정하지 않는다.
- [x] 플레이어 Blueprint를 테스트 맵의 기본 플레이어로 사용할 수 있다.
- [x] 이후 외형, 머티리얼, 애니메이션, 컴포넌트 연결을 Blueprint에서 조정할 수 있게 준비된다.
- [x] 핵심 입력과 기본 동작은 C++에 두고, 외형과 에디터 조정 책임은 Blueprint에서 관리할 수 있게 분리된다.

## 범위 밖
- 최종 캐릭터 모델
- 애니메이션 Blueprint
- 체력
- 적
- 음식
- 점수

## 사전 전제
- `Tasks/01-4_movement_facing_priority.md`의 마우스 이동 방향 회전 유지 검증 산출물

## 수동 작업 (구현 후 구체화)
1. Unreal Editor에서 C++ 변경 사항을 컴파일한다.
2. `AHungryHeroPlayerCharacter`를 부모 클래스로 하는 Blueprint를 `Content/Blueprints`에 만들고 이름을 `BP_PlayerCharacter`로 지정한다.
3. `AHungryHeroGameMode`를 부모 클래스로 하는 Blueprint를 `Content/Blueprints`에 만들고 이름을 `BP_HungryHeroGameMode`로 지정한다.
4. `BP_HungryHeroGameMode`의 `Default Pawn Class`를 `BP_PlayerCharacter`로 설정한다.
5. 테스트 맵의 `World Settings`에서 `GameMode Override`를 `BP_HungryHeroGameMode`로 설정한다.
6. 테스트 맵을 저장한다.

## 완료 조건

### 에이전트 확인
- [x] 관련 코드 수정 완료
- [x] 로컬 정적 점검 또는 프로젝트 구조 기준 확인 완료
- [x] Unreal C++/Blueprint/에셋 규칙 위반 없음
- [x] 현재 task 문서가 실제 구현 기준으로 갱신됨

### 결과 확인 (구현 후 구체화)
- [x] Unreal Editor에서 저장한 테스트 맵을 연다.
- [x] PIE를 실행했을 때 `BP_PlayerCharacter`가 플레이어로 생성되는지 확인한다.
- [x] PIE에서 플레이어가 기존처럼 `W`, `A`, `S`, `D` 입력으로 방 안에서 움직이는지 확인한다.
- [x] 이동 중 마우스를 움직이지 않았을 때 플레이어가 이동 방향으로 자동 회전하지 않고 현재 바라보는 방향을 유지하는지 확인한다.
- [x] 이동 중 또는 정지 중 마우스를 움직였을 때 플레이어가 마우스 이동 방향을 정면으로 삼아 회전하는지 확인한다.
- [x] `SpaceBar` 또는 마우스 왼쪽 클릭을 눌렀을 때 플레이어가 현재 바라보는 정면 방향에 짧은 칼 공격 표시가 보였다가 사라지는지 확인한다.
- [x] `BP_PlayerCharacter`의 inherited component에서 캡슐, 기본 Skeletal Mesh, 프로토타입 큐브 메시, 공격 컴포넌트를 확인할 수 있는지 확인한다.
- [x] 공격 입력만으로 공격 범위 판정, 적 피격, 체력 감소, 음식 생성, 점수 변화 같은 범위 밖 동작이 발생하지 않는지 확인한다.
