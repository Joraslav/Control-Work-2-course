#include <gtest/gtest.h>
#include "SmartPointer.hpp"

// Test suite for SmartPointer
class SmartPointerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right before the destructor).
    }
};

TEST_F(SmartPointerTest, DefaultConstructor)
{
    SmartPointer<int> sp;
    EXPECT_FALSE(sp);
}

TEST_F(SmartPointerTest, PointerConstructor)
{
    int *data = new int(42);
    SmartPointer<int> sp(data);
    EXPECT_TRUE(sp);
    EXPECT_EQ(*sp.data(), 42);
}

TEST_F(SmartPointerTest, CopyConstructor)
{
    int *data = new int(42);
    SmartPointer<int> sp1(data);
    SmartPointer<int> sp2(sp1);
    EXPECT_TRUE(sp2);
    EXPECT_EQ(*sp2.data(), 42);
}

TEST_F(SmartPointerTest, MoveConstructor)
{
    int *data = new int(42);
    SmartPointer<int> sp1(data);
    SmartPointer<int> sp2(std::move(sp1));
    EXPECT_TRUE(sp2);
    EXPECT_EQ(*sp2.data(), 42);
    EXPECT_FALSE(sp1);
}

TEST_F(SmartPointerTest, AssignmentOperator)
{
    int *data1 = new int(42);
    int *data2 = new int(84);
    SmartPointer<int> sp1(data1);
    SmartPointer<int> sp2(data2);
    sp1 = sp2;
    EXPECT_TRUE(sp1);
    EXPECT_EQ(*sp1.data(), 84);
}

TEST_F(SmartPointerTest, MoveAssignmentOperator)
{
    int *data1 = new int(42);
    int *data2 = new int(84);
    SmartPointer<int> sp1(data1);
    SmartPointer<int> sp2(data2);
    sp1 = std::move(sp2);
    EXPECT_TRUE(sp1);
    EXPECT_EQ(*sp1.data(), 84);
    EXPECT_FALSE(sp2);
}

// TEST_F(SmartPointerTest, Destructor)
// {
//     int *data = new int(42);
//     {
//         SmartPointer<int> sp(data);
//         EXPECT_TRUE(sp);
//     }
//     // data should be deleted here, but we cannot directly check if it's nullptr
//     // Instead, we can check that the memory is no longer accessible
//     EXPECT_DEATH({ *data = 0; }, "");
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
