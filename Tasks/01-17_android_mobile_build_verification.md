# Task 01-17 - Android 모바일 빌드 전환과 기기 실행 확인

## 설명
현재 프로토타입을 Android 모바일 빌드 대상으로 전환하고, 모바일 화면과 입력 조건에서 핵심 플레이가 실행 가능한지 확인한다. 자동 공격 전환 이후 보스전 같은 확장 기능을 넣기 전에 Android 빌드, 실행, 화면 가독성, 현재 조작 구조의 모바일 적합성을 먼저 확인한다.

## 구현 항목
- [x] Unreal 프로젝트의 Android 플랫폼 설정이 준비된다.
- [x] Android 빌드 또는 패키징을 시도할 수 있는 프로젝트 설정이 준비된다.
- [x] 실제 Android 기기 또는 에뮬레이터에서 프로젝트를 실행할 수 있다.
- [x] 모바일 화면 비율에서 체력, 점수, 공격 쿨타임 표시를 읽을 수 있도록 HUD 스케일 보정이 준비된다.
- [x] PC 키보드/마우스 입력과 Android 기본 가상 조이스틱 입력이 별도 축 이름과 플랫폼별 바인딩 경로로 분리된다.
- [x] Android landscape 화면에서 모바일 방향 전환 입력만 보정할 수 있는 컴포넌트가 준비된다.
- [x] 자동 공격이 모바일 환경에서도 별도 공격 버튼 없이 발동된다.

## 범위 밖
- Google Play 출시
- 광고
- 결제
- 최종 최적화
- 모바일 전용 터치 UI 대개편
- 보스전 추가
- 그래픽 품질 세부 튜닝

## 사전 전제
- 01-16의 자동 공격 전환과 쿨타임 시각화가 구현되어 있다.
- 01-16의 이동과 방향 전환 중심 조작 흐름이 확인되어 있다.
- 01-13의 체력, 점수, 음식 획득 흐름이 구현되어 있다.
- 01-14의 게임오버 상태 정지 처리가 구현되어 있다.

## 수동 작업
- Unreal Editor에서 C++ 변경 사항을 컴파일한다.
- Unreal Editor에서 Android SDK, NDK, JDK 경로가 유효한지 확인한다.
- Project Settings의 Android 항목에서 패키지명이 `com.studio.hungryhero`로 표시되는지 확인한다.
- Android 빌드 설정에서 ARM64, landscape 방향, APK 내부 데이터 포함 설정이 적용되어 있는지 확인한다.
- Android 기기 또는 에뮬레이터를 준비하고 개발자 모드와 USB 디버깅을 켠다.
- 기존 `Content/Blueprints/BP_PlayerCharacter` Blueprint를 열고 inherited component 변경 사항이 반영되어 있는지 확인한 뒤 Blueprint를 컴파일하고 저장한다.
- Android 기기에서 방향 전환 입력이 90도 어긋나면 `BP_PlayerCharacter`의 `MobileInputOrientationComponent`에서 `Android Landscape Input Yaw Offset Degrees` 값을 기본 `0.0`으로 되돌린다.
- Android 기기에서 방향 전환 입력의 좌우는 맞지만 위아래가 뒤집히면 `MobileFaceForward`의 `Gamepad_RightY` 축 스케일이 `-1.0`인지 확인한다.
- Android 기기에서 왼쪽 가상 스틱 이동과 오른쪽 가상 스틱 방향 전환이 서로 영향을 주지 않는지 확인한다.
- Mac 빌드에서는 `MouseFaceForward`/`MouseFaceRight`만 방향 전환 입력으로 바인딩되고, Android 빌드에서는 `MobileFaceForward`/`MobileFaceRight`만 방향 전환 입력으로 바인딩되는지 확인한다.

## 완료 조건

### 에이전트 확인
- [x] 관련 코드 수정 완료
- [x] 로컬 정적 점검 또는 프로젝트 구조 기준 확인 완료
- [x] Unreal C++/Blueprint/에셋 규칙 위반 없음
- [x] 현재 task 문서가 실제 구현 기준으로 갱신됨

### 결과 확인
- [x] Unreal Editor에서 `Content/Maps/L_PrototypeRoom` 맵을 연다.
- [x] Android 패키징을 실행했을 때 패키징이 완료되는지 확인한다.
- [x] Android 기기 또는 에뮬레이터에 설치한 뒤 앱이 실행되는지 확인한다.
- [x] 모바일 화면 비율에서 체력, 점수, 공격 쿨타임 표시가 읽히는지 확인한다.
- [x] 모바일 기본 터치 인터페이스 또는 연결된 입력 장치로 이동과 방향 전환이 가능하고, landscape 화면에서 방향이 90도 어긋나지 않는지 확인한다.
- [x] PC 마우스 방향 전환과 Android 오른쪽 가상 스틱 방향 전환이 서로 다른 입력 경로로 동작하는지 확인한다.
- [x] 일반 동물이 플레이어 공격 범위 안에 들어오면 별도 공격 버튼 없이 자동 공격이 발동되는지 확인한다.
- [x] 자동 공격 후 1초 쿨타임 표시가 줄어들고 다시 `Attack Ready` 상태로 돌아오는지 확인한다.
- [x] 체력 감소, 음식 획득, 점수 증가, 게임오버 정지 흐름이 Android 실행에서도 기존처럼 유지되는지 확인한다.
- [x] Google Play 출시, 광고, 결제, 최종 최적화, 모바일 전용 터치 UI 대개편, 보스전 추가, 그래픽 품질 세부 튜닝이 새로 나타나지 않는지 확인한다.
