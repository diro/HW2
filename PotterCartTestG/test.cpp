#include "pch.h"
#include "../PotterCart/PotterCart.h"


TEST(PotterCart, buy_1_vol1_total_should_be_100dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 1));
	sut.AddToCart(items);

	int actual = sut.GetTotal();
	
	int expected = 100;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart,buy_1_vol2_total_should_be_100dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('2', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 100;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_1_vol3_total_should_be_100dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('3', 1));
	sut.AddToCart(items);

	int actual = sut.GetTotal();
	
	int expected = 100;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_1_vol4_total_should_be_100dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('4', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 100;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_1_vol5_total_should_be_100dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('5', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 100;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_2_different_total_should_be_190dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 1));
	items.episodeCountList.insert(std::make_pair('2', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 190;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_3_different_total_should_be_270dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 1));
	items.episodeCountList.insert(std::make_pair('2', 1));
	items.episodeCountList.insert(std::make_pair('3', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 270;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_4_different_total_should_be_320dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 1));
	items.episodeCountList.insert(std::make_pair('2', 1));
	items.episodeCountList.insert(std::make_pair('3', 1));
	items.episodeCountList.insert(std::make_pair('5', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 320;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_5_different_total_should_be_375dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 1));
	items.episodeCountList.insert(std::make_pair('2', 1));
	items.episodeCountList.insert(std::make_pair('3', 1));
	items.episodeCountList.insert(std::make_pair('4', 1));
	items.episodeCountList.insert(std::make_pair('5', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 375;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_2vol1_and1_vol2_total_should_be_290dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 2));
	items.episodeCountList.insert(std::make_pair('2', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 290;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_2vol1_and2_vol2_total_should_be_380dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 2));
	items.episodeCountList.insert(std::make_pair('2', 2));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 380;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart, buy_3vol1_and1_vol2_total_should_be_390dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 3));
	items.episodeCountList.insert(std::make_pair('2', 1));
	sut.AddToCart(items);
	
	int actual = sut.GetTotal();
	
	int expected = 390;
	ASSERT_EQ(expected, actual);
}

TEST(PotterCart,buy_8_different_total_should_be_640dollars)
{
	PotterCart sut;
	ShoppingItem items;
	items.episodeCountList.insert(std::make_pair('1', 2));
	items.episodeCountList.insert(std::make_pair('2', 2));
	items.episodeCountList.insert(std::make_pair('3', 2));
	items.episodeCountList.insert(std::make_pair('4', 1));
	items.episodeCountList.insert(std::make_pair('5', 1));
	sut.AddToCart(items);

	int actual = sut.GetTotal();

	int expected = 640;
	ASSERT_EQ(expected, actual);
}
