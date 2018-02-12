#include "stdafx.h"
#include "PotterCart.h"
#include <climits>

void PotterCart::AddToCart(const ShoppingItem& items)
{
	m_shoppingItem = items;
	m_lowestPrice = INT_MAX;

	PackageNumberInfo packageNumberInfo;
	estimateCheapestPackagePlan(m_shoppingItem, 5, packageNumberInfo);
}

bool PotterCart::removePackageInShoppingItem(const int packageSize, ShoppingItem& shoppingItem)
{
	int removeCount = 0;
	auto tmpShoppingItem = shoppingItem;
	for (auto& pair : tmpShoppingItem.episodeCountList)
	{
		if (pair.second >= 1)
		{
			pair.second--;
			removeCount++;
		}

		if (removeCount == packageSize)
		{
			shoppingItem = tmpShoppingItem;
			return true;
		}
	}

	return false;
}


int PotterCart::estimateSpecifiedPackageMaxNumber(const int packageSize, ShoppingItem shoppingItem)
{
	if (packageSize > m_shoppingItem.episodeCountList.size())
		return 0;

	int totalBooks = calculateTotalBooksInCart(shoppingItem);

	auto estimatedShoppingItem = shoppingItem;

	int packageNumber = 0;

	for (int i = 0; i < totalBooks; i++)
	{
		int currentPackageSize = 0;
		int remainingEmptyNumber = estimatedShoppingItem.episodeCountList.size() - packageSize;

		for (auto& pair : estimatedShoppingItem.episodeCountList)
		{
			pair.second--;
			if (pair.second < 0)
			{
				if (remainingEmptyNumber == 0)
				{
					return packageNumber;
				}
				remainingEmptyNumber--;
			}
			else
			{
				currentPackageSize++;
			}

			if (currentPackageSize == packageSize)
			{
				packageNumber++;
				break;
			}
		}
	}

	return packageNumber;
}


double PotterCart::calculateTotalPrice(int totalBooks, PackageNumberInfo packageNumberInfo)
{
	int numOfPackage1 = totalBooks - calculateTotalPackageBooks(packageNumberInfo);

	return packageNumberInfo.at(5) * 500 * 0.75 +
		packageNumberInfo.at(4) * 400 * 0.8 +
		packageNumberInfo.at(3) * 300 * 0.9 +
		packageNumberInfo.at(2) * 200 * 0.95 +
		(totalBooks - calculateTotalPackageBooks(packageNumberInfo)) * 100;
}

int PotterCart::calculateTotalBooksInCart(const ShoppingItem &shoppingItem)
{
	int totalBooks = 0;

	for (const auto& pair : shoppingItem.episodeCountList)
	{
		totalBooks += pair.second;
	}

	return totalBooks;
}

int PotterCart::calculateTotalPackageBooks(PackageNumberInfo packageNumberInfo)
{
	auto totalBooks = 0;
	for (const auto& pair : packageNumberInfo)
	{
		totalBooks += pair.first * pair.second;
	}

	return totalBooks;
}

void PotterCart::estimateCheapestPackagePlan(ShoppingItem items, int packageSize, PackageNumberInfo packageNumberInfo)
{
	if (packageSize == 1)
	{
		int price = calculateTotalPrice(calculateTotalBooksInCart(m_shoppingItem), packageNumberInfo);
		if (price < m_lowestPrice)
		{
			m_lowestPrice = price;
		}
		return;
	}

	int maxNumberOfPackage = estimateSpecifiedPackageMaxNumber(packageSize, items);
	for (int numOfPackage = 0; numOfPackage <= maxNumberOfPackage; numOfPackage++)
	{
		PackageNumberInfo info = packageNumberInfo;
		ShoppingItem remainingShoppingItem = items;
		for (int i = 0; i < numOfPackage; i++)
		{
			removePackageInShoppingItem(packageSize, remainingShoppingItem);
		}
		info.insert(std::make_pair(packageSize, numOfPackage));
		estimateCheapestPackagePlan(remainingShoppingItem, packageSize - 1, info);
	}
}

int PotterCart::GetTotal()
{
	return m_lowestPrice;
}
