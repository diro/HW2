#pragma once
#include <map>

typedef std::map<char, int> VolumeCount;
typedef std::map<int, int> PackageNumberInfo;

class ShoppingItem
{
public:
	VolumeCount episodeCountList;
};

class PotterCart
{
public:
	PotterCart() = default;
	~PotterCart() = default;
	void AddToCart(const ShoppingItem& items);
	int GetTotal();

private:
	void estimateCheapestPackagePlan(ShoppingItem items, int packageSize, PackageNumberInfo packageNumberInfo);

	bool removePackageInShoppingItem(const int packageSize, ShoppingItem& shoppingItem);
	int estimateSpecifiedPackageMaxNumber(const int packageSize, ShoppingItem shoppingItem);

	double calculateTotalPrice(int totalBooks, PackageNumberInfo packageNumberInfo);
	int calculateTotalBooksInCart(const ShoppingItem& shoppingItem);
	int calculateTotalPackageBooks(PackageNumberInfo packageNumberInfo);


	::ShoppingItem m_shoppingItem;
	int m_lowestPrice = INT_MAX;
};
