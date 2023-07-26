#include <gtest/gtest.h>
#include "../include/TextureManager.h"

struct TestManager : public ::testing::Test {
	TextureManager* instance;
	void SetUp() override {
		instance = TextureManager::GetInstance();
	}
	void TearDown() override { 
		instance->Clear();
	}
};

TEST_F(TestManager, LoadTexture) {
	uint32_t ID = instance->Loadtexture("../media/doom.png");
	EXPECT_NE(ID, TextureManager::Error);
}

TEST_F(TestManager, LoadTextureWithID) {
	uint32_t ID = instance->Loadtexture("../media/doom.png");
	EXPECT_EQ(ID, 1);
}

TEST_F(TestManager, LoadTextureWithID2) {
	uint32_t ID = instance->Loadtexture("../media/doom.png", 1);
	EXPECT_NE(ID, 2);
}

TEST_F(TestManager, LoadTextureWithID3) {
	uint32_t ID = instance->Loadtexture("../media/doom.png", 1);
	instance->DeleteTexture(1);
	ID = instance->Loadtexture("../media/doom.png", 1);
	EXPECT_EQ(ID, 1);
}

int main (int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
