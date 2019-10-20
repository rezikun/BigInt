#include "pch.h"
#include "../BigInt/big_int.h"

namespace big_int {

	TEST(AdditionTest, SimpleAddition) {
		EXPECT_EQ(BigInt("3"), BigInt("1") + BigInt("2"));
		EXPECT_EQ(BigInt("10"), BigInt("5") + BigInt("5"));
		EXPECT_EQ(BigInt("188"), BigInt("99") + BigInt("89"));
		EXPECT_EQ(BigInt("24"), BigInt("23") + BigInt("1"));
		EXPECT_EQ(BigInt("33"), BigInt("5") + BigInt("28"));
		EXPECT_EQ(BigInt("246913578246913578246913578"),
			BigInt("123456789123456789123456789") + BigInt("123456789123456789123456789"));
		EXPECT_EQ(BigInt("23"), BigInt("-5") + BigInt("28"));
		EXPECT_EQ(BigInt("-33"), BigInt("-5") + BigInt("-28"));
	}

	TEST(SubtractionTest, SimpleSubtraction) {
		EXPECT_EQ(BigInt("-1"), BigInt("1") - BigInt("2"));
		EXPECT_EQ(BigInt("0"), BigInt("5") - BigInt("5"));
		EXPECT_EQ(BigInt("9"), BigInt("98") - BigInt("89"));
		EXPECT_EQ(BigInt("22"), BigInt("23") - BigInt("1"));
		EXPECT_EQ(BigInt("-23"), BigInt("5") - BigInt("28"));
		EXPECT_EQ(BigInt("-111111110211111110211111111"),
			BigInt("12345678912345678912345678") - BigInt("123456789123456789123456789"));
		EXPECT_EQ(BigInt("-24"), BigInt("-23") - BigInt("1"));
		EXPECT_EQ(BigInt("23"), BigInt("-5") - BigInt("-28"));
	}

	TEST(MultiplicationTest, SimpleMultiplication) {
		EXPECT_EQ(BigInt("-1"), BigInt("1") * BigInt("-1"));
		EXPECT_EQ(BigInt("0"), BigInt("5") * BigInt("0"));
		EXPECT_EQ(BigInt("882"), BigInt("98") * BigInt("9"));
		EXPECT_EQ(BigInt("23"), BigInt("23") * BigInt("1"));
		EXPECT_EQ(BigInt("-23"), BigInt("-23") * BigInt("1"));
		EXPECT_EQ(BigInt("140"), BigInt("-5") * BigInt("-28"));
		EXPECT_EQ(BigInt("1000000000000000000000000000000000000000000"),
			BigInt("100000000000000000000000000000000000000000") *
			BigInt("10"));
	}

	TEST(DivisionTest, SimpleDivision) {
		EXPECT_EQ(BigInt("-1"), BigInt("1") / BigInt("-1"));
		EXPECT_EQ(BigInt("0"), BigInt("5") / BigInt("7"));
		EXPECT_EQ(BigInt("10"), BigInt("98") / BigInt("9"));
		EXPECT_EQ(BigInt("23"), BigInt("23") / BigInt("1"));
		EXPECT_EQ(BigInt("-23"), BigInt("-23") / BigInt("1"));
		EXPECT_EQ(BigInt("0"), BigInt("-5") / BigInt("-28"));
		EXPECT_EQ(BigInt("6272110"), BigInt("12345678123012") / BigInt("1968345"));
		EXPECT_EQ(BigInt(4120227), (BigInt(8240455))/2);
		EXPECT_EQ(BigInt("1000"),
			BigInt("1000000000000000000000000000000000000000000") /
			BigInt("1000000000000000000000000000000000000000"));
		EXPECT_EQ(BigInt("-5"), BigInt("-5") % BigInt("-28"));
		EXPECT_EQ(BigInt("5"), BigInt("5") % BigInt("28"));
		EXPECT_EQ(BigInt("0"), BigInt("5") % BigInt("5"));
	}
	TEST(PowTest, SimplePow) {
		EXPECT_EQ(BigInt(1), BigInt(1).pow(BigInt(2)));
		EXPECT_EQ(BigInt(4), BigInt(2).pow(BigInt(2)));
		EXPECT_EQ(BigInt(27), BigInt(3).pow(BigInt(3)));
		EXPECT_EQ(BigInt("1606938044258990275541962092341162602522202993782792835301376"
			"000000000000000000000000000000000000000000000000000000000000000000000000000"
			"000000000000000000000000000000000000000000000000000000000000000000000000000"
			"000000000000000000000000000000000000000000000000000000000000000000000000000"
			"000000000000000000000000000000000000000000000000000000000000000000000000000"
			"000000000000000000000000000000000000000000000000000000000000000000000000000"
			"0000000000000000000000000"), BigInt(200).pow(BigInt(200)));
	}
	//TEST(WsqrtTest, SimpleWsqrt) {
		//EXPECT_EQ(BigInt(1), BigInt(1).wsqrt());
		//EXPECT_EQ(BigInt(2), BigInt(4).wsqrt());
		//EXPECT_EQ(BigInt(2), BigInt(5).wsqrt());
		//EXPECT_EQ(BigInt(11), BigInt(122).wsqrt());
		//EXPECT_EQ(BigInt("3513641830401"),
		//			BigInt("123456789123456789123456789123456789").wsqrt());
	//}
} //  namespace big_int