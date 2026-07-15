# 260710 발표 작업 컨텍스트

## 발표 주제

- 제목: `CIL-- 합성을 통한 Sparrow 분석기 공격`
- 발표일: 2026년 7월 10일
- 핵심 목표: `CIL--` 프로그램과 Big-Step 증명나무를 합성해서 Sparrow 분석기의 한계를 공격한다.
- 공격 방향:
  - completeness 공격: abstract semantics가 concrete semantics를 너무 크게 포함하는 예시를 찾는다.
  - soundness 공격: concrete semantics가 abstract semantics에 포함되지 않는 버그성 예시를 찾는다.

## 원래 연구 프로젝트 요약

- Sparrow는 C 프로그램을 CIL로 변환하고, 다시 CFG 위에서 정적분석을 수행한다.
- 연구 프로젝트는 Sparrow를 직접 실행해서 반례를 손으로 찾는 대신, 작은 언어 `CIL--`와 그 Big-Step 실행의미를 정의하고, 실행 증명나무를 bottom-up으로 합성해 공격 프로그램을 찾는 방향이다.
- `CIL--`는 현재 최소 언어로 잡는다.
  - 남기는 것: 정수 중심의 기본 표현식, statement, 조건문/반복문, 함수 호출, stack frame 기반 메모리
  - 일단 제거하는 것: 포인터, malloc/free, 배열, int 외 타입 등
- soundness 공격을 하려면 공격기에서 쓰는 concrete semantics와 Sparrow가 암묵적으로 보는 concrete semantics가 어긋나면 안 된다.
  - 그래서 C의 비결정성/undefined/implementation-dependent 성격을 CIL/CIL-- 단계에서 제거하거나 언어 밖으로 빼는 것이 중요하다.
- completeness 공격은 Rice theorem/undecidability 관점에서, 충분히 표현력 있는 subset 위에서 sound하면서 complete한 정적분석은 불가능하다는 방향을 이용한다.
- 합성은 프로그램 텍스트만 만드는 것이 아니라 메모리 전후 상태를 함께 다룬다.
  - 부분 프로그램은 자체적으로 메모리를 결정하지 않고 전/후 메모리 관계만 가진다.
  - loop/condition/call을 조립하려면 작은 증명나무 단계에서 전후 메모리를 확실히 들고 있어야 한다.
  - 현재 설명은 heap이 아니라 stack frame 중심으로 간다.

## 지금까지 한 발표 작업

- `260515` 폴더를 복사해 `260710` 발표 폴더를 만들었다.
- 발표에서 쓰지 않을 이미지/중간 파일을 정리했다.
- 본문 이미지는 제거했고, 로고 이미지 정도만 남겨두었다.
- 제목/날짜/section 뼈대를 잡았다.
- `CIL--` 표기를 위한 매크로를 추가했다.
  - 현재 정의:
    ```tex
    \newcommand{\CILmm}{\texorpdfstring{CIL-\kern0.08em-}{CIL--}}
    ```
  - 주의: `texorpdfstring`의 두 번째 인자에는 절대 `\CILmm{}`를 넣으면 안 된다. 무한 재귀로 빌드가 깨진다.
- `C 언어의 비결정성` 표를 작성했다.
  - 4열 구조: `예`, `C`, `CIL`, `CIL--`
  - `CIL--` 칸에는 현재 제거/허용 여부를 간단히 적는다.
  - 행 사이에 희미한 구분선 매크로 `\fainttablerow`를 사용한다.
- 표의 `sizeof` 예시는 `sizeof(int (*)[n++])`로 바꿨다.
  - 이유: `sizeof` 안에서 VLA 관련 size expression 평가 여부가 unspecified인 예시로 더 적절하다.
- 빌드 확인은 `260710`에서 아래 명령으로 했다.
  ```sh
  xelatex -synctex=1 -interaction=nonstopmode -file-line-error simplesnt-doc.tex
  ```
- 현재 빌드는 성공한다.

## 현재 발표 파일 상태

- 메인 파일: `260710/simplesnt-doc.tex`
- PDF 출력: `260710/simplesnt-doc.pdf`
- 현재 슬라이드 흐름:
  1. 표지
  2. 목차
  3. Sparrow 분석기 공격 목표
  4. Sparrow 기본 구조
  5. CIL / CIL-- 언어
  6. Big-Step 기본 구조
  7. Sparrow 실행의미와 공격기 실행의미 대응 문제
  8. C 언어의 비결정성 표
  9. 메모리를 포함하여 합성하는 이유
  10. 조건문/반복문에서 메모리 조립 문제
  11. 합성 시 메모리 관리
  12. stack frame 관리
  13. 앞으로 할 일
  14. 감사합니다

## 다음 세션에서 할 일

- 발표자료를 본격적으로 다듬는다.
- 우선순위:
  1. 그림부터 잡기
     - completeness/soundness 공격 그림
     - Sparrow의 `C -> CIL -> CFG` 흐름과 공격기의 `CIL-- -> Big-Step tree` 흐름 비교 그림
     - Big-Step 증명나무 기본 구조
     - 메모리 전후 상태를 붙여 증명나무를 조립하는 그림
     - stack frame 전체를 들고 다니는 방식 vs top frame 중심 방식 그림
  2. 각 슬라이드 문장을 발표용 문장으로 완성
     - 지금은 메모/구어체가 많다.
     - 내용상 큰 구조는 유지하고, 그림 옆에 1-3줄 정도로 줄인다.
  3. 코드 예시 스타일 통일
     - 현재 plain text 코드가 많다.
     - `lstlisting` 또는 간단한 박스 스타일로 통일하는 것이 좋다.
  4. 표 정리
     - 표는 현재 내용 전달용으로는 괜찮다.
     - 그림과 문장 정리 후 글씨 크기, 행간, 열 너비를 마지막에 다시 조정한다.
  5. 전체 빌드 및 PDF 확인

## 다음 작업 시 주의점

- 사용자는 `비결정성`이라는 용어를 유지하려고 한다.
  - `undefined`, `unspecified`, `implementation-defined`, `indeterminate`가 엄밀히는 다르지만, 발표에서는 넓은 의미의 비결정성으로 묶어 설명한다.
- stack frame 부분은 `stack만 본다`는 방향으로 간다.
- `CIL, 혹은 CIL--에서는 모든 변수가 외딴섬`이라는 표현은 일단 유지한다.
  - 엄밀히는 CIL 일반보다 현재 쓰는 subset/CIL--에 가까운 설명이다.
- `completeness 공격의 종료 보장` 표현도 사용자가 의도한 설명이 있으므로 임의로 약화하지 않는다.
- 구어체/메모체는 다음 단계에서 다듬을 예정이므로, 지금 당장 내용 검수 단계에서 과하게 고치지 않는다.
- 사용자가 직접 고친 내용을 임의로 갈아엎지 말 것.
