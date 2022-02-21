#pragma once

#include "UdSDKDefine.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SHeaderRow.h"

class FArguments;
class ITableRow;
class STableViewBase;

template <typename ItemType> class SListView;

class SUdSDKAssetsPanel : public SCompoundWidget {
  SLATE_BEGIN_ARGS(SUdSDKAssetsPanel) {}
  SLATE_END_ARGS()

  SUdSDKAssetsPanel();
  virtual ~SUdSDKAssetsPanel();
  void Construct(const FArguments& InArgs);
  void Refresh();

  virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
  TSharedRef<SWidget> AssetDetails();
  TSharedRef<ITableRow> CreateAssetRow(TSharedPtr<FUdAsset> item, const TSharedRef<STableViewBase>& list);
  void AddAssetToLevel(TSharedPtr<FUdAsset> item);
  void AddAsset(TSharedPtr<FUdAsset> item);
  void AssetSelected(TSharedPtr<FUdAsset> item, ESelectInfo::Type selectionType);

  void ApplyFilter();
  void ApplySorting();
  void OnSortChange(EColumnSortPriority::Type SortPriority, const FName& ColumnName, EColumnSortMode::Type NewSortMode);
  void OnSearchTextChange(const FText& SearchText);

  FDelegateHandle LoginDelegateHandle;
  FDelegateHandle ExitDelegateHandle;
  TSharedPtr<SListView<TSharedPtr<FUdAsset>>> PListView;
  TArray<TSharedPtr<FUdAsset>> Assets;
  TSharedPtr<FUdAsset> PSelection;

  FName SortColumnName;
  EColumnSortMode::Type SortMode = EColumnSortMode::Type::None;
  TSharedPtr<SSearchBox> SearchBox;
  FString SearchString;
};
