#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "OPItemTypes.generated.h"

// 아이템 종류 구분 열거형 (데이터 분리, 임시로 작성 추후 변경될 것 같음)
UENUM(BlueprintType)
enum class EItemType : uint8
{
    None          UMETA(DisplayName = "None"),
    Key           UMETA(DisplayName = "Key Item"),   // 퀘스트 아이템
    Consumable    UMETA(DisplayName = "Consumable"), // 소비 아이템
    Equipment     UMETA(DisplayName = "Equipment")   // 장착 아이템
};

// 데이터 테이블 및 데이터 에셋에서 사용할 아이템 정보 구조체
USTRUCT(BlueprintType)
struct FOPItemRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    FOPItemRow()
        : ItemId(NAME_None), ItemType(EItemType::None){}

    // 아이템 고유 ID (데이터 관리용)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    FName ItemId;

    // 위에서 만든 열거형 적용 (데이터 드리븐)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    EItemType ItemType;

    // 화면에 표시될 이름
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    FText DisplayName;

    // 인벤토리 등 UI에서 보일 아이콘
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
    TObjectPtr<UTexture2D> Icon = nullptr;

    // 아이템 설명 (이것도 추후 삭제할 수도 있음)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (MultiLine = true))
    FText Description;
};