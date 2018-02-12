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
	bool removePackageInShoppingItem(const int packageSize, ShoppingItem& shoppingItem);
	bool isValidPackage(PackageNumberInfo packageNumberInfo);
	int GetTotal();

private:
	int estimateSpecifiedPackageMaxNumber(const int packageSize);
	double calculateTotalPrice(int totalBooks, PackageNumberInfo packageNumberInfo);
	int calculateTotalBooksInCart();
	int calculateTotalPackageBooks(PackageNumberInfo packageNumberInfo);

	::ShoppingItem m_shoppingItem;
};
