#pragma once
#include <map>

typedef std::map<char, int> VolumeCount;

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
	int estimateSpecifiedPackageMaxNumber(const int packageSize);
	double calculateTotalPrice(int totalBooks, int numOfPackage5, int numOfPackage4, int numOfPackage3, int numOfPackage2);
	int calculateTotalBooks();
	int calculateTotalBooksByAllPackages(int numOfPackage5, int numOfPackage4, int numOfPackage3, int numOfPackage2);

	::ShoppingItem m_shoppingItem;
};
