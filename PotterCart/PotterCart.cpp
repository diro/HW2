#include "stdafx.h"
#include "PotterCart.h"
#include <climits>

void PotterCart::AddToCart(const ShoppingItem& items)
{
	m_shoppingItem = items;
}

int PotterCart::estimateSpecifiedPackageMaxNumber(const int packageSize)
{
	if (packageSize > m_shoppingItem.episodeCountList.size())
		return 0;

	int totalBooks = calculateTotalBooks();

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


double PotterCart::calculateTotalPrice(int totalBooks, int numOfPackage5, int numOfPackage4, int numOfPackage3,
                                       int numOfPackage2)
{
	int numOfPackage1 = totalBooks - calculateTotalBooksByAllPackages(numOfPackage5, numOfPackage4, numOfPackage3,
	                                                                  numOfPackage2);

	return numOfPackage5 * 500 * 0.75 +
		numOfPackage4 * 400 * 0.8 +
		numOfPackage3 * 300 * 0.9 +
		numOfPackage2 * 200 * 0.95 +
		numOfPackage1 * 100;
}

int PotterCart::calculateTotalBooks()
{
	int totalBooks = 0;

	for (const auto& pair : m_shoppingItem.episodeCountList)
	{
		totalBooks += pair.second;
	}

	return totalBooks;
}

int PotterCart::calculateTotalBooksByAllPackages(int numOfPackage5, int numOfPackage4, int numOfPackage3,
                                                 int numOfPackage2)
{
	return numOfPackage5 * 5 + numOfPackage4 * 4 + numOfPackage3 * 3 + numOfPackage2 * 2;
}

int PotterCart::GetTotal()
{
	int totalBooks = calculateTotalBooks();

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
					if (calculateTotalBooksByAllPackages(numOfPackage5, numOfPackage4, numOfPackage3, numOfPackage2) <= totalBooks)
					{
						const int currentPrice = calculateTotalPrice(totalBooks, numOfPackage5, numOfPackage4, numOfPackage3,
						                                             numOfPackage2);
						if (currentPrice < lowestPrice)
						{
							lowestPrice = currentPrice;
						}
					}
				}
			}
		}
	}

	return lowestPrice;
}
