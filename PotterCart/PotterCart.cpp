#include "stdafx.h"
#include "PotterCart.h"
#include <climits>

void PotterCart::AddToCart(const ShoppingItem& items)
{
	m_shoppingItem = items;
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

bool PotterCart::isValidPackage(PackageNumberInfo packageNumberInfo)
{
	auto shoppingItem = m_shoppingItem;
	for (const auto& pair : packageNumberInfo)
	{
		for (int i = 0; i < pair.second; i++)
		{
			if (!removePackageInShoppingItem(pair.first, shoppingItem))
			{
				return false;
			}
		}
	}
}

int PotterCart::estimateSpecifiedPackageMaxNumber(const int packageSize)
{
	if (packageSize > m_shoppingItem.episodeCountList.size())
		return 0;

	int totalBooks = calculateTotalBooksInCart();

	auto estimatedShoppingItem = m_shoppingItem;

	int packageNumber = 0;

	for (int i = 0; i < totalBooks; i++)
	{
		int currentPackageSize = 0;
		int remainingEmptyNumber = m_shoppingItem.episodeCountList.size() - packageSize;

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

int PotterCart::calculateTotalBooksInCart()
{
	int totalBooks = 0;

	for (const auto& pair : m_shoppingItem.episodeCountList)
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

int PotterCart::GetTotal()
{
	int totalBooks = calculateTotalBooksInCart();

	int maxNumberOfPackage5 = estimateSpecifiedPackageMaxNumber(5);
	int maxNumberOfPackage4 = estimateSpecifiedPackageMaxNumber(4);
	int maxNumberOfPackage3 = estimateSpecifiedPackageMaxNumber(3);
	int maxNumberOfPackage2 = estimateSpecifiedPackageMaxNumber(2);

	int lowestPrice = INT_MAX;

	for (int numOfPackage5 = 0; numOfPackage5 <= maxNumberOfPackage5; numOfPackage5++)
	{
		for (int numOfPackage4 = 0; numOfPackage4 <= maxNumberOfPackage4; numOfPackage4++)
		{
			for (int numOfPackage3 = 0; numOfPackage3 <= maxNumberOfPackage3; numOfPackage3++)
			{
				for (int numOfPackage2 = 0; numOfPackage2 <= maxNumberOfPackage2; numOfPackage2++)
				{
					PackageNumberInfo packageNumberInfo;
					packageNumberInfo.insert(std::make_pair(5, numOfPackage5));
					packageNumberInfo.insert(std::make_pair(4, numOfPackage4));
					packageNumberInfo.insert(std::make_pair(3, numOfPackage3));
					packageNumberInfo.insert(std::make_pair(2, numOfPackage2));
					
					if (calculateTotalPackageBooks(packageNumberInfo) > totalBooks)
						continue;
					
					if (!isValidPackage(packageNumberInfo))
						continue;

					const int currentPrice = calculateTotalPrice(totalBooks, packageNumberInfo);
					if (currentPrice < lowestPrice)
					{
						lowestPrice = currentPrice;
					}
				}
			}
		}
	}

	return lowestPrice;
}
