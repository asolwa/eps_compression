#include <gtest/gtest.h>
#include "../../src/mainwindow.h"
 
TEST(SquareRootTest, PositiveNos) {
    ASSERT_EQ(6, MainWindow::squareRoot(36.0));
    ASSERT_EQ(18.0, MainWindow::squareRoot(324.0));
    ASSERT_EQ(25.4, MainWindow::squareRoot(645.16));
    ASSERT_EQ(0, MainWindow::squareRoot(0.0));
    ASSERT_EQ(0, MainWindow::squareRoot(0));
}
 
TEST(SquareRootTest, NegativeNos) {
    ASSERT_EQ(-1.0, MainWindow::squareRoot(-15.0));
    ASSERT_EQ(-1.0, MainWindow::squareRoot(-0.2));
    ASSERT_EQ(0, 0);
}
