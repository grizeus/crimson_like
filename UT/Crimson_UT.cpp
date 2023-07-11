#include <gtest/gtest.h>

// struct TestCalc : public ::testing::Test {
// 	Calculator* calc;
// 	void SetUp() override {
// 		ToolsPtr tools (new SDL_Tools());
// 		calc = new Calculator(tools); 
// 	}
// 	void TearDown() override { 
// 		delete calc; 
// 	}
// };

int main (int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
