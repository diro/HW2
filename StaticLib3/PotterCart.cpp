#include "stdafx.h"
#include "PotterCart.h"
#include <climits>


PotterCart::PotterCart()
{
}


PotterCart::~PotterCart()
{
}

void PotterCart::AddToCart(const ShoppingItem& items)
{
	m_shoppingItem = items;
}

int PotterCart::estimateSpecifiedPackageMaxNumber(int packageSize)
{
	int totalBooks = 0;
	for (const auto& pair : m_shoppingItem.episodeCountList)
	{
		totalBooks += pair.second;
	}

	auto tmpShoppingItem = m_shoppingItem;

	int packageAmount = 0;
	
	for (int i = 0; i < totalBooks; i++)
	{
		int gotCount = 0;
		int allowedEmpty = 5 - packageSize;
		for (auto& pair : tmpShoppingItem.episodeCountList)
		{
			if (pair.second-- <= 0)
			{
				if (allowedEmpty == 0)
				{
					return packageAmount;
				}
				else
				{
					allowedEmpty--;
				}
			}
			else
			{
				gotCount++;
			}

			if (gotCount == packageSize)
			{
				packageAmount++;
				break;
			}
		}
	}
	return packageAmount;
}


double PotterCart::calculateTotalPrice(int totalBooks, int numOfPackage5, int numOfPackage4, int numOfPackage3,
	int numOfPackage2)
{
	int numOfPackage1 = totalBooks - calculateTotalBooksByAllPackages(numOfPackage5, numOfPackage4, numOfPackage3,  numOfPackage2);
	
	return	numOfPackage5 * 500 * 0.75 +
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
						const int currentPrice = calculateTotalPrice(totalBooks, numOfPackage5, numOfPackage4, numOfPackage3, numOfPackage2);
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

