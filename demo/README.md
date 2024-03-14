# Demo

## Generate Project Files

```zsh
/Users/Shared/Epic\ Games/UE_4.26/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh -project="$(pwd)/demo/Demo.uproject"
```

## Unreal Custom Widgets [:link:](https://snorristurluson.github.io/CustomSlateWidgets/)

## Delegates [:link:](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/)

  | Type | Description |
  |---|---|
  | Single | 가장 기본적인 Delegate 로 함수 1개를 바인드하여 사용합니다. |
  | Multicast | Single Delegate 와 동일하지만 여러 함수를 바인드 할 수 있습니다. |
  | └─ Events | Multicast Delegate 와 동일하지만 전역으로 설정할 수 없어 외부 클래스에서 추가 Delegate 선언이 불가능합니다. |
  | Dynamic | |
